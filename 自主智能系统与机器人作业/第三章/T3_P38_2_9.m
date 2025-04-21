clc; clear; close all;

P = [   7;
        3;
        1;
        1   ]

T = troty(90) * transl(4, -3, 7) * trotz(90)

P_transformed = T * P