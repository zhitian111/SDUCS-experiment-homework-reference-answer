#include <rclcpp/rclcpp.hpp>
#include <turtlesim/srv/spawn.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("turtle_spawn");

  // Create service client
  auto client = node->create_client<turtlesim::srv::Spawn>("/spawn");

  // Wait for service to be available
  while (!client->wait_for_service(std::chrono::seconds(1)))
  {
    if (!rclcpp::ok())
    {
      RCLCPP_ERROR(node->get_logger(),
                   "Interrupted while waiting for the service. Exiting.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "Service /spawn not available, waiting...");
  }

  // Prepare service request
  auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
  request->x = 2.0;
  request->y = 2.0;
  request->name = "turtle2";

  RCLCPP_INFO(node->get_logger(),
              "Call service to spawn turtle[x=%.6f, y=%.6f, name=%s]",
              request->x, request->y, request->name.c_str());

  // Call service asynchronously
  auto result = client->async_send_request(request);

  // Wait for the result
  if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(node->get_logger(),
                "Spawning turtle successfully![x=%.6f, y=%.6f, name=%s]",
                request->x, request->y, request->name.c_str());
  }
  else
  {
    RCLCPP_ERROR(node->get_logger(), "Failed to call service /spawn");
  }

  rclcpp::shutdown();
  return 0;
}
