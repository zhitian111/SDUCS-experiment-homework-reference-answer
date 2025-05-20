#include <learning_topic/msg/person.hpp>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("person_publisher");
  auto pub =
      node->create_publisher<learning_topic::msg::Person>("/person_info", 10);
  rclcpp::Rate rate(1); // 1 Hz

  while (rclcpp::ok())
  {
    learning_topic::msg::Person person_msg;
    person_msg.name = "Tom";
    person_msg.age = 18;
    person_msg.sex = learning_topic::msg::Person::SEX_MALE;
    pub->publish(person_msg);
    RCLCPP_INFO(node->get_logger(), "Publish person info: %s, %u, %u",
                person_msg.name.c_str(), person_msg.age, person_msg.sex);
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
