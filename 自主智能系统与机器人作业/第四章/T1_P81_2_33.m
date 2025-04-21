% 定义D - H参数
theta = [0 -45 0 0 -45 0]; % 初始关节角度
d = [27 6 0 18 0 0];
a = [0 15 1 0 0 0];
alpha = [-pi/2 0 -pi/2 pi/2 -pi/2 0];
% 创建机器人对象
L(1) = Link([theta(1) d(1) a(1) alpha(1)], 'modified');
L(2) = Link([theta(2) d(2) a(2) alpha(2)], 'modified');
L(3) = Link([theta(3) d(3) a(3) alpha(3)], 'modified');
L(4) = Link([theta(4) d(4) a(4) alpha(4)], 'modified');
L(5) = Link([theta(5) d(5) a(5) alpha(5)], 'modified');
L(6) = Link([theta(6) d(6) a(6) alpha(6)], 'modified');
robot = SerialLink(L, 'name', 'Puma 562');
robot.plot(theta);