clc; clear; close all;

% (a)
T = trotz(90) * trotx(90) * transl(0,0,3) * transl(0,5,0)

% (b)
P = [   1;
        5;
        4;
        1   ]


F = [1 0 0 P(1);
     0 1 0 P(2);
     0 0 1 P(3);
     0 0 0 1];

F_tem = trotx(90) * F

tranimate(F,F_tem)
F = F_tem

F_tem = F * transl(0,0,3)
hold on
tranimate(F,F_tem)
F = F_tem

F_tem = trotz(90) * F
hold on
tranimate(F,F_tem)
F = F_tem

F_tem = F * transl(0,5,0)
hold on
tranimate(F,F_tem)
F = F_tem


P_transformed = T * P