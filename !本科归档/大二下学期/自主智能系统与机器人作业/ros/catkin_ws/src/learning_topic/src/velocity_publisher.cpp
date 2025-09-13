#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("velocity_publisher");
  auto velocity_publisher =
      node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
  rclcpp::Rate loop_rate(10); // 10 Hz

  while (rclcpp::ok())
  {
    geometry_msgs::msg::Twist vel_msg;
    vel_msg.linear.x = 0.5;
    vel_msg.angular.z = 0.2;
    velocity_publisher->publish(vel_msg);
    RCLCPP_INFO(node->get_logger(),
                "Publish turtle velocity command [%.2f m/s, %.2f rad/s]",
                vel_msg.linear.x, vel_msg.angular.z);
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
