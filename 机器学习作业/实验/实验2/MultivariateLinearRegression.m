%% 清空工作区
clc;
clear;
format long g;
%% 声明全局变量
% global x;
% global y;
global theta;
global alpha;
global num_iterations;
theta = zeros(3,1);
num_iterations = 50;
alpha = 0.07;

%% 加载数据集
x = load("ex2Data/ex2x.dat");
y = load("ex2Data/ex2y.dat");
% disp(x);
% disp(y);


%% 数据标准化
m = size(x, 1);
x = [ones(m,1),x];
% disp(x);

sigma = std(x);
mu = mean(x);
% disp(sigma);
% disp(mu);
x(:,2) = (x(:,2) - mu(2))./sigma(2);
x(:,3) = (x(:,3) - mu(3))./sigma(3);

%% 梯度下降

% J_figure_disp(x,y,theta);
% learning_rate_compare(x,y);
% training(x,y);
% disp(theta);

% theta_normal(x,y);
training(x,y);
disp(theta);
test_data = [1,1650,3];
normal_test_data = [1,1650,3];

normal_test_data(2) = (test_data(2) - mu(2))./sigma(2);
normal_test_data(3) = (test_data(3) - mu(3))./sigma(3);
disp(h(normal_test_data));
%% h(x)

function result = h(x)
    global theta;
    result = x * theta;
end

%% gradientDecent
function result = gradientDecent(x, y)
    global theta;
    global alpha;
    m = size(x, 1);
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    for i = 1:m
        sum1 = sum1 + (h(x(i,:)) - y(i,:))*x(i,1);
        sum2 = sum2 + (h(x(i,:)) - y(i,:))*x(i,2);
        sum3 = sum3 + (h(x(i,:)) - y(i,:))*x(i,3);
    end
    sum1 = sum1 / m;
    sum2 = sum2 / m;
    sum3 = sum3 / m;
    theta(1) = theta(1) - alpha * sum1;
    theta(2) = theta(2) - alpha * sum2;
    theta(3) = theta(3) - alpha * sum3;
end

%% J(θ)

function result = J(x,y)
    sum = 0;
    for i = 1:size(x,1)
        sum = sum + (h(x(i,:)) - y(i,:))^2;
    end
    result = sum / (2*size(x,1));
end

%% training
function result = training(x,y)
    global num_iterations;
    for i = 1:num_iterations
        gradientDecent(x, y);  
    end
end

%% J_figure_disp
function J_figure_disp(x,y,theta)
    global num_iterations;
    J_vals = zeros(num_iterations,1);
    for i = 1:num_iterations
        J_vals(i) = J(x,y);
        gradientDecent(x, y);
    end
    figure;
    plot(0:49,J_vals(1:50),'-');
    xlabel('Number of iterations');
    ylabel('Cost J');


end

%% learning_rate_compare
function learning_rate_compare(x,y)
    global alpha;
    global num_iterations;
    global theta;
    figure;
    alpha_vals = [0.07,0.1,1];
    alpha = 0.07;
    theta = zeros(3,1);
    J_vals = zeros(num_iterations,1);
    for i = 1:num_iterations
        J_vals(i) = J(x,y);
        gradientDecent(x, y);
    end    
    plot(0:49,J_vals(1:50),'-');

    hold on;

    J_vals = zeros(num_iterations,1);
    theta = zeros(3,1);
    alpha = alpha_vals(1);
    for i = 1:num_iterations
        J_vals(i) = J(x,y);
        gradientDecent(x, y);
    end
    plot(0:49,J_vals(1:50),'b-');


    J_vals = zeros(num_iterations,1);
    theta = zeros(3,1);
    alpha = alpha_vals(2);
    for i = 1:num_iterations
        J_vals(i) = J(x,y);
        gradientDecent(x, y);
    end
    plot(0:49,J_vals(1:50),'r-');


    J_vals = zeros(num_iterations,1);
    theta = zeros(3,1);    
    alpha = alpha_vals(3);
    for i = 1:num_iterations
        J_vals(i) = J(x,y);
        gradientDecent(x, y);
    end
    plot(0:49,J_vals(1:50),'k-');

    xlabel('Number of iterations');
    ylabel('Cost J');

end

%% 正规方程求theta
function theta_normal(x,y)
    global theta;
    theta = inv((x'*x))*(x'*y);
end    