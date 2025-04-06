%% 清空工作区
clear;
clc;

%% 全局变量声明
global alpha;
global theta;
alpha = 0.07;       %学习率设置
theta = [0,0];      %参数初始值
sum_times = 1500;   %梯度下降次数

%% 初始数据处理

x = load("ex1Data/ex1x.dat");
y = load("ex1Data/ex1y.dat");

% disp(x);
% disp(y);

figure;
plot(x,y,'o');
ylabel("Height/m");
xlabel("Age/y");

m = length(y);

x = [ones(m,1),x];

pause;
%% 循环进行梯度下降的部分
for times_cnt = 1:sum_times

h_ans = h(x(1,:));
disp(h_ans);

sum_w = 0;
sum_b = 0;
for i = 1:size(x,1)
   sum_w = sum_w + (h(x(i,:)) - y(i)) * x(i,2);
   sum_b = sum_b + (h(x(i,:)) - y(i)) * x(i,1);
end
disp(sum_w);
disp(sum_b);


theta(1) = theta(1) - alpha * sum_b / size(x,1);
theta(2) = theta(2) - alpha * sum_w / size(x,1);
end
% 以上为一次更新

%% 打印参数结果

disp(theta);
fprintf("y = %fx + %f\n",theta(2),theta(1));

%% 检验模型效果
hold on;
plot(x(:,2),h(x),'-');
legend('Training data','Linear regression');

%% 测试预测效果
fprintf("height of boy who has age 3.5: %f m\n",h([1,3.5]));
fprintf("height of boy who has age 7  : %f m\n",h([1,7  ]));

J_vals = zeros(100,100);
theta0_vals = linspace(-3,3,100);
theta1_vals = linspace(-1,1,100);
for i = 1:length(theta0_vals)
    for j = 1:length(theta1_vals)
        t = [theta0_vals(i);theta1_vals(j)];
        J_vals(i,j) = h_j(x,y,t);
    end
end

J_vals = J_vals';
figure;
surf(theta0_vals,theta1_vals,J_vals);
xlabel('\theta_0');
ylabel('\theta_1');

%% 使用 linspace 绘制等高线图
figure;
contour(theta0_vals, theta1_vals, J_vals, linspace(0, 30, 20));
xlabel('\theta_0');
ylabel('\theta_1');
title('Contour plot of J(\theta)');
%% 使用 logspace 绘制等高线图
% 使用 logspace 生成等高线的值范围
figure;
contour(theta0_vals, theta1_vals, J_vals, logspace(-3, 1.5, 20));
xlabel('\theta_0');
ylabel('\theta_1');
title('Contour plot of J(\theta) using logspace');

%% 模型使用的函数

function result = h(x)
global theta;
% sum = 0;
% 
% for i = 1:size(x,1)
%     sum = sum + theta .* x(i,:);
% end


result = theta * x';

end
%% 构造J平面使用的函数

function result = h_j(x,y,tem_theta)
sum_j = 0;
% sum_b = 0;
% disp(tem_theta);
% disp(x(1,:));
% disp(x(1,:)*tem_theta);
% disp([1.0,2.0]*[-3;-1]);
for i = 1:size(x,1)
   sum_j = sum_j + ((x(i,:) * tem_theta) - y(i)) * ((x(i,:) * tem_theta) - y(i));
end
% disp(sum_w);
% disp(sum_b);
% sum_w = sum_w / size(x,1);
% sum_b = sum_b / size(x,1);
result = sum_j / size(x,1);
end