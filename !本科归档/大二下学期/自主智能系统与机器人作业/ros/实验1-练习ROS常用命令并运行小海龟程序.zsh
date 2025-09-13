#!/bin/zsh
source ./ros2ini.zsh
ros2 run turtlesim turtlesim_node&
ros2 run turtlesim turtle_teleop_key
pkill -f turtlesim_node
