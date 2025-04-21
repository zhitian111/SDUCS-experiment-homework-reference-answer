% (a)
T = trotz(90) * trotx(90) * transl(0,0,3) * transl(0,5,0)

% (b)
P = [   1;
        5;
        4;
        1   ]

P_transformed = T * P