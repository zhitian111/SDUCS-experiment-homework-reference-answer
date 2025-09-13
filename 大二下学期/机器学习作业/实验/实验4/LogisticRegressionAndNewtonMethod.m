%% 清空工作区
clc; clear; close all;
%% 加载数据

x = load('ex4Data/ex4x.dat')
y = load('ex4Data/ex4y.dat')

% disp(x)
% disp(y)
x = [ones(size(x,1),1) x];
pos = find(y==1);
neg = find(y==0);
figure;
plot(x(pos,2),x(pos,3),'+');hold on;
plot(x(neg,2),x(neg,3),'o');

%% 全局变量
global theta;% 参数

%% 计算

theta = zeros(size(x,2),1);
gradientDescent(x,y,15);
disp(theta)
x_l = linspace(0,100,100);
y_l = (-theta(1)-theta(2)*x_l)/theta(3);
plot(x_l,y_l);hold on;

test = [1 20 80];
disp("通过率为")
disp(hx(test))

%% 函数

%% hx
function result = hx(x)
    global theta;
    result = sigmoid(x * theta);
end

%% cost
function J = cost(x,y)
    global theta;
    m = length(y);
    h = hx(x);
    J = (1/m) * (-y' * log(h) - (1 - y)' * log(1 - h));
end

%% gradient decent

function [theta,J_history] = gradientDescent(x,y,num_iters)
    global theta;
    J_history = cost(x,y);
    for i = 1:num_iters
        H = HMatrix(x,y);
        disp(H)
        grad = deltaJ(x,y);
        H = inv(H);
        theta = theta - H*grad;
        J_history = [J_history cost(x,y)]
        if abs(J_history(end) - J_history(end-1)) < 1e-6
            disp("迭代次数");
            disp(i);
            break;
        end
    end
end


% HesMatrix

% 海森矩阵
function H = HMatrix(x, y)
    global theta;
    m = length(y);
    h = sigmoid(x * theta);
    H = zeros(size(theta));
    for i = 1:m
        h_i = h(i);
        x_i = x(i, :);
        H = H + h_i * (1 - h_i) * (x_i' * x_i);
    end
    H = H / m;
end
% ΔJ
function result = deltaJ(x,y)
    global theta;
    m = length(y);
    h = hx(x);
    result = (1/m) * (x' * (h - y));
end

% sigmoid

function result = sigmoid(z)
    result = 1 ./ (1 + exp(-z));
end