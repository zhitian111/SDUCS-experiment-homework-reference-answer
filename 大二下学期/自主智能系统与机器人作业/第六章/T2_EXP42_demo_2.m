clc; clear; close all;


ml1=Link([0,0.4967,0,0,0],'modified');
ml2=Link([-pi/2,-0.18804,0.2,3*pi/2,0],'modified');
ml3=Link([0,0.17248,0.79876,0,0],'modified');
ml4=Link([0,0.98557,0.25126,3*pi/2,0],'modified');
ml5=Link([0,0,0,pi/2,0],'modified');
ml6=Link([0,0,0,pi/2,0],'modified');
robot=SerialLink([ml1,ml2,ml3,ml4,ml5,ml6],'name','Fanuc M20ia');
%末端初始状态
p1=[
0.617222144 0.465154659 -0.634561241 -0.254420286 
-0.727874557 0.031367208 -0.684992502 -1.182407321
-0.298723039 0.884673523 0.357934776 -0.488241553
0 0 0 1
];
%末端最后状态
p2=[
    -0.504697849 -0.863267623 0.007006569 0.664188571
    -0.599843651 0.356504321 -0.716304589 -0.35718173
    0.620860432 -0.357314539 -0.697752567 2.106929688
    0 0 0 1
];
step=40;
Tc=ctraj(p1,p2,step);
subplot(3,3,[1,4,7]);
q=zeros(step,6);
for i =1:step
    q(i,:)=robot.ikine(Tc(:,:,i));
end 
robot.plot(q);
qd=zeros(step-1,6)
for i =2:step
    qd(i,1)=q(i,1)-q(i-1,1)
    qd(i,2)=q(i,2)-q(i-1,2)
    qd(i,3)=q(i,3)-q(i-1,3)
    qd(i,4)=q(i,4)-q(i-1,4)
    qd(i,5)=q(i,5)-q(i-1,5)
    qd(i,6)=q(i,6)-q(i-1,6)
end 
qdd=zeros(step-2,6);
for i =2:step-1
    qdd(i,1)=qd(i,1)-qd(i-1,1);
    qdd(i,2)=qd(i,2)-qd(i-1,2);
    qdd(i,3)=qd(i,3)-qd(i-1,3);
    qdd(i,4)=qd(i,4)-qd(i-1,4);
    qdd(i,5)=qd(i,5)-qd(i-1,5);
    qdd(i,6)=qd(i,6)-qd(i-1,6);
end 
subplot(3,3,2);
i=1:6;
    plot(q(:,i));
title("初始位置 各关节角度随时间的变化 目标位置")
grid on;
subplot(3,3,5)
i=1:6;
    plot(qd(:,i));
title('各关节角速度随时间的变化')
subplot(3,3,8);
i=1:6;
    plot(qdd(:,i));
title('各关节加速度随时间变化');
grid on;
subplot(3,3,3)
hold on;
grid on;
title("末端执行器在三位空间的变化")
for i=1:step
    plot3(Tc(1,4,i),Tc(1,4,i),Tc(1,4,i),'b.','MarkerSize',5);
end 

subplot(3,3,6)
hold on;
grid on;
title('末端执行器速度大小随时间的变化')
vel_velocity=zeros(step,1)
for i=2:step
    vel_velocity(i)=sqrt((Tc(1,4,i)-Tc(1,4,i-1))^2+(Tc(2,4,i)-Tc(2,4,i-1))^2+(Tc(3,4,i)-Tc(3,4,i-1))^2)
end 
x=linspace(1,step,step)
plot(x,vel_velocity)

subplot(3,3,9)
hold on 
grid on 
title('末端执行器加速度大小随时间的变化')
vel_acceleration=zeros(step-2,1);
for i=3:step
    vel_acceleration(i-2)=sqrt((Tc(1,4,i)-Tc(1,4,i-1)-(Tc(1,4,i-1)-Tc(1,4,i-2)))^2+(Tc(2,4,i)-Tc(2,4,i-1)-(Tc(2,4,i-1)-Tc(2,4,i-2)))^2+(Tc(3,4,i)-Tc(3,4,i-1)-(Tc(3,4,i-1)-Tc(3,4,i-2)))^2);
end 
x=linspace(1,step-2,step-2);
plot(x,vel_acceleration);