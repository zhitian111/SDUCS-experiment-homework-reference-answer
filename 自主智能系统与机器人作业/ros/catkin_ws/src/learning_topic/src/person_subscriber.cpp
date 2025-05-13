#include <learning_topic/msg/person.hpp>
#include <rclcpp/rclcpp.hpp>

void personCallback(const learning_topic::msg::Person::SharedPtr person)
{
  RCLCPP_INFO(rclcpp::get_logger("person_subscriber"),
              "Person info: name=%s, age=%d, sex=%d", person->name.c_str(),
              person->age, person->sex);
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("person_subscriber");
  auto sub = node->create_subscription<learning_topic::msg::Person>(
      "/person_info", 10, personCallback);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
