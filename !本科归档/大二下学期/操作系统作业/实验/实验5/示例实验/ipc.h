/*
*Filename: ipc.h
*copyright: (C) 2006 by zhonghonglie
* Function
: 声明 IPC 机制的函数原型和全局变量
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
#define BUFSZ 256
#define MAXVAL 100
#define STRSIZ 8
#define WRITERQUEST 1
#define READERQUEST 2
#define FINISHED 3
/*信号量控制用的共同体*/
typedef union semuns
{
    int val;
} Sem_uns;

// 读写完成标识
/* 消 息 结 构 体 */
typedef struct msgbuf
{
    long mtype;
    int mid;
} Msg_buf;


extern key_t buff_key;
extern int buff_num;
extern char *buff_ptr;
extern int shm_flg;
extern int quest_flg;
extern key_t quest_key;
extern int quest_id;
extern int respond_flg;
extern key_t respond_key;
extern int respond_id;



int get_ipc_id(char *proc_file, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);