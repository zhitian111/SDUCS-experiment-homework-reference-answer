//
// Created by goksu on 4/6/19.
//

#include "rasterizer.hpp"
#include <algorithm>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <stdexcept>

rst::pos_buf_id
rst::rasterizer::load_positions(const std::vector<Eigen::Vector3f>& positions)
{
  auto id = get_next_id();
  pos_buf.emplace(id, positions);

  return {id};
}

rst::ind_buf_id
rst::rasterizer::load_indices(const std::vector<Eigen::Vector3i>& indices)
{
  auto id = get_next_id();
  ind_buf.emplace(id, indices);

  return {id};
}

// Bresenham's line drawing algorithm
// Code taken from a stack overflow answer: https://stackoverflow.com/a/16405254
void rst::rasterizer::draw_line(Eigen::Vector3f begin, Eigen::Vector3f end)
{
  auto x1 = begin.x();
  auto y1 = begin.y();
  auto x2 = end.x();
  auto y2 = end.y();

  Eigen::Vector3f line_color = {255, 255, 255};

  int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

  dx = x2 - x1;
  dy = y2 - y1;
  dx1 = fabs(dx);
  dy1 = fabs(dy);
  px = 2 * dy1 - dx1;
  py = 2 * dx1 - dy1;

  if (dy1 <= dx1)
  {
    if (dx >= 0)
    {
      x = x1;
      y = y1;
      xe = x2;
    }
    else
    {
      x = x2;
      y = y2;
      xe = x1;
    }
    Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
    set_pixel(point, line_color);
    for (i = 0; x < xe; i++)
    {
      x = x + 1;
      if (px < 0)
      {
        px = px + 2 * dy1;
      }
      else
      {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
        {
          y = y + 1;
        }
        else
        {
          y = y - 1;
        }
        px = px + 2 * (dy1 - dx1);
      }
      //            delay(0);
      Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
      set_pixel(point, line_color);
    }
  }
  else
  {
    if (dy >= 0)
    {
      x = x1;
      y = y1;
      ye = y2;
    }
    else
    {
      x = x2;
      y = y2;
      ye = y1;
    }
    Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
    set_pixel(point, line_color);
    for (i = 0; y < ye; i++)
    {
      y = y + 1;
      if (py <= 0)
      {
        py = py + 2 * dx1;
      }
      else
      {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
        {
          x = x + 1;
        }
        else
        {
          x = x - 1;
        }
        py = py + 2 * (dx1 - dy1);
      }
      //            delay(0);
      Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
      set_pixel(point, line_color);
    }
  }
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f)
{
  return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

void rst::rasterizer::draw(rst::pos_buf_id pos_buffer,
                           rst::ind_buf_id ind_buffer, rst::Primitive type)
{
  auto& buf = pos_buf[pos_buffer.pos_id];
  auto& ind = ind_buf[ind_buffer.ind_id];

  float f1 = (100 - 0.1) / 2.0;
  float f2 = (100 + 0.1) / 2.0;

  Eigen::Matrix4f mvp = projection * view * model;
  if (type == rst::Primitive::Line)
  {
  }
  if (type == rst::Primitive::Triangle)
  {
    for (auto& i : ind)
    {
      Triangle t;

      Eigen::Vector4f v[] = {mvp * to_vec4(buf[i[0]], 1.0f),
                             mvp * to_vec4(buf[i[1]], 1.0f),
                             mvp * to_vec4(buf[i[2]], 1.0f)};

      for (auto& vec : v)
      {
        vec /= vec.w();
      }

      for (auto& vert : v)
      {
        vert.x() = 0.5 * width * (vert.x() + 1.0);
        vert.y() = 0.5 * height * (vert.y() + 1.0);
        vert.z() = vert.z() * f1 + f2;
      }

      for (int i = 0; i < 3; ++i)
      {
        t.setVertex(i, v[i].head<3>());
        t.setVertex(i, v[i].head<3>());
        t.setVertex(i, v[i].head<3>());
      }

      t.setColor(0, 255.0, 0.0, 0.0);
      t.setColor(1, 0.0, 255.0, 0.0);
      t.setColor(2, 0.0, 0.0, 255.0);

      rasterize_wireframe(t);
    }
  }
}

void rst::rasterizer::rasterize_wireframe(const Triangle& t)
{
  draw_line(t.c(), t.a());
  draw_line(t.c(), t.b());
  draw_line(t.b(), t.a());
}

void rst::rasterizer::set_model(const Eigen::Matrix4f& m) { model = m; }

void rst::rasterizer::set_view(const Eigen::Matrix4f& v) { view = v; }

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p)
{
  projection = p;
}

void rst::rasterizer::clear(rst::Buffers buff)
{
  if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
  {
    std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{0, 0, 0});
  }
  if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth)
  {
    std::fill(depth_buf.begin(), depth_buf.end(),
              std::numeric_limits<float>::infinity());
  }
}

rst::rasterizer::rasterizer(int w, int h) : width(w), height(h)
{
  frame_buf.resize(w * h);
  depth_buf.resize(w * h);
}

int rst::rasterizer::get_index(int x, int y)
{
  return (height - y) * width + x;
}

void rst::rasterizer::set_pixel(const Eigen::Vector3f& point,
                                const Eigen::Vector3f& color)
{
  // old index: auto ind = point.y() + point.x() * width;
  if (point.x() < 0 || point.x() >= width || point.y() < 0 ||
      point.y() >= height)
    return;
  auto ind = (height - point.y()) * width + point.x();
  frame_buf[ind] = color;
}

LineSegmentParametricEquation2f
rst::rasterizer::Liang_Barsky(Eigen::Vector3f& begin, Eigen::Vector3f& end)
{
  LineSegmentParametricEquation2f line(begin, end);
  // 计算参数方程
  float t_x, t_y, x_0, y_0;
  float x_min, x_max, y_min, y_max;
  x_0 = begin.x();
  y_0 = begin.y();
  x_min = 0;
  x_max = width - 1;
  y_min = 0;
  y_max = height - 1;
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

  line = LineSegmentParametricEquation2f(Eigen::Vector2f(xn1, y_max - yn1),
                                         Eigen::Vector2f(xn2, y_max - yn2));
  return line;
}
