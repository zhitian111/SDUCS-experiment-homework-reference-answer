clc; clear; close all;

T = transl(0,10,5)

F = [ 0.527, -0.574, 0.628, 5;...
      0.369,  0.819, 0.439, 3;...
     -0.766,      0, 0.643, 8;... 
          0,      0,     0, 1]

F_T = T * F

tranimate(F,F_T)