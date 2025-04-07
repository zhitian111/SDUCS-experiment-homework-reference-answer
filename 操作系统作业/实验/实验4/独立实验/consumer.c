#include "common.h"

int run()
{
  if (shm_ptrs[0] == 0 || shm_ptrs[1] == 0 || shm_ptrs[2] == 0)
  {
    printf("共享内存未初始化！");
    return -1;
  }
  iniSharedMemory();
  char buf[1];
  readForPaper(buf, sizeof(buf));
  printf("从共享内存中接收到了字符: %c\n", buf[0]);
  return 0;
}

int main()
{
  run();
  return 0;
}
