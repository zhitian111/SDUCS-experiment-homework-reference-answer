#!/bin/zsh
source /opt/ros/jazzy/setup.zsh

echo "由于实验特性，请先在另一个终端中运行实验1脚本，打开小海龟显示，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "现在生成第二个小海龟...\n\r"
ros2 service call /spawn turtlesim/srv/Spawn "{x: 5.0, y: 5.0, theta: 0.0, name: 'turtle2'}"&
echo "第二个小海龟已生成！\n\r"
echo "按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "现在改变背景色...\n\r"
ros2 param set /turtlesim background_b 0
ros2 param set /turtlesim background_r 255
ros2 param set /turtlesim background_g 0
ros2 service call /clear turtlesim/srv/Clear
echo "背景色已变为红色！\n\r"
echo "按任意键继续..."
read -k 1 -s
echo "\n\r"
pkill -f turtlesim
pkill -f python3
