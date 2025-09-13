clc; clear; close all;

P = [2;3;4]

F = [1 0 0 P(1);
     0 1 0 P(2);
     0 0 1 P(3);
     0 0 0 1];

T = rotx(90)

T_r = trotx(90)

P_rotated = T*P

F_rotated = T_r*F

tranimate(F,F_rotated)