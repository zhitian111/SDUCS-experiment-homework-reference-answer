
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <eigen3/Eigen/Core>
#include <fstream>
#include <iostream>
#include <limits>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <pthread.h>
#include <sstream>
#include <stddef.h>
#include <string>
#include <thread>
#include <utility>
#include <vector>
using namespace cv;
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define FRAMEWORK_HEIGHT 600
#define FRAMEWORK_WIDTH 600
constexpr auto y_max =
    (WINDOW_HEIGHT - FRAMEWORK_HEIGHT) / 2 + FRAMEWORK_HEIGHT;
constexpr auto x_max = (WINDOW_WIDTH - FRAMEWORK_WIDTH) / 2 + FRAMEWORK_WIDTH;
constexpr auto y_min = (WINDOW_HEIGHT - FRAMEWORK_HEIGHT) / 2;
constexpr auto x_min = (WINDOW_WIDTH - FRAMEWORK_WIDTH) / 2;
class LineSegmentParametricEquation2f
{
private:
  Eigen::Vector2f p0, t, p1;
  float upper_bound, lower_bound;

public:
  LineSegmentParametricEquation2f(const Eigen::Vector2f& p0,
                                  const Eigen::Vector2f& p1)
      : p0(p0), p1(p1)
  {
    float dx = p1.x() - p0.x();
    float dy = p1.y() - p0.y();
    t = Eigen::Vector2f(dx, dy);
    lower_bound = 0.0f;
    upper_bound = 1.0f;
  }
  LineSegmentParametricEquation2f(const Eigen::Vector3f& p0,
                                  const Eigen::Vector3f& p1)
  {
    this->p0[0] = p0[0];
    this->p0[1] = p0[1];
    this->p1[0] = p1[0];
    this->p1[1] = p1[1];
    float dx = p1[0] - p0[0];
    float dy = p1[1] - p0[1];
    t = Eigen::Vector2f(dy, dx);
    lower_bound = 0.0f;
    upper_bound = 1.0f;
  }
  Eigen::Vector2f operator()(float s) const { return p0 + s * t; }
  void set_upper_bound(float upper) { upper_bound = upper; }
  void set_lower_bound(float lower) { lower_bound = lower; }
  Eigen::Vector2f get_p0() const { return p0; }
  Eigen::Vector2f get_p1() const { return p0 + t * upper_bound; }
  void display() const
  {
    std::cout << "p0: " << p0.transpose() << std::endl;
    std::cout << "t: " << t.transpose() << std::endl;
    std::cout << "upper_bound: " << upper_bound << std::endl;
    std::cout << "lower_bound: " << lower_bound << std::endl;
  }
};
class LineSegmentNormalEquation2f
{
private:
  float a, b, c;
  float upper_bound, lower_bound;
  Eigen::Vector2f p0, p1;

public:
  LineSegmentNormalEquation2f(const Eigen::Vector2f& p0,
                              const Eigen::Vector2f& p1)
  {
    a = p0[1] - p1[1];                 // y1 - y2
    b = p1[0] - p0[0];                 // x2 - x1
    c = p0[0] * p1[1] - p1[0] * p0[1]; // x1*y2 - x2*y1
    upper_bound = p1.x();
    lower_bound = p0.x();
    this->p0 = p0;
    this->p1 = p1;
  }
  float operator()(float s) const
  {
    if (lower_bound == upper_bound)
    {
      return 0;
    }
    return -(a * s + c) / b;
  }
  float operator()(float x, float y) const
  {
    if (b == 0)
    {
      return 0;
    }
    return a * x + b * y + c;
  }
  float operator[](float s) const { return -(b * s + c) / a; }
  LineSegmentNormalEquation2f(const LineSegmentParametricEquation2f& l)
  {
    Eigen::Vector2f p0 = l.get_p0();
    Eigen::Vector2f p1 = l.get_p1();
    a = p0[1] - p1[1];
    b = p1[0] - p0[0];
    c = p0[0] * p1[1] - p1[0] * p0[1];
    upper_bound = l.get_p1().x();
    lower_bound = l.get_p0().x();
    this->p0 = p0;
    this->p1 = p1;
  }
  float get_a() const { return a; }
  float get_b() const { return b; }
  float get_c() const { return c; }
  float get_k() const
  {
    if (b == 0)
    {
      if (a > 0)
      {
        return std::numeric_limits<float>::max();
      }
      if (a < 0)
      {
        return -std::numeric_limits<float>::max();
      }
    }
    return -a / b;
  }
  Eigen::Vector2f get_p0() const { return p0; }
  Eigen::Vector2f get_p1() const { return p1; }
};
LineSegmentParametricEquation2f Liang_Barsky(Eigen::Vector2f& begin,
                                             Eigen::Vector2f& end)
{
  LineSegmentParametricEquation2f line(begin, end);
  // 计算参数方程
  float t_x, t_y, x_0, y_0;
  x_0 = begin.x();
  y_0 = begin.y();
  // defining variables
  float p1, p2, p3, p4, q1, q2, q3, q4;
  p1 = -(end.x() - x_0);
  p2 = -p1;
  p3 = -(end.y() - y_0);
  p4 = -p3;
  q1 = x_0 - x_min;
  q2 = x_max - x_0;
  q3 = y_0 - y_min;
  q4 = y_max - y_0;
  float r1, r2, r3, r4;
  std::vector<float> posarr;
  std::vector<float> negarr;
  posarr.push_back(1);
  negarr.push_back(0);
  // 线段全部在屏幕外
  if ((p1 == 0 && q1 < 0) || (p3 == 0 && q3 < 0))
  {
    line.set_upper_bound(0);
    return line;
  }
  // 对于非0的pk, uk = qk/pk
  if (p1 != 0)
  {
    r1 = q1 / p1;
    r2 = q2 / p2;
    if (p1 < 0)
    {
      posarr.push_back(r2);
      negarr.push_back(r1);
    }
    else
    {
      posarr.push_back(r1);
      negarr.push_back(r2);
    }
  }
  if (p3 != 0)
  {
    r3 = q3 / p3;
    r4 = q4 / p4;
    if (p3 < 0)
    {
      posarr.push_back(r4);
      negarr.push_back(r3);
    }
    else
    {
      posarr.push_back(r3);
      negarr.push_back(r4);
    }
  }
  float xn1, xn2, yn1, yn2;
  float rn1, rn2;
  rn1 = *std::max_element(negarr.begin(), negarr.end());
  rn2 = *std::min_element(posarr.begin(), posarr.end());
  // 线段在屏幕外
  if (rn1 > rn2)
  {
    line.set_upper_bound(0);
    return line;
  }
  xn1 = x_0 + rn1 * p2;
  yn1 = y_0 + rn1 * p4;
  xn2 = x_0 + rn2 * p2;
  yn2 = y_0 + rn2 * p4;
  std::cout << "xn1: " << xn1 << " yn1: " << yn1 << " xn2: " << xn2
            << " yn2: " << yn2 << std::endl;
  line = LineSegmentParametricEquation2f(Eigen::Vector2f(xn1, yn1),
                                         Eigen::Vector2f(xn2, yn2));
  return line;
}
// 画矩形框
void draw_rectangle(Mat& img, Point p1, Point p2, Scalar color)
{
  auto x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
  line(img, Point(x1, y1), Point(x2, y1), color, 1);
  line(img, Point(x1, y2), Point(x2, y2), color, 1);
  line(img, Point(x1, y1), Point(x1, y2), color, 1);
  line(img, Point(x2, y1), Point(x2, y2), color, 1);
}
void draw_framework(Mat& img)
{
  auto offset_x = (WINDOW_WIDTH - FRAMEWORK_WIDTH) / 2;
  auto offset_y = (WINDOW_HEIGHT - FRAMEWORK_HEIGHT) / 2;
  draw_rectangle(img, Point(offset_x, offset_y),
                 Point(offset_x + FRAMEWORK_HEIGHT, offset_y + FRAMEWORK_WIDTH),
                 Scalar(255, 255, 255));
}
// 中点画线法画线段
void draw_line(Mat& img, LineSegmentParametricEquation2f l, Scalar color)
{
  // float x1, y1, x2, y2;
  // x1 = l.get_p0().x();
  // y1 = l.get_p0().y();
  // x2 = l.get_p1().x();
  // y2 = l.get_p1().y();
  // line(img, Point(x1, y1), Point(x2, y2), color, 1);
  auto ll = LineSegmentNormalEquation2f(l);
  // if (ll.get_k() < 0 && abs(ll.get_k()) != std::numeric_limits<float>::max())
  // {
  //   ll = LineSegmentNormalEquation2f(ll.get_p1(), ll.get_p0());
  // }
  // if (abs(ll.get_k()) == std::numeric_limits<float>::max())
  // {
  //   ll
  // }
  if (abs(ll.get_k()) > 1)
  {
    int x1, y1, x2, y2;
    x1 = std::round(ll.get_p0().x());
    y1 = std::round(ll.get_p0().y());
    x2 = std::round(ll.get_p1().x());
    y2 = std::round(ll.get_p1().y());
    if (y1 > y2)
    {
      std::swap(y1, y2);
      std::swap(x1, x2);
    }
    while (y1 <= y2)
    {
      img.at<Vec3b>(y1, x1) = cv::Vec3b(color[0], color[1], color[2]);
      if (ll.get_k() > 0)
      {
        auto mid_x = x1 + 0.5;
        auto q = ll[y1 + 1];
        if (q > mid_x)
        {
          y1 = y1 + 1;
          x1 = x1 + 1;
        }
        else
        {
          y1 = y1 + 1;
        }
      }
      else
      {
        auto mid_x = x1 - 0.5;
        auto q = ll[y1 + 1];
        if (q < mid_x)
        {
          y1 = y1 + 1;
          x1 = x1 - 1;
        }
        else
        {
          y1 = y1 + 1;
        }
      }
    }
  }
  else
  {
    int x1, y1, x2, y2;
    x1 = std::round(ll.get_p0().x());
    y1 = std::round(ll.get_p0().y());
    x2 = std::round(ll.get_p1().x());
    y2 = std::round(ll.get_p1().y());

    if (x1 > x2)
    {
      std::swap(x1, x2);
      std::swap(y1, y2);
    }
    while (x1 <= x2)
    {
      img.at<Vec3b>(y1, x1) = cv::Vec3b(color[0], color[1], color[2]);
      auto mid_y = y1 + 0.5;
      auto q = ll(x1 + 1);
      if (q > mid_y)
      {
        x1 = x1 + 1;
        y1 = y1 + 1;
      }
      else
      {
        x1 = x1 + 1;
      }
    }
  }
}
std::vector<LineSegmentParametricEquation2f> lines;
std::vector<std::pair<Point, Point>> lines_without_clip;
bool is_end = false;
void input_lines()
{
  while (true)
  {
    float x1, y1, x2, y2;
    if (std::cin.peek() != EOF)
    {
      std::string s;
      std::getline(std::cin, s);

      std::stringstream ss(s);
      ss >> x1 >> y1 >> x2 >> y2;
      lines_without_clip.push_back(
          std::make_pair(Point(x1, y1), Point(x2, y2)));
      Eigen::Vector2f begin(x1, y1);
      Eigen::Vector2f end(x2, y2);
      LineSegmentParametricEquation2f l = Liang_Barsky(begin, end);
      lines.push_back(l);
    }
    if (is_end)
    {
      break;
    }
  }
}
int main(int argc, char** argv)
{
  std::string output_file_name;
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-o") == 0)
    {
      output_file_name = std::string(argv[i + 1]);
    }
  }
  Mat img = Mat::zeros(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3);
  std::thread input_thread(input_lines);
  input_thread.detach();
  while (true)
  {
    img.setTo(Scalar(0, 0, 0));
    draw_framework(img);
    for (auto& l : lines_without_clip)
    {
      line(img, l.first, l.second, Scalar(255, 0, 0));
    }
    for (auto& l : lines)
    {
      draw_line(img, l, Scalar(0, 0, 255));
    }
    imshow("line", img);
    if (waitKey(1000 / 60) == 27)
    {
      break;
    }
  }
  is_end = true;
  if (!output_file_name.empty())
  {
    imwrite(output_file_name, img);
  }
  return 0;
}
