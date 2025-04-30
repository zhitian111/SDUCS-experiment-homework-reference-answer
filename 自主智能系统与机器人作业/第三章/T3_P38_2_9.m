clc; clear; close all;

P = [   7;
        3;
        1;
        1   ]
F = [1 0 0 P(1);
     0 1 0 P(2);
     0 0 1 P(3);
     0 0 0 1];

T = troty(90) * transl(4, -3, 7) * trotz(90)

F_tem = trotz(90) * F

tranimate(F,F_tem)
hold on
F = F_tem

F_tem = transl(4, -3, 7) * F

tranimate(F,F_tem)
hold on
F = F_tem

F_tem = troty(90) * F

tranimate(F,F_tem)
hold on

P_transformed = T * P