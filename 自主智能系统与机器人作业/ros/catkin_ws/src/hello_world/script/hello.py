#!/usr/bin/env python
#coding:utf-8
import rclpy
import rclpy
from rclpy.node import Node

class MyNode(Node):
    def __init__(self):
        super().__init__('my_node')
        self.get_logger().info('hello ros python')

def main(args=None):
    rclpy.init(args=args)
    node = MyNode()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
