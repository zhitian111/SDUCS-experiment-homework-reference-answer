#!/bin/zsh
source /opt/ros/jazzy/setup.zsh
echo "现在启动小海龟图形界面...\n\r"
ros2 run turtlesim turtlesim_node
echo "现在启动小海龟命令服务...\n\r"
cd ~/catkin_ws
source ./install/setup.zsh
ros2 run learning_service turtle_command_server&
echo "现在启动个人信息服务...\n\r"
ros2 run learning_service person_server
