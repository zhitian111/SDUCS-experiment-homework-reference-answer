#include <learning_service/srv/person.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("person_client");
  auto client =
      node->create_client<learning_service::srv::Person>("/show_person");

  auto request = std::make_shared<learning_service::srv::Person::Request>();
  request->name = "Tom";
  request->age = 20;
  request->sex = learning_service::srv::Person::Request::SEX_MALE;

  RCLCPP_INFO(node->get_logger(),
              "Call service to show person[name:%s, age:%d, sex:%d]",
              request->name.c_str(), request->age, request->sex);

  // Wait for the service to be available
  while (!client->wait_for_service(std::chrono::seconds(1)))
  {
    if (!rclcpp::ok())
    {
      RCLCPP_ERROR(node->get_logger(),
                   "Interrupted while waiting for the service. Exiting.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting...");
  }

  // Call the service
  auto result = client->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(node->get_logger(), "Show person result: %s",
                result.get()->result.c_str());
  }
  else
  {
    RCLCPP_ERROR(node->get_logger(), "Failed to call service /show_person");
  }

  rclcpp::shutdown();
  return 0;
}
