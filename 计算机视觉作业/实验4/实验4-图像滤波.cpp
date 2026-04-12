#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace cv;

static int gaussianKernelSize(double sigma) {
    int k = static_cast<int>(std::floor(6.0 * sigma - 1.0));
    return std::max(1, k);
}

static std::vector<double> build1DGaussianKernel(int k, double sigma) {
    std::vector<double> g(static_cast<size_t>(k));
    double sum = 0.0;
    const double inv = 1.0 / (std::sqrt(2.0 * CV_PI) * sigma);
    for (int i = 0; i < k; i++) {
        double x = static_cast<double>(i) - 0.5 * static_cast<double>(k - 1);
        double v = inv * std::exp(-(x * x) / (2.0 * sigma * sigma));
        g[static_cast<size_t>(i)] = v;
        sum += v;
    }
    for (double& v : g) {
        v /= sum;
    }
    return g;
}

static Mat build2DGaussianKernel(int k, double sigma) {
    Mat ker(k, k, CV_64F);
    double sum = 0.0;
    const double inv = 1.0 / (2.0 * CV_PI * sigma * sigma);
    for (int j = 0; j < k; j++) {
        double y = static_cast<double>(j) - 0.5 * static_cast<double>(k - 1);
        for (int i = 0; i < k; i++) {
            double x = static_cast<double>(i) - 0.5 * static_cast<double>(k - 1);
            double v = inv * std::exp(-(x * x + y * y) / (2.0 * sigma * sigma));
            ker.at<double>(j, i) = v;
            sum += v;
        }
    }
    ker /= sum;
    return ker;
}

static void convolve1DHorizontal(const Mat& src, Mat& dst, const std::vector<double>& kernel,
                                 int borderType = BORDER_REFLECT_101) {
    CV_Assert(src.type() == CV_32FC1 || src.type() == CV_32FC3);
    const int k = static_cast<int>(kernel.size());
    const int padL = (k - 1) / 2;
    const int padR = k - 1 - padL;

    Mat padded;
    copyMakeBorder(src, padded, 0, 0, padL, padR, borderType);

    dst.create(src.size(), src.type());
    const int ch = src.channels();
    const int w = src.cols;
    const int h = src.rows;

    if (ch == 1) {
        for (int y = 0; y < h; y++) {
            const float* ps = padded.ptr<float>(y);
            float* pd = dst.ptr<float>(y);
            for (int x = 0; x < w; x++) {
                double acc = 0.0;
                for (int t = 0; t < k; t++) {
                    acc += kernel[static_cast<size_t>(t)] * static_cast<double>(ps[x + t]);
                }
                pd[x] = static_cast<float>(acc);
            }
        }
    } else {
        for (int y = 0; y < h; y++) {
            const float* ps = padded.ptr<float>(y);
            float* pd = dst.ptr<float>(y);
            for (int x = 0; x < w; x++) {
                double accB = 0.0, accG = 0.0, accR = 0.0;
                for (int t = 0; t < k; t++) {
                    const float* p = ps + 3 * (x + t);
                    accB += kernel[static_cast<size_t>(t)] * p[0];
                    accG += kernel[static_cast<size_t>(t)] * p[1];
                    accR += kernel[static_cast<size_t>(t)] * p[2];
                }
                pd[3 * x + 0] = static_cast<float>(accB);
                pd[3 * x + 1] = static_cast<float>(accG);
                pd[3 * x + 2] = static_cast<float>(accR);
            }
        }
    }
}

static void convolve1DVertical(const Mat& src, Mat& dst, const std::vector<double>& kernel,
                               int borderType = BORDER_REFLECT_101) {
    CV_Assert(src.type() == CV_32FC1 || src.type() == CV_32FC3);
    const int k = static_cast<int>(kernel.size());
    const int padT = (k - 1) / 2;
    const int padB = k - 1 - padT;

    Mat padded;
    copyMakeBorder(src, padded, padT, padB, 0, 0, borderType);

    dst.create(src.size(), src.type());
    const int ch = src.channels();
    const int w = src.cols;
    const int h = src.rows;

    if (ch == 1) {
        for (int y = 0; y < h; y++) {
            float* pd = dst.ptr<float>(y);
            for (int x = 0; x < w; x++) {
                double acc = 0.0;
                for (int t = 0; t < k; t++) {
                    const float* row = padded.ptr<float>(y + t);
                    acc += kernel[static_cast<size_t>(t)] * static_cast<double>(row[x]);
                }
                pd[x] = static_cast<float>(acc);
            }
        }
    } else {
        for (int y = 0; y < h; y++) {
            float* pd = dst.ptr<float>(y);
            for (int x = 0; x < w; x++) {
                double accB = 0.0, accG = 0.0, accR = 0.0;
                for (int t = 0; t < k; t++) {
                    const float* row = padded.ptr<float>(y + t);
                    const float* p = row + 3 * x;
                    accB += kernel[static_cast<size_t>(t)] * p[0];
                    accG += kernel[static_cast<size_t>(t)] * p[1];
                    accR += kernel[static_cast<size_t>(t)] * p[2];
                }
                pd[3 * x + 0] = static_cast<float>(accB);
                pd[3 * x + 1] = static_cast<float>(accG);
                pd[3 * x + 2] = static_cast<float>(accR);
            }
        }
    }
}

static void convertToOutput(const Mat& srcF, Mat& dst, int srcDepth) {
    if (srcDepth == CV_8U) {
        srcF.convertTo(dst, CV_8U);
    } else if (srcDepth == CV_32F) {
        dst = srcF.clone();
    } else {
        srcF.convertTo(dst, srcDepth);
    }
}

void gaussianBlur(const Mat& input, Mat& output, double sigma) {
    CV_Assert(!input.empty());
    if (sigma <= 0.0) {
        input.copyTo(output);
        return;
    }

    const int depth = input.depth();
    const int k = gaussianKernelSize(sigma);
    const std::vector<double> ker = build1DGaussianKernel(k, sigma);

    Mat work;
    input.convertTo(work, CV_32F);

    Mat tmp, workF;
    convolve1DHorizontal(work, tmp, ker, BORDER_REFLECT_101);
    convolve1DVertical(tmp, workF, ker, BORDER_REFLECT_101);

    convertToOutput(workF, output, depth);
}

static void gaussianBlur2DFull(const Mat& input, Mat& output, double sigma) {
    CV_Assert(!input.empty());
    if (sigma <= 0.0) {
        input.copyTo(output);
        return;
    }

    const int depth = input.depth();
    const int k = gaussianKernelSize(sigma);
    Mat ker = build2DGaussianKernel(k, sigma);

    Mat work, workF;
    input.convertTo(work, CV_32F);

    const int pad = (k - 1) / 2;
    Mat padded;
    copyMakeBorder(work, padded, pad, pad, pad, pad, BORDER_REFLECT_101);

    workF.create(work.size(), work.type());
    const int ch = work.channels();
    const int w = work.cols;
    const int h = work.rows;

    if (ch == 1) {
        for (int y = 0; y < h; y++) {
            float* pd = workF.ptr<float>(y);
            for (int x = 0; x < w; x++) {
                double acc = 0.0;
                for (int j = 0; j < k; j++) {
                    const float* ps = padded.ptr<float>(y + j);
                    for (int i = 0; i < k; i++) {
                        acc += ker.at<double>(j, i) * static_cast<double>(ps[x + i]);
                    }
                }
                pd[x] = static_cast<float>(acc);
            }
        }
    } else {
        for (int y = 0; y < h; y++) {
            float* pd = workF.ptr<float>(y);
            for (int x = 0; x < w; x++) {
                double accB = 0.0, accG = 0.0, accR = 0.0;
                for (int j = 0; j < k; j++) {
                    const float* row = padded.ptr<float>(y + j);
                    for (int i = 0; i < k; i++) {
                        const float* p = row + 3 * (x + i);
                        const double c = ker.at<double>(j, i);
                        accB += c * p[0];
                        accG += c * p[1];
                        accR += c * p[2];
                    }
                }
                pd[3 * x + 0] = static_cast<float>(accB);
                pd[3 * x + 1] = static_cast<float>(accG);
                pd[3 * x + 2] = static_cast<float>(accR);
            }
        }
    }

    convertToOutput(workF, output, depth);
}

static double computePSNR(const Mat& a, const Mat& b) {
    CV_Assert(a.size() == b.size() && a.type() == b.type());
    Mat a32, b32;
    a.convertTo(a32, CV_32F);
    b.convertTo(b32, CV_32F);

    Mat d;
    absdiff(a32, b32, d);
    d = d.mul(d);
    Scalar s = sum(d);
    const double sse = s[0] + s[1] + s[2] + s[3];
    const double n = static_cast<double>(a.channels() * a.total());
    const double mse = sse / n;

    if (mse < 1e-10) {
        return 99.0;
    }
    return 10.0 * std::log10((255.0 * 255.0) / mse);
}

static std::string parentDir(const std::string& p) {
    size_t pos = p.find_last_of("\\/");
    if (pos == std::string::npos) {
        return ".";
    }
    return p.substr(0, pos);
}

int main(int argc, char** argv) {
    std::string exeDir = parentDir(std::string(argv[0]));
    std::string outDir = exeDir + "\\figures";
    std::filesystem::create_directories(outDir);

    std::string imgPath;
    if (argc > 1) {
        imgPath = argv[1];
    } else {
        imgPath = exeDir + "\\..\\mumu.jpg";
    }

    Mat src = imread(imgPath, IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "无法读取图像: " << imgPath << std::endl;
        return 1;
    }
    if (src.channels() == 4) {
        cvtColor(src, src, COLOR_BGRA2BGR);
    }

    auto outPath = [&outDir](const char* leaf) {
        return outDir + "\\" + leaf;
    };

    imwrite(outPath("e4_input.png"), src);

    const double testSigma = 1.0;
    const int k = gaussianKernelSize(testSigma);
    std::cout << "sigma=" << testSigma << " -> kernel size k=" << k << " (floor(6*sigma-1))" << std::endl;

    Mat mine, cvRef, diff;
    gaussianBlur(src, mine, testSigma);
    GaussianBlur(src, cvRef, Size(k, k), testSigma, testSigma, BORDER_DEFAULT);
    absdiff(mine, cvRef, diff);

    imwrite(outPath("e4_mine_sigma1.png"), mine);
    imwrite(outPath("e4_opencv_sigma1.png"), cvRef);
    imwrite(outPath("e4_absdiff_sigma1.png"), diff);

    const double psnr = computePSNR(mine, cvRef);
    std::cout << "与 cv::GaussianBlur 的 PSNR (sigma=1, k=" << k << "): " << psnr << " dB" << std::endl;

    for (double s : {0.5, 1.0, 2.0, 3.0}) {
        Mat b;
        gaussianBlur(src, b, s);
        char tag[32];
        std::snprintf(tag, sizeof(tag), "%.1f", s);
        imwrite(outDir + "\\e4_blur_sigma_" + std::string(tag) + ".png", b);
        std::cout << "sigma=" << s << " -> k=" << gaussianKernelSize(s) << std::endl;
    }

    const int repeat = 5;
    Mat tmp;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < repeat; i++) {
        gaussianBlur(src, tmp, testSigma);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < repeat; i++) {
        gaussianBlur2DFull(src, tmp, testSigma);
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    const double msSep = std::chrono::duration<double, std::milli>(t1 - t0).count() / repeat;
    const double ms2d = std::chrono::duration<double, std::milli>(t2 - t1).count() / repeat;

    std::cout << "平均耗时：可分离卷积 " << msSep << " ms，全二维卷积 " << ms2d
              << " ms（约 " << (ms2d / std::max(msSep, 1e-6)) << " 倍）" << std::endl;

    FILE* fp = std::fopen(outPath("e4_metrics.txt").c_str(), "w");
    if (fp) {
        std::fprintf(fp, "PSNR_vs_OpenCV_sigma1\t%.4f\n", psnr);
        std::fprintf(fp, "kernel_size_formula\tfloor(6*sigma-1)\n");
        std::fprintf(fp, "sigma\t1.0\tk\t%d\n", k);
        std::fprintf(fp, "time_separable_ms\t%.4f\n", msSep);
        std::fprintf(fp, "time_full2d_ms\t%.4f\n", ms2d);
        std::fclose(fp);
    }

    std::cout << "结果已写入: " << outDir << std::endl;
    return 0;
}
