#!/bin/zsh
source /opt/ros/jazzy/setup.zsh

echo "由于实验特性，请先在另一个终端中运行实验5测试脚本，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "开始执行小海龟自动转圈消息的发布..."
cd ~/catkin_ws
source ./install/setup.zsh
echo "请使用任意键退出接下来执行的程序，确认无误后按任意键继续..."
read -k 1 -s
echo "\n\r"
ros2 run learning_topic velocity_publisher&
read -k 1 -s
echo "\n\r"
pkill -f velocity
echo "接下来测试小海龟位置订阅的功能，请使用任意键退出接下来执行的程序，确认无误后按任意键继续..."
ros2 run learning_topic velocity_publisher >>/dev/null 2>/dev/null &
ros2 run learning_topic pose_subscriber&
read -k 1 -s
echo "\n\r"
pkill -f pose
pkill -f turtle
pkill -f python3
echo "接下来测试自定义消息的发布和订阅，请使用任意键退出接下来执行的程序，请先在另一个终端中运行发布者程序，确认无误后按任意键继续..."
read -k 1 -s
echo "\n\r"
ros2 run learning_topic person_subscriber&
read -k 1 -s
echo "\n\r"
pkill -f person
