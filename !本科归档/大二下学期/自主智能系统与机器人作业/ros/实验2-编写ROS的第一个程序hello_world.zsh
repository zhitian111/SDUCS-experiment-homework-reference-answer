#!/bin/zsh
cd ~/catkin_ws
source ./install/setup.zsh
ros2 run hello_world hello_node
./src/hello_world/script/hello.py
