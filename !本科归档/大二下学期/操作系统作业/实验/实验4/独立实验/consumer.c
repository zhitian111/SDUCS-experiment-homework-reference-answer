#include "common.h"

int run(int type)
{
  // if (shm_ptrs[0] == 0 || shm_ptrs[1] == 0 || shm_ptrs[2] == 0)
  // {
  //   printf("共享内存未初始化！");
  //   return -1;
  // }
  iniSharedMemory();
  iniSemaphore();
  // char buf[1];
  // readForPaper(buf, sizeof(buf));
  // printf("从共享内存中接收到了字符: %c\n", buf[0]);
  consumerRun(type);
  return 0;
}

int main(int argc, char* argv[])
{
  int type = 1;
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-t") == 0)
    {
      type = atoi(argv[i + 1]);
    }
    // if (strcmp(argv[i], "-i") == 0)
    // {
    //
    // }
  }
  run(type);
  return 0;
}
