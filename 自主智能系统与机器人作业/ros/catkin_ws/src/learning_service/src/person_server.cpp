#include <learning_service/srv/person.hpp>
#include <rclcpp/rclcpp.hpp>
#include <string>

// 使用std::shared_ptr传递请求和响应
bool personCallback(
    const std::shared_ptr<learning_service::srv::Person::Request> req,
    std::shared_ptr<learning_service::srv::Person::Response> res)
{
  // 使用RCLCPP_INFO输出日志
  RCLCPP_INFO(rclcpp::get_logger("person_server"),
              "Person: name: %s, age: %d, sex: %d", req->name.c_str(), req->age,
              req->sex);
  res->result = "OK";
  return true;
}

int main(int argc, char** argv)
{
  // 初始化ROS 2
  rclcpp::init(argc, argv);

  // 创建节点
  auto node = std::make_shared<rclcpp::Node>("person_server");

  // 创建服务
  auto server = node->create_service<learning_service::srv::Person>(
      "/show_person", &personCallback);

  // 日志输出
  RCLCPP_INFO(node->get_logger(), "Ready to show person information.");

  // 自旋，处理回调
  rclcpp::spin(node);

  // 关闭ROS 2
  rclcpp::shutdown();
  return 0;
}
