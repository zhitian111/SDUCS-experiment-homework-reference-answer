
#include <string>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// ---------- 3.1：S 形对比度（可调参数 + 滑块） ----------
static Mat g_srcContrast;   // 原始图（BGR，8U）
static int g_steepness = 30;   // 陡度，越大 S 形越明显
static int g_midpoint = 128;   // 曲线中心（0~255）

// 归一化 sigmoid，再线性拉伸使 0->0、255->255
static double sigmoidNorm(double t, double k, double m) {
    auto g = [&](double x) {
        return 1.0 / (1.0 + exp(-k * (x - m)));
    };
    double g0 = g(0.0);
    double g1 = g(1.0);
    if (fabs(g1 - g0) < 1e-9)
        return t;
    double gn = g(t);
    return (gn - g0) / (g1 - g0);
}

static void buildContrastLut(Mat& lut1, double k, double mid01) {
    lut1.create(256, 1, CV_8UC1);
    for (int i = 0; i < 256; i++) {
        double t = i / 255.0;
        double y = sigmoidNorm(t, k, mid01);
        int v = (int)lround(y * 255.0);
        v = max(0, min(255, v));
        lut1.at<uchar>(i, 0) = (uchar)v;
    }
}

static void applySContrast(const Mat& src, Mat& dst, double k, double mid01) {
    Mat lut;
    buildContrastLut(lut, k, mid01);
    if (src.channels() == 1) {
        LUT(src, lut, dst);
    }
    else {
        vector<Mat> ch;
        split(src, ch);
        for (size_t c = 0; c < ch.size(); c++)
            LUT(ch[c], lut, ch[c]);
        merge(ch, dst);
    }
}

static void onContrastTrackbar(int, void*) {
    // 陡度：滑块 5~100 -> k 约 2~24
    double k = 2.0 + (g_steepness / 100.0) * 22.0;
    double m = g_midpoint / 255.0;
    Mat out;
    applySContrast(g_srcContrast, out, k, m);
    imshow("3.1 S形对比度", out);
}

static void runContrastSliderDemo(const String& path) {
    g_srcContrast = imread(path);
    if (g_srcContrast.empty()) {
        cout << "无法读取图像: " << path << endl;
        return;
    }
    if (g_srcContrast.channels() == 4)
        cvtColor(g_srcContrast, g_srcContrast, COLOR_BGRA2BGR);
    namedWindow("3.1 S形对比度", WINDOW_AUTOSIZE);
    g_steepness = 30;
    g_midpoint = 128;
    createTrackbar("陡度(0-100)", "3.1 S形对比度", &g_steepness, 100, onContrastTrackbar);
    createTrackbar("中点(0-255)", "3.1 S形对比度", &g_midpoint, 255, onContrastTrackbar);
    onContrastTrackbar(0, nullptr);
    cout << "3.1：拖动滑块调整 S 形对比度，按任意键继续。" << endl;
    waitKey(0);
    destroyWindow("3.1 S形对比度");
}

// ---------- 3.2：双线性插值 resize ----------
static uchar sampleBilinear(const Mat& src, float sx, float sy, int c) {
    int w = src.cols;
    int h = src.rows;
    float x = sx;
    float y = sy;
    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    float wx = x - (float)x0;
    float wy = y - (float)y0;
    x0 = max(0, min(w - 1, x0));
    x1 = max(0, min(w - 1, x1));
    y0 = max(0, min(h - 1, y0));
    y1 = max(0, min(h - 1, y1));
    float v00 = (float)src.at<Vec3b>(y0, x0)[c];
    float v01 = (float)src.at<Vec3b>(y1, x0)[c];
    float v10 = (float)src.at<Vec3b>(y0, x1)[c];
    float v11 = (float)src.at<Vec3b>(y1, x1)[c];
    float top = v00 * (1.f - wx) + v10 * wx;
    float bot = v01 * (1.f - wx) + v11 * wx;
    float v = top * (1.f - wy) + bot * wy;
    return (uchar)max(0.f, min(255.f, v + 0.5f));
}

Mat resizeBilinear(const Mat& src, int dstW, int dstH) {
    if (src.empty() || dstW <= 0 || dstH <= 0) {
        cout << "resizeBilinear: 无效参数" << endl;
        return Mat();
    }
    if (src.type() != CV_8UC3) {
        cout << "resizeBilinear: 当前实现仅支持 CV_8UC3" << endl;
        return Mat();
    }
    int srcW = src.cols;
    int srcH = src.rows;
    if (srcW == dstW && srcH == dstH)
        return src.clone();
    Mat dst(dstH, dstW, CV_8UC3);
    float scaleX = (float)srcW / (float)dstW;
    float scaleY = (float)srcH / (float)dstH;
    for (int dy = 0; dy < dstH; dy++) {
        float sy = (dy + 0.5f) * scaleY - 0.5f;
        for (int dx = 0; dx < dstW; dx++) {
            float sx = (dx + 0.5f) * scaleX - 0.5f;
            Vec3b& p = dst.at<Vec3b>(dy, dx);
            p[0] = sampleBilinear(src, sx, sy, 0);
            p[1] = sampleBilinear(src, sx, sy, 1);
            p[2] = sampleBilinear(src, sx, sy, 2);
        }
    }
    return dst;
}

int main() {
    String imgPath = "./图片1.png";

    cout << "实验 3.1：S 形对比度（滑块调参）" << endl;
    runContrastSliderDemo(imgPath);

    cout << "实验 3.2：双线性插值缩放" << endl;
    Mat src = imread(imgPath);
    if (src.empty()) {
        cout << "无法读取图像: " << imgPath << endl;
        return -1;
    }
    if (src.channels() == 4)
        cvtColor(src, src, COLOR_BGRA2BGR);
    int tw = 320;
    int th = 240;
    Mat mine = resizeBilinear(src, tw, th);
    Mat ref;
    resize(src, ref, Size(tw, th), 0, 0, INTER_LINEAR);
    if (!mine.empty()) {
        imshow("3.2 自实现双线性", mine);
        imshow("3.2 OpenCV INTER_LINEAR 对照", ref);
        cout << "缩放至 " << tw << "x" << th << "，左为自实现，右为 OpenCV 对照。按任意键结束。" << endl;
        waitKey(0);
        destroyAllWindows();
    }

    return 0;
}
