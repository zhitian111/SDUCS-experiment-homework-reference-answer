cmake_minimum_required(VERSION 3.8)
project(learning_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
# set(MSG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/msg/Person.msg")
# if (NOT EXISTS ${MSG_FILE})
#   message(FATAL_ERROR "Person.msg not found at: ${MSG_FILE}")
# endif()
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Person.msg"
  DEPENDENCIES std_msgs
)

add_executable(person_publisher src/person_publisher.cpp)
ament_target_dependencies(person_publisher rclcpp std_msgs)
add_executable(person_subscriber src/person_subscriber.cpp)
ament_target_dependencies(person_subscriber rclcpp std_msgs)
add_executable(pose_subscriber src/pose_subscriber.cpp)
ament_target_dependencies(pose_subscriber rclcpp turtlesim)
add_executable(velocity_publisher src/velocity_publisher.cpp)
ament_target_dependencies(velocity_publisher rclcpp geometry_msgs)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(person_publisher ${cpp_typesupport_target})
target_link_libraries(person_subscriber ${cpp_typesupport_target})
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()
install(TARGETS velocity_publisher DESTINATION lib/${PROJECT_NAME})
install(TARGETS pose_subscriber DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY msg DESTINATION share/${PROJECT_NAME})
install(TARGETS person_publisher DESTINATION lib/${PROJECT_NAME})
install(TARGETS person_subscriber DESTINATION lib/${PROJECT_NAME})
ament_package()
