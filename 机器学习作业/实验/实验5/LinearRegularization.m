%% 清空工作区
clc;clear;close all;

%% 加载数据
x = load('ex5Data/ex5Linx.dat')
y = load('ex5Data/ex5Liny.dat')

%% 绘制数据

plot(x,y,'r.','MarkerSize',20)

hold on
% 构造x的多项式特征

new_x = ones(size(x,1),1);
disp(size(x,1))
for i = 1:size(x,1) - 1
    new_x = [new_x x.^i];
end
x = new_x

lambda = 10

tem = eye(size(x,2))
tem(1) = 0
theta = inv(x'*x + lambda*tem)*x'*y
% 绘制拟合曲线
i = linspace(-1,1,100);
j = h(theta,i);
plot(i,j,'b--')
hold off
%% 函数部分

% h(x)

function hx = h(theta,x)
    m = size(theta,1);
    sum = 0;
    for i = 0:m - 1
        sum = sum + theta(i+1)*(x.^i);
    end
    hx = sum;
end

% J(theta,x,y,lambda)

function J = J(theta,x,y,lambda)
    m = size(x,1);
    J = (1/2)*sum((h(theta,x)-y).^2) + (lambda/(2*m))*sum(theta(2:end).^2);
end
