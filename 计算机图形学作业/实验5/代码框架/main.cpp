#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
  Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

  Eigen::Matrix4f translate;
  translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1, -eye_pos[2],
      0, 0, 0, 1;

  view = translate * view;

  return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
  Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
  rotation_angle = rotation_angle * MY_PI / 180;
  // TODO: Implement this function
  // Create the model matrix for rotating the triangle around the Z axis.
  // Then return it.
  Eigen::Matrix4f translate = Eigen::Matrix4f::Identity();
  translate << std::cos(rotation_angle), -std::sin(rotation_angle), 0, 0,
      std::sin(rotation_angle), std::cos(rotation_angle), 0, 0, 0, 0, 1, 0, 0,
      0, 0, 1;
  model = translate;
  return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
  // Students will implement this function

  Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

  // TODO: Implement this function
  // Create the projection matrix for the given parameters.
  // Then return it.

  float t = std::tan(eye_fov / 2);
  projection << 1 / (t * aspect_ratio), 0, 0, 0, 0, 1 / t, 0, 0, 0, 0,
      (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zNear - zFar), 0,
      0, -1, 0;

  return projection;
}

Eigen::Matrix4f get_rotation(Eigen::Vector3f axis, float angle)
{
  angle = angle * MY_PI / 180;
  axis = axis.normalized();
  float tem = 1 - std::cos(angle);
  float cos_angle = std::cos(angle);
  float sin_angle = std::sin(angle);
  Eigen::Matrix4f translate = Eigen::Matrix4f::Identity();
  translate << axis[0] * axis[0] * tem + cos_angle,
      axis[0] * axis[1] * tem - axis[2] * sin_angle,
      axis[0] * axis[2] * tem + axis[1] * sin_angle, 0,
      axis[1] * axis[0] * tem + axis[2] * sin_angle,
      axis[1] * axis[1] * tem + cos_angle,
      axis[1] * axis[2] * tem - axis[0] * sin_angle, 0,
      axis[2] * axis[0] * tem - axis[1] * sin_angle,
      axis[2] * axis[1] * tem + axis[0] * sin_angle,
      axis[2] * axis[2] * tem + cos_angle, 0, 0, 0, 0, 1;
  return translate;
}

int main(int argc, const char** argv)
{
  float angle = 0;

  rst::rasterizer r(700, 700);

  Eigen::Vector3f eye_pos = {0, 0, 5};

  std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

  std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

  auto pos_id = r.load_positions(pos);
  auto ind_id = r.load_indices(ind);

  int key = 0;
  int frame_count = 0;

  // if (command_line) {
  //     r.clear(rst::Buffers::Color | rst::Buffers::Depth);
  //
  //     r.set_model(get_model_matrix(angle));
  //     r.set_view(get_view_matrix(eye_pos));
  //     r.set_projection(get_projection_matrix(45, 1, 0.1, 50));
  //
  //     r.draw(pos_id, ind_id, rst::Primitive::Triangle);
  //     cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
  //     image.convertTo(image, CV_8UC3, 1.0f);
  //
  //     cv::imwrite(filename, image);
  //
  //     return 0;
  // }
  // Eigen::Vector3f axis = Eigen::Vector3f::Identity();
  // std::cin >> axis[0] >> axis[1] >> axis[2];
  while (key != 27)
  {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    // r.set_model(get_rotation(axis,angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(30, 1, 0.1, 2));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);

    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::imshow("image", image);
    key = cv::waitKey(10);

    std::cout << "frame count: " << frame_count++ << '\n';

    if (key == 'a')
    {
      angle += 10;
    }
    else if (key == 'd')
    {
      angle -= 10;
    }
  }

  return 0;
}
