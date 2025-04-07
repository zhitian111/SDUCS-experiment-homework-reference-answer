#include "common.h"

int run(int timer)
{
  if (iniSharedMemory() == -1)
  {
    perror("初始化共享内存失败");
    return -1;
  }
  for (int i = 0; i < 26; i++)
  {
    char c = 'a' + i;
    writeForPaper(&c, sizeof(char));
    printf("向共享内存写入%c\n", c);
    sleep(timer);
  }
  freeAllSharedMemory();
  return 0;
}

int main(int argc, char const* argv[])
{
  int timer = 1;
  if (argc > 1)
  {
    timer = atoi(argv[1]);
  }
  run(timer);
  return 0;
}
