#!/usr/bin/zsh
source /opt/ros/humble/local_setup.zsh

echo "由于turtle_teleop_key的特性无法设为后台执行，请另开一个终端执行实验1的脚本，然后按任意键继续..."
read -k 1 -s
echo "\n\r"

ros2 run rqt_graph rqt_graph &
echo "请刷新rqt_graph窗口查看结果后继续...\n\r"
echo "按任意键继续进入topic实验..."
read -k 1 -s
echo "\n\r"

echo "topic echo 部分\n\r"
sleep 2
ros2 topic echo /turtle1/cmd_vel &
TOPIC_ECHO_PID=$!
echo "请在另一个终端输入控制按键后查看topic结果，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
kill $TOPIC_ECHO_PID 2>/dev/null

echo "topic list 部分\n\r"
ros2 topic list -v
echo "按任意键继续..."
read -k 1 -s
echo "\n\r"

echo "topic type 部分\n\r"
ros2 topic type /turtle1/cmd_vel
echo "按任意键继续..."
read -k 1 -s
echo "\n\r"

echo "topic pub 部分\n\r"
echo "单次命令流\n\r"
ros2 topic pub -1 /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
echo "按任意键继续..."
read -k 1 -s
echo "\n\r"

echo "连续命令流\n\r"
ros2 topic pub /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}" -r 1 >>/dev/null &
TOPIC_PUB_PID=$!

sleep 2

echo "启动海龟位置信息可视化...\n\r"
# 直接启动rqt_plot，然后手动添加话题
ros2 run rqt_plot rqt_plot &
RQT_PLOT_PID=$!

echo "等待rqt_plot启动...（约5秒）"
sleep 5

echo "请在rqt_plot窗口左上角输入框手动添加以下话题："
echo "1. 输入: /turtle1/pose/x    然后按回车"
echo "2. 输入: /turtle1/pose/y    然后按回车" 
echo "3. 输入: /turtle1/pose/theta 然后按回车"
echo "\n\r"

echo "海龟正在转圈运动，您应该看到："
echo "- X坐标 (/turtle1/pose/x) - 波形变化"
echo "- Y坐标 (/turtle1/pose/y) - 波形变化" 
echo "- 朝向角度 (/turtle1/pose/theta) - 线性增长"
echo "\n\r"

echo "手动添加话题后，观察海龟运动轨迹，然后按任意键继续..."
read -k 1 -s
echo "\n\r"

# 停止连续命令流
kill $TOPIC_PUB_PID 2>/dev/null
pkill -f "ros2 topic pub"

echo "现在进入rqt_plot实验...\n\r"
pkill -f "rqt_plot"
sleep 1

ros2 run rqt_plot rqt_plot &
echo "按任意键结束本实验..."
read -k 1 -s
echo "\n\r"

pkill -f rqt_graph
pkill -f rqt_plot
pkill -f "ros2 topic"
pkill -f python3