#!/usr/bin/zsh
source /opt/ros/jazzy/setup.zsh
echo "按任意键开始实验..."
read -k 1 -s
echo "\n\r"
echo "即将开始实验1-练习ROS常用命令并运行小海龟程序...\n\r"
./实验1-练习ROS常用命令并运行小海龟程序.zsh
echo "按任意键进行下一个实验..."
read -k 1 -s
echo "\n\r"
echo "即将开始实验2-编写ROS的第一个程序hello_world...\n\r"
./实验2-编写ROS的第一个程序hello_world.zsh
echo "按任意键进行下一个实验..."
read -k 1 -s
echo "\n\r"
echo "即将开始实验3-ROS话题通信实验...\n\r"
./实验3-ROS话题通信实验.zsh
echo "按任意键进行下一个实验..."
read -k 1 -s
echo "\n\r"
echo "即将开始实验4-ROS服务通信实验...\n\r"
./实验4-ROS服务通信实验.zsh
echo "按任意键进行下一个实验..."
read -k 1 -s
echo "\n\r"
echo "即将开始实验5-自定义消息的发布和订阅实验...\n\r"
./实验5-自定义消息的发布和订阅.zsh
echo "按任意键进行下一个实验..."
read -k 1 -s
echo "\n\r"
echo "即将开始实验6-自定义服务的请求和服务实验...\n\r"
./实验6-自定义服务的请求和服务.zsh
echo "\033[32m实验结束!!!\n\r\033[0m"
