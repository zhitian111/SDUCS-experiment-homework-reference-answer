#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void fx(int*);
void fy(int*);
void fxy(int*);

int calculate_fx(int num);
int calculate_fy(int num);

int pipe_xy_to_x[2], pipe_x_to_xy[2], pipe_y_to_xy[2], pipe_xy_to_y[2];
pthread_t thrd_xy, thrd_x, thrd_y;



int main()
{
    int num1 = 1, num2 = 2, num3 = 3;
    int x, y;
    x = 1;
    y = 1;
    printf("x = ");
    scanf("%d", &x);
    printf("y = ");
    scanf("%d", &y);
    int for_thrd_xy[3] = { num1, x, y };
    int for_thrd_x[2] = { num2, x };
    int for_thrd_y[2] = { num3, y };

    if (pipe(pipe_x_to_xy) < 0)
    {
        perror("pipe_x_to_xy create failed");
    }
    if (pipe(pipe_y_to_xy) < 0)
    {
        perror("pipe_y_to_xy create failed");
    }
    if (pipe(pipe_xy_to_x) < 0)
    {
        perror("pipe_xy_to_x create failed");
    }
    if (pipe(pipe_xy_to_y) < 0)
    {
        perror("pipe_xy_to_y create failed");
    }


    if (pthread_create(&thrd_xy, NULL, (void*)fxy, (void*)for_thrd_xy))
    {
        perror("pthread_create thrd_xy failed");
    }
    if (pthread_create(&thrd_x, NULL, (void*)fx, (void*)&for_thrd_x))
    {
        perror("pthread_create thrd_x failed");
    }
    if (pthread_create(&thrd_y, NULL, (void*)fy, (void*)&for_thrd_y))
    {
        perror("pthread_create thrd_y failed");
    }

    pthread_join(thrd_xy, NULL);
    pthread_join(thrd_x, NULL);
    pthread_join(thrd_y, NULL);
    return EXIT_SUCCESS;
}

void fxy(int* num)
{
    int x, y, id;
    id = num[0];
    x = num[1];
    y = num[2];

    write(pipe_xy_to_x[1], &x, sizeof(int));
    write(pipe_xy_to_y[1], &y, sizeof(int));

    int ans_x, ans_y;
    read(pipe_x_to_xy[0], &ans_x, sizeof(int));
    read(pipe_y_to_xy[0], &ans_y, sizeof(int));
    printf("thread %d calculate fxy(%d,%d) = %d\n", id, x, y, ans_x + ans_y);
    close(pipe_x_to_xy[0]);
    close(pipe_x_to_xy[1]);
    close(pipe_y_to_xy[0]);
    close(pipe_y_to_xy[1]);
    close(pipe_xy_to_x[0]);
    close(pipe_xy_to_x[1]);
    close(pipe_xy_to_y[0]);
    close(pipe_xy_to_y[1]);
}


void fx(int* num)
{
    int x, id;
    id = num[0];
    // x = num[1];
    // read(pipe_xy_to_x[0], &x, sizeof(int));
    if (read(pipe_xy_to_x[0], &x, sizeof(int)) == -1)
    {
        perror("fx read failed");
        exit(EXIT_FAILURE);
    }
    printf("x=%d\n", x);
    int ans = calculate_fx(x);
    printf("thread %d calculate fx(%d) = %d\n",id,x,ans);
    write(pipe_x_to_xy[1], &ans, sizeof(int));
}

void fy(int* num)
{
    int y, id;
    id = num[0];
    // y = num[1];
    if (read(pipe_xy_to_y[0], &y, sizeof(int)) == -1)
    {
        perror("fy read failed");
        exit(EXIT_FAILURE);
    }
    printf("y=%d\n", y);
    int ans = calculate_fy(y);
    printf("thread %d calculate fy(%d) = %d\n",id,y,ans);
    write(pipe_y_to_xy[1], &ans, sizeof(int));
}

int calculate_fx(int num)
{
    if (num == 1)
    {
        return 1;
    }
    if (num > 1)
    {
        return calculate_fx(num - 1) * num;
    }
}

int calculate_fy(int num)
{
    if (num == 1 || num == 2)
    {
        return 1;
    }
    if (num > 2)
    {
        return calculate_fy(num - 1) + calculate_fy(num - 2);
    }
}