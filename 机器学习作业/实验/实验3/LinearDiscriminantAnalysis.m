%% 清空环境变量
clear; 
clc;

%% 加载数据
redPoints = load('ex3Data/ex3red.dat');    % 红色点
bluePoints = load('ex3Data/ex3blue.dat');  % 蓝色点
greenPoints = load('ex3Data/ex3green.dat');% 绿色点

%% 绘制数据点
figure;
plot(redPoints(:, 1), redPoints(:, 2), 'r.', 'MarkerSize', 15);
axis equal;
hold on;
plot(bluePoints(:, 1), bluePoints(:, 2), 'b.', 'MarkerSize', 15);
% plot(greenPoints(:, 1), greenPoints(:, 2), 'g.', 'MarkerSize', 15);
xlabel('x');
ylabel('y');

%% 二分类LDA

% disp(redPoints);

mu0 = mean(redPoints);
mu1 = mean(bluePoints);

sum0 = cov(redPoints - mu0);
sum1 = cov(bluePoints - mu1);

sum_w = sum0+sum1;


w = inv(sum_w)*(mu0-mu1)';
% disp(w);
x = linspace(-5,15);
y = x * (w(2)/w(1));
plot(x,y,'k-');
for i = 1:size(redPoints, 1)
    m = w(2) / w(1);
    b = 0;
    x0 = redPoints(i, 1);
    y0 = redPoints(i, 2);
    x1 = (m * (y0 - b) + x0) / (m^2 + 1);
    y2 = (m^2 * y0 + m * x0 + b) / (m^2 + 1);
    plot([x0 x1], [y0 y2], 'r-');
end

for i = 1:size(bluePoints, 1)
    m = w(2) / w(1);
    b = 0;
    x0 = bluePoints(i, 1);
    y0 = bluePoints(i, 2);
    x1 = (m * (y0 - b) + x0) / (m^2 + 1);
    y2 = (m^2 * y0 + m * x0 + b) / (m^2 + 1);
    plot([x0 x1], [y0 y2], 'b-');
end

%% 多分类LDA

figure;
plot(redPoints(:, 1), redPoints(:, 2), 'r.', 'MarkerSize', 15);
axis equal;
hold on;
plot(bluePoints(:, 1), bluePoints(:, 2), 'b.', 'MarkerSize', 15);
plot(greenPoints(:, 1), greenPoints(:, 2), 'g.', 'MarkerSize', 15);
xlabel('x');
ylabel('y');

mu = mean([bluePoints;redPoints;greenPoints]);
disp(mu);

sb = size(bluePoints, 1) * cov(mean(bluePoints) - mu) + size(greenPoints, 1) * cov(mean(greenPoints) - mu) + size(redPoints, 1) * cov(mean(redPoints) - mu);

sw = cov(bluePoints - mean(bluePoints)) + cov(greenPoints - mean(greenPoints)) + cov(redPoints - mean(redPoints));

S = inv(sw) * sb;

[eigvecs, eigvals] = eig(S);
disp(eigvecs);
disp(eigvals);

max_eigval = max(diag(eigvals));
[~, idx] = max(diag(eigvals));
max_eigvec = eigvecs(:, idx);

disp(max_eigval);
disp(max_eigvec);

unit_max_eigvec = max_eigvec / norm(max_eigvec);

x = linspace(-5,15);
y = x * (unit_max_eigvec(2)/unit_max_eigvec(1));
plot(x,y,'k-');
for i = 1:size(redPoints, 1)
    m = unit_max_eigvec(2) / unit_max_eigvec(1);
    b = 0;
    x0 = redPoints(i, 1);
    y0 = redPoints(i, 2);
    x1 = (m * (y0 - b) + x0) / (m^2 + 1);
    y2 = (m^2 * y0 + m * x0 + b) / (m^2 + 1);
    plot([x0 x1], [y0 y2], 'r-');
end

for i = 1:size(bluePoints, 1)
    m = unit_max_eigvec(2) / unit_max_eigvec(1);
    b = 0;
    x0 = bluePoints(i, 1);
    y0 = bluePoints(i, 2);
    x1 = (m * (y0 - b) + x0) / (m^2 + 1);
    y2 = (m^2 * y0 + m * x0 + b) / (m^2 + 1);
    plot([x0 x1], [y0 y2], 'b-');
end

for i = 1:size(greenPoints, 1)
    m = unit_max_eigvec(2) / unit_max_eigvec(1);
    b = 0;
    x0 = greenPoints(i, 1);
    y0 = greenPoints(i, 2);
    x1 = (m * (y0 - b) + x0) / (m^2 + 1);
    y2 = (m^2 * y0 + m * x0 + b) / (m^2 + 1);
    plot([x0 x1], [y0 y2], 'g-');
end