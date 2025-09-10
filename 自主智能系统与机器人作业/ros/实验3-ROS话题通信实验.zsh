#!/bin/zsh
source /opt/ros/jazzy/local_setup.zsh
echo "由于turtle_teleop_key的特性无法设为后台执行，请另开一个终端执行实验1的脚本，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
ros2 run rqt_graph rqt_graph &
echo "请刷新rqt_graph窗口查看结果后继续...\n\r"
echo "按任意键继续进入topic实验..."
read -k 1 -s
echo "\n\r"
echo "topic echo 部分\n\r"
ros2 topic echo /turtle1/cmd_vel&
echo "请在另一个终端输入控制按键后查看topic结果，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "topic list 部分\n\r"
ros2 topic list -v&
echo "按任意键继续..."
read -k 1 -s
echo "\n\r"
ros2 topic type /turtle1/cmd_vel&
echo "请在另一个终端输入控制按键后查看topic结果，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "topic pub 部分\n\r"
echo "单次命令流\n\r"
ros2 topic pub -1 /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
echo "请在另一个终端输入控制按键后查看topic结果，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "连续命令流\n\r"
ros2 topic pub /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}" -r 1 >>/dev/null &
echo "请在另一个终端输入控制按键后查看topic结果，以及在rqt_graph窗口中刷新查看结果，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "现在进入rqt_plot实验...\n\r"
ros2 run rqt_plot rqt_plot&
echo "按任意键结束本实验..."
read -k 1 -s
echo "\n\r"
pkill -f rqt_graph
pkill -f topic
pkill -f rqt_plot
pkill -f python3
pkill -9 -f rqt
