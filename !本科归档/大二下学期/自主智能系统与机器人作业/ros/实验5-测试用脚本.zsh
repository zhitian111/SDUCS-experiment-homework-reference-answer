#!/bin/zsh
source /opt/ros/jazzy/setup.zsh
echo "即将进入小海龟程序部分...\n\r"
./实验1-练习ROS常用命令并运行小海龟程序.zsh
cd ~/catkin_ws
source ./install/setup.zsh
ros2 run learning_topic person_publisher
