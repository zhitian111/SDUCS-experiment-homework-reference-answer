#!/bin/zsh
source /opt/ros/jazzy/setup.zsh
cd ~/catkin_ws
source ./install/setup.zsh

echo "由于实验特性，请先在另一个终端中运行实验6测试用脚本，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "现在生成第二个小海龟...\n\r"
ros2 run learning_service turtle_spawn
echo "\n\r"
echo "请查看结果，确认结果无误后，按任意键继续..."
read -k 1 -s
echo "\n\r"
pkill -f turtle
echo "请先在另一终端运行服务端，确定服务端已经启动后，按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "执行第一次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第二次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第三次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第四次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第五次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第六次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第七次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第八次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第九次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
echo "执行第十次服务调用...\n\r"
ros2 service call /turtle_command std_srvs/srv/Trigger {} >> /dev/null 2> /dev/null
echo "\n\r"
pkill -f turtle
echo "服务端测试结束，按任意键继续..."
read -k 1 -s
echo "\n\r"

echo "现在测试自定义服务的请求和服务端，服务端将在另一个终端中运行...\n\r"
echo "请先在另一终端运行服务端，确定服务端已经启动后，按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "执行自定义服务的请求...\n\r"
echo "执行第一次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第二次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第三次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第四次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第五次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第六次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第七次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第八次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第九次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "执行第十次请求...\n\r"
ros2 run learning_service person_client
echo "\n\r"
echo "请求测试结束，按任意键继续..."
read -k 1 -s
echo "\n\r"

pkill -f person
pkill -f python3
