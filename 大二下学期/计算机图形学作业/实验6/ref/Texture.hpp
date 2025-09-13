//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture
{
private:
  cv::Mat image_data;

public:
  Texture(const std::string& name)
  {
    image_data = cv::imread(name);
    cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
    width = image_data.cols;
    height = image_data.rows;
  }

  int width, height;

  Eigen::Vector3f getColor(float u, float v)
  {

    if (u < 0)
      u = 0;
    if (v < 0)
      v = 0;
    if (u > 1)
      u = 1;
    if (v > 1)
      v = 1;

    auto u_img = u * width;
    auto v_img = (1 - v) * height;

    auto color = image_data.at<cv::Vec3b>(v_img, u_img);
    return Eigen::Vector3f(color[0], color[1], color[2]);
  }
  Eigen::Vector3f getColorBilinear(float u, float v)
  {
    auto x = u * width;               // 像素x坐标
    auto y = (1 - v) * height;        // 像素y坐标
    int roundx = static_cast<int>(x); // 最近的纹理点x坐标
    int roundy = static_cast<int>(y); // 最近的纹理点y坐标

    // 两个插值比例
    float s = x - roundx;
    float t = y - roundy;

    // 四个相邻纹理点
    auto p00 = image_data.at<cv::Vec3b>(roundy, roundx);
    auto p01 =
        image_data.at<cv::Vec3b>(roundy, std::min(roundx + 1, width - 1));
    auto p10 =
        image_data.at<cv::Vec3b>(std::min(roundy + 1, height - 1), roundx);
    auto p11 = image_data.at<cv::Vec3b>(std::min(roundy + 1, height - 1),
                                        std::min(roundx + 1, width - 1));

    // 水平方向插值
    auto px = p00 * (1 - s) + p10 * s;
    auto py = p01 * (1 - s) + p11 * s;

    // 竖直方向插值
    auto color = px * (1 - t) + py * t;
    return Eigen::Vector3f(color[0], color[1], color[2]);
  }
};

#endif // RASTERIZER_TEXTURE_H
