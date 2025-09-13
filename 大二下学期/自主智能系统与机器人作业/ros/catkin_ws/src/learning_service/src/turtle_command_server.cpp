#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>

class TurtleCommandServer : public rclcpp::Node
{
public:
  TurtleCommandServer() : Node("turtle_command_server")
  {
    // Create publisher
    turtle_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
        "/turtle1/cmd_vel", 10);

    // Create service
    service_ = this->create_service<std_srvs::srv::Trigger>(
        "turtle_command",
        std::bind(&TurtleCommandServer::pubCommandCallback, this,
                  std::placeholders::_1, std::placeholders::_2));

    // Create timer for publishing velocity
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(100),
        std::bind(&TurtleCommandServer::timerCallback, this));

    RCLCPP_INFO(this->get_logger(), "Ready to receive turtle command.");
  }

private:
  void pubCommandCallback(
      const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
      std::shared_ptr<std_srvs::srv::Trigger::Response> response)
  {
    (void)request; // Unused parameter
    pub_command_ = !pub_command_;
    RCLCPP_INFO(this->get_logger(), "Publish turtle velocity command [%s]",
                pub_command_ ? "YES" : "NO");
    response->success = true;
    response->message = "Change turtle command status.";
  }

  void timerCallback()
  {
    if (pub_command_)
    {
      geometry_msgs::msg::Twist vel_msg;
      vel_msg.linear.x = 0.5;
      vel_msg.angular.z = 0.2;
      turtle_vel_pub_->publish(vel_msg);
    }
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr turtle_vel_pub_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;
  rclcpp::TimerBase::SharedPtr timer_;
  bool pub_command_ = false;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TurtleCommandServer>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
