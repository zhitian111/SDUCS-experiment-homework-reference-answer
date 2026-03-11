
#include <string>
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
using namespace cv;

using namespace std;

void showImage(Mat& img, String name = "Image") {
    imshow(name, img);
    waitKey(0);
}

void showImage(String path, String name = "Image") {
    Mat img = imread(path);
    if (img.empty()) {
        cout << "Failed to load image from " << path << endl;
        return;
    }
    else {
       showImage(img, name);
    }
}

void saveImage(Mat& img, String path) {
    if (imwrite(path, img)) {
        cout << "Image saved successfully to " << path << endl;
    }
    else {
        cout << "Failed to save image to " << path << endl;
    }
}

Mat openMat(String path) {
    // 1. 读取带 alpha 的 PNG
    Mat src = imread(path, IMREAD_UNCHANGED);
    if (src.empty()) {
        cout << "无法读取" << path << endl;
        exit(-1);
    }
    // 检查是否为4通道
    if (src.channels() != 4) {
        cout << path << "不是4通道图像" << endl;
        vector<Mat> channels;
        split(src, channels);
        Mat alpha = Mat::zeros(src.size(), CV_8UC1);
        alpha.setTo(Scalar(255));
        channels.push_back(alpha);
        merge(channels, src);
    }
    return src;
}




Mat _alphaBlend(Mat& front, Mat& back) {
    // 调整背景图大小，使其和前景图一致
    resize(back, back, front.size());

    // 拆分通道
    vector<Mat> front_bgrChannels;
    vector<Mat> back_bgrChannels;
    Mat alpha_float;
    {
        vector<Mat> channels;
        split(front, channels);
        Mat b = channels[0];
        Mat g = channels[1];
        Mat r = channels[2];
        Mat alpha = channels[3];
        front_bgrChannels = { b, g, r };
        alpha.convertTo(alpha_float, CV_32F, 1.0 / 255.0);
    }
    {
        vector<Mat> channels;
        split(back, channels);
        Mat b = channels[0];
        Mat g = channels[1];
        Mat r = channels[2];
        back_bgrChannels = { b, g, r };
    }
    // 把单通道 alpha 扩展成三通道，便于和 BGR 图逐像素相乘
    Mat alpha3;
    vector<Mat> alphaChannels = { alpha_float, alpha_float, alpha_float };
    merge(alphaChannels, alpha3);
    Mat frontBGRChannels;
    Mat backBGRChannels;
    merge(front_bgrChannels, frontBGRChannels);
    merge(back_bgrChannels, backBGRChannels);
    // 前景和背景转成浮点型
    Mat foregroundFloat, backgroundFloat;
    frontBGRChannels.convertTo(foregroundFloat, CV_32FC3);
    backBGRChannels.convertTo(backgroundFloat, CV_32FC3);
    // alpha 混合
    Mat resultFloat = alpha3.mul(foregroundFloat) + (Scalar::all(1.0) - alpha3).mul(backgroundFloat);
    
    Mat blended;

    resultFloat.convertTo(blended, CV_8UC3);
    return blended;
}

void alphaBlend(String front_path, String back_path) {
    Mat front_img = openMat(front_path);
    Mat back_img = openMat(back_path);
    cout << "front_img.channels()=" << front_img.channels() << endl;
    cout << "back_img.channels()=" << back_img.channels() << endl;
    Mat result = _alphaBlend(front_img, back_img);
    showImage(result, "result");
    saveImage(result, "result.png");
}
int main()
{
    cout << "实验 1.1" << endl;
    showImage("./图片1.png");
    cout << "实验 1.2" << endl;
    alphaBlend("./图片2.png", "./back.jpg");
    return 0;
}