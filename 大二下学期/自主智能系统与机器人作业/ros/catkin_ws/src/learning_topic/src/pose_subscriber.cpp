#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>

void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
{
  RCLCPP_INFO(rclcpp::get_logger("pose_subscriber"),
              "Turtle pose: x = %.6f, y = %.6f", msg->x, msg->y);
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("pose_subscriber");
  auto sub = node->create_subscription<turtlesim::msg::Pose>("/turtle1/pose",
                                                             10, poseCallback);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
