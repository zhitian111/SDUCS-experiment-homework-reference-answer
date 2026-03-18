#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void showImage(Mat& img, String name = "Image") {
    imshow(name, img);
    waitKey(0);
}

void saveImage(Mat& img, String path) {
    if (imwrite(path, img)) {
        cout << "Image saved successfully to " << path << endl;
    } else {
        cout << "Failed to save image to " << path << endl;
    }
}

Mat openMat(String path) {
    Mat src = imread(path, IMREAD_UNCHANGED);
    if (src.empty()) {
        cout << "无法读取" << path << endl;
        exit(-1);
    }
    if (src.channels() != 4) {
        cout << path << "不是4通道图像，自动补全 alpha 通道" << endl;
        vector<Mat> channels;
        split(src, channels);
        Mat alpha = Mat::zeros(src.size(), CV_8UC1);
        alpha.setTo(Scalar(255));
        channels.push_back(alpha);
        merge(channels, src);
    }
    return src;
}

// --------------- 实验1 的实现：基于 split/merge 与矩阵运算 ---------------
Mat alphaBlend_Exp1(Mat& front, Mat& back) {
    Mat backResized;
    resize(back, backResized, front.size());

    vector<Mat> front_bgrChannels, back_bgrChannels;
    Mat alpha_float;
    {
        vector<Mat> channels;
        split(front, channels);
        front_bgrChannels = { channels[0], channels[1], channels[2] };
        channels[3].convertTo(alpha_float, CV_32F, 1.0 / 255.0);  // α ∈ [0,1]，非二值
    }
    {
        vector<Mat> channels;
        split(backResized, channels);
        back_bgrChannels = { channels[0], channels[1], channels[2] };
    }

    Mat alpha3;
    vector<Mat> alphaChannels = { alpha_float, alpha_float, alpha_float };
    merge(alphaChannels, alpha3);
    Mat frontBGR, backBGR;
    merge(front_bgrChannels, frontBGR);
    merge(back_bgrChannels, backBGR);

    Mat foregroundFloat, backgroundFloat;
    frontBGR.convertTo(foregroundFloat, CV_32FC3);
    backBGR.convertTo(backgroundFloat, CV_32FC3);
    // 图像合成公式：C_out = α * C_fg + (1-α) * C_bg
    Mat resultFloat = alpha3.mul(foregroundFloat) + (Scalar::all(1.0) - alpha3).mul(backgroundFloat);

    Mat blended;
    resultFloat.convertTo(blended, CV_8UC3);
    return blended;
}

// --------------- 实验2 优化：指针直接遍历，图像合成公式（α 非二值） ---------------
Mat alphaBlend_Exp2_Ptr(Mat& front, Mat& back) {
    CV_Assert(front.channels() == 4);
    Mat backResized;
    resize(back, backResized, front.size());
    // 背景可能是 3 通道(BGR) 或 4 通道(BGRA)，只取前 3 通道参与合成
    const int backChannels = backResized.channels();
    CV_Assert(backChannels == 3 || backChannels == 4);

    const int rows = front.rows;
    const int cols = front.cols;
    Mat blended(rows, cols, CV_8UC3);

    for (int y = 0; y < rows; ++y) {
        const uchar* pFront = front.ptr<uchar>(y);       // BGRA，步长 4
        const uchar* pBack  = backResized.ptr<uchar>(y); // BGR 或 BGRA，步长 backChannels
        uchar*       pOut   = blended.ptr<uchar>(y);     // BGR，步长 3

        for (int x = 0; x < cols; ++x) {
            // 图像合成公式：C_out = α*C_fg + (1-α)*C_bg，α 为归一化透明度 [0,1]，非二值
            const float a = pFront[3] / 255.0f;

            pOut[0] = cv::saturate_cast<uchar>(a * pFront[0] + (1.0f - a) * pBack[0]);
            pOut[1] = cv::saturate_cast<uchar>(a * pFront[1] + (1.0f - a) * pBack[1]);
            pOut[2] = cv::saturate_cast<uchar>(a * pFront[2] + (1.0f - a) * pBack[2]);

            pFront += 4;
            pBack  += backChannels;  // 按实际通道数步进，避免越界
            pOut   += 3;
        }
    }
    return blended;
}

void runAlphaBlendWithTiming(String front_path, String back_path, int repeatCount = 100) {
    Mat front_img = openMat(front_path);
    Mat back_img  = openMat(back_path);

    cout << "front_img: " << front_img.cols << "x" << front_img.rows << ", channels=" << front_img.channels() << endl;
    cout << "back_img:  " << back_img.cols << "x" << back_img.rows << ", channels=" << back_img.channels() << endl;
    cout << "重复次数: " << repeatCount << " (取平均时间)" << endl << endl;

    // ---------- 实验1 方法计时 ----------
    Mat result1;
    double t1 = getTickCount();
    for (int i = 0; i < repeatCount; ++i) {
        result1 = alphaBlend_Exp1(front_img, back_img);
    }
    t1 = (getTickCount() - t1) / getTickFrequency();
    cout << "[实验1 split/merge] 总时间: " << (t1 * 1000.0) << " ms, 平均: " << (t1 * 1000.0 / repeatCount) << " ms/次" << endl;

    // ---------- 实验2 指针遍历方法计时 ----------
    Mat result2;
    double t2 = getTickCount();
    for (int i = 0; i < repeatCount; ++i) {
        result2 = alphaBlend_Exp2_Ptr(front_img, back_img);
    }
    t2 = (getTickCount() - t2) / getTickFrequency();
    cout << "[实验2 指针遍历]   总时间: " << (t2 * 1000.0) << " ms, 平均: " << (t2 * 1000.0 / repeatCount) << " ms/次" << endl;

    cout << endl << "速度比 (实验1/实验2): " << (t1 / t2) << " (实验2 约为实验1 的 " << (t1 / t2) << " 倍)" << endl;

    saveImage(result1, "result_exp1.png");
    saveImage(result2, "result_exp2.png");
    showImage(result2, "Alpha Blend (Exp2 Ptr)");
}

int main() {
    cout << "实验2：Alpha 混合优化与耗时对比" << endl;
    runAlphaBlendWithTiming("./图片2.png", "./back.jpg", 100);
    return 0;
}
