#include "common.h"

int run()
{
  if (iniSharedMemory() == -1)
  {
    perror("初始化共享内存失败");
    return -1;
  }
  if (iniSemaphore() == -1)
  {
    perror("初始化信号量失败");
    freeAllSharedMemory();
    return -1;
  }
  producerRun();
  freeAllSharedMemory();
  freeAllSemaphore();
  return 0;
}

int main(int argc, char const* argv[])
{
  int timer = 1;
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-t") == 0)
    {
      timer = atoi(argv[i + 1]);
    }
    // if (strcmp(argv[i], "-i") == 0)
    // {
    //
    // }
  }
  run();
  return 0;
}
