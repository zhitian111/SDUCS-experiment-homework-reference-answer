#!/usr/bin/zsh
source /opt/ros/jazzy/setup.zsh
cd ~/catkin_ws
source ./install/setup.zsh

echo "由于实验特性，请先在另一个终端中运行实验6测试用脚本，然后按任意键继续..."
read -k 1 -s
echo "\n\r"
echo "现在生成第二个小海龟...\n\r"
ros2 run learning_service turtle_spawn
echo "\n\r"
echo "请查看结果，确认第二个海龟生成后，按任意键继续..."
read -k 1 -s
echo "\n\r"

# 修改：使用现有的topic发布方式实现运动控制
echo "现在进入海龟运动控制测试...\n\r"
echo "海龟运动控制指令说明："
echo "输入 's' - 让海龟开始圆周运动"
echo "输入 'x' - 让海龟停止运动"
echo "输入 'q' - 退出运动控制测试"
echo "\n\r"

MOTION_PID=""

while true; do
    echo "请输入控制指令 (s:开始, x:停止, q:退出): "
    read -k 1 -s user_input
    echo "\n\r"
    
    case $user_input in
        "s"|"S")
            if [ -z "$MOTION_PID" ] || ! kill -0 $MOTION_PID 2>/dev/null; then
                echo "发送开始运动指令..."
                # 使用ros2 topic pub发布连续运动命令
                ros2 topic pub /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}" -r 10 >>/dev/null &
                MOTION_PID=$!
                echo "海龟开始圆周运动 (PID: $MOTION_PID)..."
            else
                echo "海龟已经在运动中..."
            fi
            ;;
        "x"|"X")
            if [ ! -z "$MOTION_PID" ] && kill -0 $MOTION_PID 2>/dev/null; then
                echo "发送停止运动指令..."
                kill $MOTION_PID 2>/dev/null
                # 发布停止命令
                ros2 topic pub -1 /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}" >>/dev/null
                MOTION_PID=""
                echo "海龟停止运动..."
            else
                echo "海龟当前没有在运动..."
            fi
            ;;
        "q"|"Q")
            echo "退出运动控制测试..."
            # 清理运动进程
            if [ ! -z "$MOTION_PID" ] && kill -0 $MOTION_PID 2>/dev/null; then
                kill $MOTION_PID 2>/dev/null
                ros2 topic pub -1 /turtle1/cmd_vel geometry_msgs/Twist "{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}" >>/dev/null
            fi
            break
            ;;
        *)
            echo "无效指令，请重新输入 (s:开始, x:停止, q:退出)"
            ;;
    esac
done

echo "运动控制测试结束，按任意键继续执行服务调用测试..."
read -k 1 -s
echo "\n\r"

# 原有的服务调用测试
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