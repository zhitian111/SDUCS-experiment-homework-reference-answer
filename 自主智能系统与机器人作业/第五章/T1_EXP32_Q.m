clc; clear; close all;

% 加载 puma560 机器人模型
mdl_puma560;
% 创建 SerialLink 对象
p560 = SerialLink(p560);

% 定义新的关节角度
q = [pi/6, -pi/6, pi/3, -pi/3, pi/4, -pi/4];

% 正运动学求解
T = fkine(p560, q);
disp('正运动学得到的末端位姿齐次变换矩阵 T:');
disp(T);

% 逆运动学求解
qi = ikine(p560, T);
disp('逆运动学求解得到的关节角度 qi:');
disp(qi);

% 对比原始关节角度和逆运动学求解结果
disp('原始关节角度 q:');
disp(q);

% 使用 trplot 绘制末端位姿
figure;
trplot(T, 'frame', 'T', 'color', 'b');
title('末端执行器位姿');    