%% 清空工作区
clc;clear;close all;

%% 加载数据

x = load('ex5Data/ex5Logx.dat')
y = load('ex5Data/ex5Logy.dat')

figure

pos = find(y)
neg = find(y==0)
plot(x(pos,1),x(pos,2),'+')
hold on
plot(x(neg,1),x(neg,2),'o')
% hold off

new_x = map_feature(x(:,1),x(:,2))

theta = ones(size(new_x,2),1)

lambda = 10


% disp(train(new_x,y,lambda))
% dis = dJ(new_x,y,theta,lambda)
% dis = H(theta,new_x,y,lambda)
% disp(inv(dis))
theta = train(new_x,y,lambda)
u = linspace(-1,1.5,200)
v = linspace(-1,1.5,200)
z = zeros(length(u),length(v))
for i = 1:length(u)
    for j = 1:length(v)
        z(i,j) = map_feature([u(i)],[v(j)])*theta;
    end
end

contour(u,v,z',[0,0],'LineWidth',2);

%% 函数部分
% h(x)

function hx = h(theta,x)
    % 计算sigmoid函数值
    hx = 1./(1+exp(-(x*theta)));
    % disp("hx=")
    % disp(hx)
end

% J(x)
function J = J(theta,x,y,lambda)
    m = size(x,1);
    sum = 0;
    for i = 1:m
        sum = sum - y(i)*log(h(theta,x(i,:))) - (1-y(i))*log(1-h(theta,x(i,:)));
    end
    J = sum / m + (lambda/(2*m))*(theta'*theta);
end
% dJ(x)
function dJ = dJ(x,y,theta,lambda)
    m = size(theta,1);
    n = size(x,1);
    sum = 0;
    for k = 1:size(x,1)
        sum = sum + (h(theta,x(k,:)) - y(k)).*x(k,1);
    end
    dJ = sum / n;
    sum = 0;
    for j = 2:size(x,2)
        for k = 1:size(x,1)
            sum = sum + (h(theta,x(k,:)) - y(k)).*x(k,j);
        end
        sum = sum / n
        sum = sum + (lambda/n)*theta(j);
        dJ = [dJ;sum];
        sum = 0
    end
    % disp("dJ")
    % disp(dJ)
end
% has(x)
function H = H(theta,x,y,lambda)
    m = size(x,1);
    sum = 0;
    for i = 1:m
        sum = sum + h(theta,x(i,:))*(1-h(theta,x(i,:)))*(x(i,:)')*x(i,:)
        % disp('h(theta,x(i,:))*(1-h(theta,x(i,:)))')
        % disp(h(theta,x(i,:))*(1-h(theta,x(i,:))))
    end
    sum = sum / m
    tem = eye(size(theta,1))
    tem(1,1) = 0;
    H = sum + (lambda/m)*tem
end


function result = train(x,y,lambda)
    theta = zeros(size(x,2),1)
    % disp("theta0")
    % disp(theta)
    J_his = []
    for i = 1:15
        J_his = [J_his,J(theta,x,y,lambda)];
        theta = theta - inv(H(theta,x,y,lambda))*dJ(x,y,theta,lambda);
    end
    result = theta
    disp(J_his)
end