cmake_minimum_required(VERSION 3.8)
project(learning_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

add_executable(turtle_spawn src/turtle_spawn.cpp)
ament_target_dependencies(turtle_spawn rclcpp turtlesim)
add_executable(turtle_command_server src/turtle_command_server.cpp)
ament_target_dependencies(turtle_command_server rclcpp turtlesim std_msgs geometry_msgs std_srvs)
add_executable(person_server src/person_server.cpp)
ament_target_dependencies(person_server rclcpp std_msgs)
add_executable(person_client src/person_client.cpp)
ament_target_dependencies(person_client rclcpp std_msgs)
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/Person.srv"
  DEPENDENCIES std_msgs
)
ament_export_dependencies(rosidl_default_generators)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(person_server ${cpp_typesupport_target})
target_link_libraries(person_client ${cpp_typesupport_target})
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
install(TARGETS turtle_spawn
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS turtle_command_server
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS person_server
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS person_client
  DESTINATION lib/${PROJECT_NAME})
ament_package()
