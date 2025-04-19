//
// Created by goksu on 4/6/19.
//

#pragma once

#include "Triangle.hpp"
#include <algorithm>
#include <eigen3/Eigen/Eigen>
using namespace Eigen;
class LineSegmentParametricEquation2f
{
private:
  Eigen::Vector2f p0, t;
  float upper_bound, lower_bound;

public:
  LineSegmentParametricEquation2f(const Eigen::Vector2f& p0,
                                  const Eigen::Vector2f& p1)
      : p0(p0)
  {
    float dx = p1.x() - p0.x();
    float dy = p1.y() - p0.y();
    t = Eigen::Vector2f(dy, dx);
    lower_bound = 0.0f;
    upper_bound = 1.0f;
  }
  LineSegmentParametricEquation2f(const Eigen::Vector3f& p0,
                                  const Eigen::Vector3f& p1)
  {
    this->p0[0] = p0[0];
    this->p0[1] = p0[1];
    float dx = p1[0] - p0[0];
    float dy = p1[1] - p0[1];
    t = Eigen::Vector2f(dy, dx);
    lower_bound = 0.0f;
    upper_bound = 1.0f;
  }
  Eigen::Vector2f operator()(float s) const { return p0 + s * t; }
  void set_upper_bound(float upper) { upper_bound = upper; }
  void set_lower_bound(float lower) { lower_bound = lower; }
};

namespace rst
{
enum class Buffers
{
  Color = 1,
  Depth = 2
};

inline Buffers operator|(Buffers a, Buffers b)
{
  return Buffers((int)a | (int)b);
}

inline Buffers operator&(Buffers a, Buffers b)
{
  return Buffers((int)a & (int)b);
}

enum class Primitive
{
  Line,
  Triangle
};

/*
 * For the curious : The draw function takes two buffer id's as its arguments.
 * These two structs make sure that if you mix up with their orders, the
 * compiler won't compile it. Aka : Type safety
 * */
struct pos_buf_id
{
  int pos_id = 0;
};

struct ind_buf_id
{
  int ind_id = 0;
};

class rasterizer
{
public:
  rasterizer(int w, int h);
  pos_buf_id load_positions(const std::vector<Eigen::Vector3f>& positions);
  ind_buf_id load_indices(const std::vector<Eigen::Vector3i>& indices);

  void set_model(const Eigen::Matrix4f& m);
  void set_view(const Eigen::Matrix4f& v);
  void set_projection(const Eigen::Matrix4f& p);

  void set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color);

  void clear(Buffers buff);

  void draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, Primitive type);

  std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }

private:
  void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);
  void rasterize_wireframe(const Triangle& t);
  LineSegmentParametricEquation2f Liang_Barsky(Eigen::Vector3f& begin,
                                               Eigen::Vector3f& end);

private:
  Eigen::Matrix4f model;
  Eigen::Matrix4f view;
  Eigen::Matrix4f projection;

  std::map<int, std::vector<Eigen::Vector3f>> pos_buf;
  std::map<int, std::vector<Eigen::Vector3i>> ind_buf;

  std::vector<Eigen::Vector3f> frame_buf;
  std::vector<float> depth_buf;
  int get_index(int x, int y);

  int width, height;

  int next_id = 0;
  int get_next_id() { return next_id++; }
};
} // namespace rst
