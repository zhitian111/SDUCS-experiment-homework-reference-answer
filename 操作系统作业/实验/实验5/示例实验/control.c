#include "ipc.h"
#include <stdio.h>
key_t buff_key;
int buff_num;
char* buff_ptr;
int shm_flg;
int quest_flg;
key_t quest_key;
int quest_id;
int respond_flg;
key_t respond_key;
int respond_id;
int main(int argc, char* argv[])
{
  int i;
  int rate;
  int w_mid;
  int count = MAXVAL;
  Msg_buf msg_arg;
  struct msqid_ds msg_inf;
  // 建立一个共享内存先写入一串 A 字符模拟要读写的内容
  buff_key = 101;
  buff_num = STRSIZ + 1;
  shm_flg = IPC_CREAT | 0644;
  buff_ptr = (char*)set_shm(buff_key, buff_num, shm_flg);
  for (i = 0; i < STRSIZ; i++)
    buff_ptr[i] = 'A';
  buff_ptr[i] = '\0';
  // 建立一条请求消息队列
  quest_flg = IPC_CREAT | 0644;
  quest_key = 201;
  quest_id = set_msq(quest_key, quest_flg);
  // 建立一条响应消息队列
  respond_flg = IPC_CREAT | 0644;
  respond_key = 202;
  respond_id = set_msq(respond_key, respond_flg);
  // 控制进程准备接收和响应读写者的消息
  printf("Wait quest \n");
  fflush(stdout);
  while (1)
  {
    // 当 count 大于 0 时说明没有新的读写请求，查询是否有任何新请求
    if (count > 0)
    {
      quest_flg = IPC_NOWAIT; // 以非阻塞方式接收请求消息
      if (msgrcv(quest_id, &msg_arg, sizeof(msg_arg), FINISHED, quest_flg) >= 0)
      {
        // 有读者完成
        count++;
        printf("%d reader finished\n", msg_arg.mid);
        fflush(stdout);
      }
      else if (msgrcv(quest_id, &msg_arg, sizeof(msg_arg), READERQUEST,
                      quest_flg) >= 0)
      {
        // 有读者请求，允许读者读
        count--;
        msg_arg.mtype = msg_arg.mid;
        msgsnd(respond_id, &msg_arg, sizeof(msg_arg), 0);
        printf("%d quest read\n", msg_arg.mid);
        fflush(stdout);
      }
    }
    // 当 count 等于 0 时说明写者正在写，等待写完成
    if (count == 0)
    {
      // 以阻塞方式接收消息.
      msgrcv(quest_id, &msg_arg, sizeof(msg_arg), FINISHED, 0);
      count = MAXVAL;
      printf("%d write finished\n", msg_arg.mid);
      fflush(stdout);
      if (msgrcv(quest_id, &msg_arg, sizeof(msg_arg), READERQUEST, quest_flg) >=
          0)
      {
        // 有读者请求，允许读者读
        count--;
        msg_arg.mtype = msg_arg.mid;
        msgsnd(respond_id, &msg_arg, sizeof(msg_arg), 0);
        printf("%d quest read\n", msg_arg.mid);
        fflush(stdout);
      }
    }
  }
  return EXIT_SUCCESS;
}
