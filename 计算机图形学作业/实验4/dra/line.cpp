#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <sstream>
#include <stddef.h>
#include <string>
#include <vector>
using namespace cv;

class my_point
{
public:
  double x, y;
  size_t v_id;
};
class my_edge
{
public:
  size_t edge_id;
  size_t v1_id, v2_id;
};
class my_face
{
public:
  size_t face_id;
  std::vector<size_t> points;
  std::vector<size_t> edges;
};
std::vector<my_point> all_points;
std::vector<my_edge> all_edges;
std::vector<my_face> all_faces;
#define SCALE 200.0
#define OFFSET 100.0
// // 设置窗口
//    // 注意opencv的坐标系原点在左上角
// Mat img = Mat::zeros(Size(800, 800), CV_8UC3);
// img.setTo(255);              // 设置屏幕为白色
//
// Point p1(100, 100);          // 点p1
// Point p2(758, 50);           // 点p2
//
// // 画直线函数
// line(img, p1, p2, Scalar(0, 0, 255), 1);   // 红色
// line(img, Point(300, 300), Point(758, 400), Scalar(0, 255, 255), 1); //
// 黄色
//
//    // 画点 p1
// circle(img, p1, 3, Scalar(0, 255, 0), -1);
//    // 画点 p2
// circle(img, p2, 3, Scalar(120, 120,sum 120), -1);
//
// imshow("画板", img);
// waitKey(0);
void read_file(const char* filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cout << "Error: cannot open file " << filename << std::endl;
    return;
  }
  size_t point_index = 0;
  size_t edge_index = 0;
  size_t face_index = 0;

  char type;
  while (file >> type)
  {
    if (type == 'v')
    {
      my_point p;
      point_index++;
      file >> p.x >> p.y;
      p.v_id = point_index;
      p.x *= SCALE;
      p.y *= SCALE;
      p.x += OFFSET;
      p.y += OFFSET;
      all_points.push_back(p);
    }
    if (type == 'e')
    {
      my_edge e;
      edge_index++;
      file >> e.v1_id >> e.v2_id;
      e.edge_id = edge_index;
      all_edges.push_back(e);
    }
    if (type == 'f')
    {
      my_face f;
      face_index++;
      std::string str;
      std::getline(file, str);
      std::stringstream ss(str);
      // size_t v1, v2, v3, v4;
      // file >> v1 >> v2 >> v3 >> v4;
      // f.face_id = face_index;
      // f.points.push_back(v1);
      // f.points.push_back(v2);
      // f.points.push_back(v3);
      // f.points.push_back(v4);
      // for (auto& i : all_edges)
      // {
      //   if (i.v1_id == v1 && i.v2_id == v2)
      //   {
      //     f.edges.push_back(i.edge_id);
      //   }
      //   if (i.v1_id == v2 && i.v2_id == v3)
      //   {
      //     f.edges.push_back(i.edge_id);
      //   }
      //   if (i.v1_id == v3 && i.v2_id == v4)
      //   {
      //     f.edges.push_back(i.edge_id);
      //   }
      //   if (i.v1_id == v4 && i.v2_id == v1)
      //   {
      //     f.edges.push_back(i.edge_id);
      //   }
      // }
      f.face_id = face_index;
      size_t buf;
      while (ss >> buf)
      {
        // std::cout << buf << std::endl;
        f.points.push_back(buf);
      }
      for (size_t i = 0; i < f.points.size(); i++)
      {
        auto edge = std::find_if(
            all_edges.begin(), all_edges.end(),
            [f, i](const my_edge& e)
            {
              return (e.v1_id == f.points[i] &&
                      e.v2_id == f.points[(i + 1) % f.points.size()]) ||
                     (e.v1_id == f.points[(i + 1) % f.points.size()] &&
                      e.v2_id == f.points[i]);
            });
        f.edges.push_back(edge->edge_id);
      }
      all_faces.push_back(f);
    }
  }
}
void draw_all(Mat& img)
{
  // 画点
  for (auto& i : all_points)
  {
    circle(img, Point(i.x, i.y), 3, Scalar(0, 255, 0), -1);
  }
  // 画边
  for (auto& i : all_edges)
  {
    auto point_1 =
        std::find_if(all_points.begin(), all_points.end(),
                     [i](const my_point& p) { return p.v_id == i.v1_id; });
    auto point_2 =
        std::find_if(all_points.begin(), all_points.end(),
                     [i](const my_point& p) { return p.v_id == i.v2_id; });
    line(img, Point(point_1->x, point_1->y), Point(point_2->x, point_2->y),
         Scalar(0, 0, 255), 1);
  }
  // 画面
}
void display_all()
{
  for (auto& i : all_points)
  {
    std::cout << "点" << i.v_id << "(" << i.x << "," << i.y << ")" << std::endl;
  }
  for (auto& i : all_edges)
  {
    std::cout << "边" << i.edge_id << "(" << i.v1_id << "," << i.v2_id << ")"
              << std::endl;
  }
  for (auto& i : all_faces)
  {
    std::cout << "面" << i.face_id << std::endl;
    for (auto& j : i.points)
    {
      std::cout << "点" << j << " " << std::endl;
    }
    for (auto& j : i.edges)
    {
      std::cout << "边" << j << " " << std::endl;
    }
  }
}
void display_faces(std::vector<my_face>& faces)
{
  std::cout << "共有" << faces.size() << "个面" << std::endl;
  for (auto& i : faces)
  {
    std::cout << "面" << i.face_id << std::endl;
    std::cout << "点" << i.points.size() << std::endl;
    for (auto& j : i.points)
    {
      auto point = std::find_if(all_points.begin(), all_points.end(),
                                [j](const my_point& p) { return p.v_id == j; });
      std::cout << "(" << point->x << "," << point->y << ")" << std::endl;
    }
    std ::cout << "边" << i.edges.size() << std::endl;
    for (auto& j : i.edges)
    {
      auto edge =
          std::find_if(all_edges.begin(), all_edges.end(),
                       [j](const my_edge& e) { return e.edge_id == j; });
      std::cout << "(" << edge->v1_id << "," << edge->v2_id << ")" << std::endl;
    }
  }
}
void display_points(Mat& img, std::vector<my_point>& points)
{
  std::srand(std::time(0));
  double r = std::rand() % 256;
  double g = std::rand() % 256;
  double b = std::rand() % 256;
  for (auto& i : points)
  {
    circle(img, Point(i.x, i.y), 3, Scalar(b, g, r), -1);
  }
}
void catmull_clark()
{
  // 面点
  std::vector<my_point> face_points;
  for (auto& i : all_faces)
  {
    double sum_x = 0.0;
    double sum_y = 0.0;
    size_t cnt = i.points.size();
    for (auto& j : i.points)
    {
      auto point = std::find_if(all_points.begin(), all_points.end(),
                                [j](const my_point& p) { return p.v_id == j; });
      sum_x += point->x;
      sum_y += point->y;
    }
    my_point p;
    p.x = sum_x / cnt;
    p.y = sum_y / cnt;
    p.v_id = i.face_id;
    face_points.push_back(p);
  }
  // std::cout << face_points.size() << std::endl;
  // for (auto& i : face_points)
  // {
  //   std::cout << "点" << i.v_id << "(" << i.x << "," << i.y << ")" <<
  //   std::endl;
  // }
  // 边中点
  std::vector<my_point> edge_avg_points;
  for (auto& i : all_edges)
  {
    auto point_1 =
        std::find_if(all_points.begin(), all_points.end(),
                     [i](const my_point& p) { return p.v_id == i.v1_id; });
    auto point_2 =
        std::find_if(all_points.begin(), all_points.end(),
                     [i](const my_point& p) { return p.v_id == i.v2_id; });
    my_point p;
    p.x = (point_1->x + point_2->x) / 2.0;
    p.y = (point_1->y + point_2->y) / 2.0;
    p.v_id = i.edge_id;
    edge_avg_points.push_back(p);
  }
  // 边点
  std::vector<my_point> edge_points;
  for (auto& i : all_edges)
  {
    auto start = all_faces.begin();
    my_point sum;
    size_t cnt = 0;
    auto face_1 = std::find_if(
        start, all_faces.end(),
        [i](const my_face& f)
        {
          return find_if(f.edges.begin(), f.edges.end(), [i](const size_t& e)
                         { return e == i.edge_id; }) != f.edges.end();
        });
    start = face_1 + 1;
    auto face_2 = std::find_if(
        start, all_faces.end(),
        [i](const my_face& f)
        {
          return find_if(f.edges.begin(), f.edges.end(), [i](const size_t& e)
                         { return e == i.edge_id; }) != f.edges.end();
        });
    if (face_1 != all_faces.end())
    {
      auto point = std::find_if(face_points.begin(), face_points.end(),
                                [face_1](const my_point& p)
                                { return p.v_id == face_1->face_id; });
      std::cout << "面的中点" << face_1->face_id << "(" << point->x << ","
                << point->y << ")" << std::endl;
      sum.x = point->x;
      sum.y = point->y;
      cnt++;
    }
    if (face_2 != all_faces.end())
    {
      auto point = std::find_if(face_points.begin(), face_points.end(),
                                [face_2](const my_point& p)
                                { return p.v_id == face_2->face_id; });
      std::cout << "面的中点" << face_2->face_id << "(" << point->x << ","
                << point->y << ")" << std::endl;
      sum.x += point->x;
      sum.y += point->y;
      cnt++;
    }
    sum.x /= cnt;
    sum.y /= cnt;
    sum.x *= 0.5;
    sum.y *= 0.5;
    sum.x +=
        std::find_if(edge_avg_points.begin(), edge_avg_points.end(),
                     [i](const my_point& e) { return i.edge_id == e.v_id; })
            ->x *
        0.5;
    sum.y +=
        std::find_if(edge_avg_points.begin(), edge_avg_points.end(),
                     [i](const my_point& e) { return i.edge_id == e.v_id; })
            ->y *
        0.5;
    sum.v_id = i.edge_id;
    edge_points.push_back(sum);
  }
  // while (start != all_faces.end())
  // {
  //   auto face = std::find_if(
  //       start, all_faces.end(),
  //       [i](const my_face& f)
  //       {
  //         return find_if(f.edges.begin(), f.edges.end(), [i](const size_t& e)
  //                        { return e == i.edge_id; }) != f.edges.end();
  //       });
  //   if (face != all_faces.end())
  //   {
  //     auto point = std::find_if(face_points.begin(), face_points.end(),
  //                               [face](const my_point& p)
  //                               { return p.v_id == face->face_id; });
  //     sum.x += point->x;
  //     sum.y += point->y;
  //     cnt++;
  //     start = face;
  //   }
  //   else
  //   {
  //     break;
  //   }
  // }

  Mat img = Mat::zeros(Size(800, 800), CV_8UC3);
  img.setTo(255); // 设置屏幕为白色
  display_points(img, face_points);
  display_points(img, edge_avg_points);
  display_points(img, edge_points);
  draw_all(img);
  imshow("画板", img);
  waitKey(0);
  // 更新点
  for (auto& i : all_points)
  {
  }
}
int main()
{
  read_file("obj1.txt");
  // display_all();
  display_faces(all_faces);
  Mat img = Mat::zeros(Size(800, 800), CV_8UC3);
  img.setTo(255); // 设置屏幕为白色
  draw_all(img);
  // display_all();
  catmull_clark();
  imshow("画板", img);
  waitKey(0);
  // 输出png
  imwrite("output.png", img);
  return 0;
}
