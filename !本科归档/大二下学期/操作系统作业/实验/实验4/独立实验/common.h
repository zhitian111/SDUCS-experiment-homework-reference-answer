#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define SHM_SIZE 1024
#define SHM_MODE 0666 | IPC_CREAT
#define SEM_MODE 0666 | IPC_CREAT
#define SEM_VALUE 1
#define DIVIDER 20
#define PATH "common.h"
#define SLEEP_TIME 1 // 1s
key_t key_for_paper;
key_t key_for_water;
key_t key_for_tobacco;
key_t key_for_producer[3];
key_t key_for_consumer[3];
key_t key_for_paper_cnt;
key_t key_for_water_cnt;
key_t key_for_tobacco_cnt;
int shmids[3] = {0, 0, 0};
void* shm_ptrs[3];
int semids_for_producer[3]; // 表明是否有生产者正在生产
int semids_for_consumer[3]; // 表明是否有消费者正在消费
int semid_for_paper;        // 表明待生产的纸张数量
int semid_for_water;        // 表明待生产的水的数量
int semid_for_tobacco;      // 表明待生产的烟草的数量
int semids_for_paper_cnt;   // 表明纸张的数量
int semids_for_water_cnt;   // 表明水的数量
int semids_for_tobacco_cnt; // 表明烟草的数量
size_t paper_cnt;           // 表明生产总量
size_t water_cnt;           // 表明生产总量
size_t tobacco_cnt;         // 表明生产总量
static inline int createSharedMemory(key_t key, int size)
{
  int shm_id = shmget(key, size, SHM_MODE);
  if (shm_id == -1)
  {
    perror("shmget");
    return -1;
  }
  return shm_id;
}
static inline int getSharedMemory(key_t key, int size)
{
  int shm_id = shmget(key, size, SHM_MODE);
  if (shm_id == -1)
  {
    perror("shmget");
    return -1;
  }
  return shm_id;
}

static inline int iniSharedMemoryID()
{
  shmids[0] = createSharedMemory(key_for_paper, SHM_SIZE);
  shmids[1] = createSharedMemory(key_for_water, SHM_SIZE);
  shmids[2] = createSharedMemory(key_for_tobacco, SHM_SIZE);
  if (shmids[0] == -1 || shmids[1] == -1 || shmids[2] == -1)
  {
    perror("shmget");
    return -1;
  }
  return 0;
}

static inline int getKeys()
{
  key_for_paper = ftok(PATH, 'p');
  key_for_water = ftok(PATH, 'w');
  key_for_tobacco = ftok(PATH, 't');
  if (key_for_paper == -1 || key_for_water == -1 || key_for_tobacco == -1)
  {
    perror("ftok");
    return -1;
  }
  return 0;
}
static inline int matSharedMemory()
{
  shm_ptrs[0] = shmat(shmids[0], NULL, 0);
  shm_ptrs[1] = shmat(shmids[1], NULL, 0);
  shm_ptrs[2] = shmat(shmids[2], NULL, 0);
  if (shm_ptrs[0] == (void*)-1 || shm_ptrs[1] == (void*)-1 ||
      shm_ptrs[2] == (void*)-1)
  {
    perror("shmat");
    return -1;
  }
  return 0;
}
static inline int iniSharedMemory()
{
  if (shmids[0] == 0 || shmids[1] == 0 || shmids[2] == 0)
  {
    if (getKeys() == -1)
    {
      perror("ftok");
      return -1;
    }
  }
  else
  {
    printf("Shared memory already exists.\n");
    return -1;
  }
  if (iniSharedMemoryID() == -1)
  {
    perror("shmget");
    return -1;
  }
  if (matSharedMemory() == -1)
  {
    perror("shmat");
    return -1;
  }
  return 0;
}
static inline int writeSharedMemory(void* shm_ptr, const void* data,
                                    size_t size)
{
  if (size > SHM_SIZE)
  {
    return -1;
  }
  if (shm_ptr == NULL || shm_ptr == (void*)-1 || data == NULL)
  {
    return -1;
  }
  memcpy(shm_ptr, data, size);
  return 0;
}
static inline int writeForPaper(const void* data, size_t size)
{
  return writeSharedMemory(shm_ptrs[0], data, size);
}
static inline int writeForWater(const void* data, size_t size)
{
  return writeSharedMemory(shm_ptrs[1], data, size);
}
static inline int writeForTobacco(const void* data, size_t size)
{
  return writeSharedMemory(shm_ptrs[2], data, size);
}
static inline int readSharedMemory(void* shm_ptr, void* data, size_t size)
{
  if (size > SHM_SIZE)
  {
    return -1;
  }
  if (shm_ptr == NULL || shm_ptr == (void*)-1 || data == NULL)
  {
    return -1;
  }
  memcpy(data, shm_ptr, size);
  return 0;
}
static inline int readForPaper(void* data, size_t size)
{
  return readSharedMemory(shm_ptrs[0], data, size);
}
static inline int readForWater(void* data, size_t size)
{
  return readSharedMemory(shm_ptrs[1], data, size);
}
static inline int readForTobacco(void* data, size_t size)
{
  return readSharedMemory(shm_ptrs[2], data, size);
}
static inline int freeSharedMemory(int shm_id)
{
  if (shmctl(shm_id, IPC_STAT, 0) != 1)
  {
    return 0;
  }
  if (shmctl(shm_id, IPC_RMID, 0) == -1)
  {
    perror("shmctl");
    return -1;
  }
  return 0;
}
static inline int dematSharedMemory()
{
  if (shmdt(shm_ptrs[0]) == -1 || shmdt(shm_ptrs[1]) == -1 ||
      shmdt(shm_ptrs[2]) == -1)
  {
    perror("shmdt");
    return -1;
  }
  return 0;
}
static inline int freeAllSharedMemory()
{
  if (dematSharedMemory() == -1)
  {
    perror("shmdt");
    return -1;
  }
  if (freeSharedMemory(shmids[0]) == -1 || freeSharedMemory(shmids[1]) == -1 ||
      freeSharedMemory(shmids[2]) == -1)
  {
    perror("shmctl");
    return -1;
  }
  return 0;
}
static inline int getSemaphoreKey()
{
  key_for_producer[0] = ftok(PATH, 'P');
  key_for_producer[1] = ftok(PATH, 'W');
  key_for_producer[2] = ftok(PATH, 'T');
  key_for_consumer[0] = ftok(PATH, 'p' + 'P');
  key_for_consumer[1] = ftok(PATH, 'w' + 'W');
  key_for_consumer[2] = ftok(PATH, 't' + 'T');
  key_for_paper_cnt = ftok(PATH, 'c' + 'P');
  key_for_water_cnt = ftok(PATH, 'c' + 'W');
  key_for_tobacco_cnt = ftok(PATH, 'c' + 'T');
  if (key_for_producer[0] == -1 || key_for_producer[1] == -1 ||
      key_for_producer[2] == -1)
  {
    perror("ftok");
    return -1;
  }
  return 0;
}
static inline int getSemaphore(key_t key)
{
  int sem_id = semget(key, SEM_VALUE, SEM_MODE);
  if (sem_id == -1)
  {
    perror("semget");
    return -1;
  }
  return sem_id;
}

static inline int down(int sem_id)
{
  struct sembuf sem[1];
  sem[0].sem_num = 0;
  sem[0].sem_op = -1;
  sem[0].sem_flg = SEM_UNDO;
  if (semop(sem_id, sem, 1) == -1)
  {
    perror("semop");
    return -1;
  }
  return 0;
}

static inline int up(int sem_id)
{
  struct sembuf sem[1];
  sem[0].sem_num = 0;
  sem[0].sem_op = 1;
  sem[0].sem_flg = SEM_UNDO;
  if (semop(sem_id, sem, 1) == -1)
  {
    perror("semop");
    return -1;
  }
  return 0;
}
static inline int iniSemaphore()
{
  if (semids_for_producer[0] == 0 || semids_for_producer[1] == 0 ||
      semids_for_producer[2] == 0 || semids_for_consumer[0] == 0 ||
      semids_for_consumer[1] == 0 || semids_for_consumer[2] == 0 ||
      semids_for_paper_cnt == 0 || semids_for_water_cnt == 0 ||
      semids_for_tobacco_cnt == 0 || semid_for_paper == 0 ||
      semid_for_water == 0 || semid_for_tobacco == 0)
  {
    if (getKeys() == -1)
    {
      perror("ftok");
      return -1;
    }
  }
  else
  {
    printf("Semaphore already exists.\n");
    return -1;
  }
  if (getSemaphoreKey() == -1)
  {
    perror("ftok");
    return -1;
  }
  semids_for_producer[0] = getSemaphore(key_for_producer[0]);
  semids_for_producer[1] = getSemaphore(key_for_producer[1]);
  semids_for_producer[2] = getSemaphore(key_for_producer[2]);
  semid_for_paper = getSemaphore(key_for_paper);
  semid_for_water = getSemaphore(key_for_water);
  semid_for_tobacco = getSemaphore(key_for_tobacco);
  semids_for_consumer[0] = getSemaphore(key_for_consumer[0]);
  semids_for_consumer[1] = getSemaphore(key_for_consumer[1]);
  semids_for_consumer[2] = getSemaphore(key_for_consumer[2]);
  semids_for_paper_cnt = getSemaphore(key_for_paper_cnt);
  semids_for_water_cnt = getSemaphore(key_for_water_cnt);
  semids_for_tobacco_cnt = getSemaphore(key_for_tobacco_cnt);
  if (semids_for_producer[0] == -1 || semids_for_producer[1] == -1 ||
      semids_for_producer[2] == -1)
  {
    perror("semget");
    return -1;
  }
  if (semid_for_paper == -1 || semid_for_water == -1 || semid_for_tobacco == -1)
  {
    perror("semget");
    return -1;
  }
  if (semids_for_consumer[0] == -1 || semids_for_consumer[1] == -1 ||
      semids_for_consumer[2] == -1)
  {
    perror("semget");
    return -1;
  }
  if (semids_for_paper_cnt == -1 || semids_for_water_cnt == -1 ||
      semids_for_tobacco_cnt == -1)
  {
    perror("semget");
    return -1;
  }
  // 初始化生产者
  up(semids_for_producer[0]);
  up(semids_for_producer[1]);
  up(semids_for_producer[2]);
  // 初始化消费者
  up(semids_for_consumer[0]);
  up(semids_for_consumer[1]);
  up(semids_for_consumer[2]);
  return 0;
}

static inline int freeSemaphore(int sem_id)
{
  if (semctl(sem_id, 0, IPC_STAT, 0) != 1)
  {
    return 0;
  }
  if (semctl(sem_id, 0, IPC_RMID, 0) == -1)
  {
    perror("semctl");
    return -1;
  }
  return 0;
}

static inline int freeAllSemaphore()
{
  if (freeSemaphore(semids_for_producer[0]) == -1 ||
      freeSemaphore(semids_for_producer[1]) == -1 ||
      freeSemaphore(semids_for_producer[2]) == -1)
  {
    perror("semctl");
    return -1;
  }
  if (freeSemaphore(semid_for_paper) == -1 ||
      freeSemaphore(semid_for_water) == -1 ||
      freeSemaphore(semid_for_tobacco) == -1)
  {
    perror("semctl");
    return -1;
  }
  if (freeSemaphore(semids_for_consumer[0]) == -1 ||
      freeSemaphore(semids_for_consumer[1]) == -1 ||
      freeSemaphore(semids_for_consumer[2]) == -1)
  {
    perror("semctl");
    return -1;
  }
  if (freeSemaphore(semids_for_paper_cnt) == -1 ||
      freeSemaphore(semids_for_water_cnt) == -1 ||
      freeSemaphore(semids_for_tobacco_cnt) == -1)
  {
    perror("semctl");
    return -1;
  }
  return 0;
}

static inline int produce(int type, void* shm_ptr, void* data, int size)
{
  // 如果有生产者正在生产，则等待
  if (down(semids_for_producer[type]) == -1)
  {
    perror("semop");
    return -1;
  }
  // 如果没有生产任务，则等待
  if (type == 0)
  {
    down(semid_for_paper);
  }
  else if (type == 1)
  {
    down(semid_for_water);
  }
  else if (type == 2)
  {
    down(semid_for_tobacco);
  }
  if (writeSharedMemory(shm_ptr, data, size) == -1)
  {
    perror("writeSharedMemory");
    return -1;
  }
  // 生产完成，通知其他生产者和消费者
  if (up(semids_for_producer[type]) == -1)
  {
    perror("semop");
    return -1;
  }
  return 0;
}

static inline int producePaper()
{
  if (produce(0, shm_ptrs[0], (void*)&paper_cnt, sizeof(size_t)) == -1)
  {
    perror("producePaper");
    return -1;
  }
  paper_cnt++;
  // 生产完成，通知消费者
  up(semids_for_paper_cnt);
  return 0;
}

static inline int produceWater()
{
  if (produce(1, shm_ptrs[1], (void*)&water_cnt, sizeof(size_t)) == -1)
  {
    perror("produceWater");
    return -1;
  }
  water_cnt++;
  // 生产完成，通知消费者
  up(semids_for_water_cnt);
  return 0;
}

static inline int produceTobacco()
{
  if (produce(2, shm_ptrs[2], (void*)&tobacco_cnt, sizeof(size_t)) == -1)
  {
    perror("produceTobacco");
    return -1;
  }
  tobacco_cnt++;
  // 生产完成，通知消费者
  up(semids_for_tobacco_cnt);
  return 0;
}

static inline int consumePaper(void* data_buf, size_t size)
{
  // 如果有消费者正在消费，则等待
  down(semids_for_consumer[0]);
  // 呼起生产者
  up(semid_for_paper);
  // 等待生产者完成生产
  down(semids_for_paper_cnt);
  if (readSharedMemory(shm_ptrs[0], data_buf, size) == -1)
  {
    perror("readSharedMemory");
    return -1;
  }
  // 唤起其他消费者
  up(semids_for_consumer[0]);
  return 0;
}

static inline int consumeWater(void* data_buf, size_t size)
{
  // 如果有消费者正在消费，则等待
  down(semids_for_consumer[1]);
  // 呼起生产者
  up(semid_for_water);
  // 等待生产者完成生产
  down(semids_for_water_cnt);
  if (readSharedMemory(shm_ptrs[1], data_buf, size) == -1)
  {
    perror("readSharedMemory");
    return -1;
  }
  // 唤起其他消费者
  up(semids_for_consumer[1]);
  return 0;
}

static inline int consumeTobacco(void* data_buf, size_t size)
{
  // 如果有消费者正在消费，则等待
  down(semids_for_consumer[2]);
  // 呼起生产者
  up(semid_for_tobacco);
  // 等待生产者完成生产
  down(semids_for_tobacco_cnt);
  if (readSharedMemory(shm_ptrs[2], data_buf, size) == -1)
  {
    perror("readSharedMemory");
    return -1;
  }
  // 唤起其他消费者
  up(semids_for_consumer[2]);
  return 0;
}

static inline int produceLoop(int type)
{
  time_t current_time;
  time(&current_time);
  struct tm* time_info = localtime(&current_time);
  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
  if (type == 0)
  {
    producePaper();
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Producer Pid : %d, produce paper. paper_cnt : %d\n",
           time_str, getpid(), (int)paper_cnt);
    produceWater();
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Producer Pid : %d, produce water. water_cnt : %d\n",
           time_str, getpid(), (int)water_cnt);
  }
  if (type == 1)
  {
    produceWater();
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Producer Pid : %d, produce water. water_cnt : %d\n",
           time_str, getpid(), (int)water_cnt);
    produceTobacco();
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Producer Pid : %d, produce tobacco. tobacco_cnt : %d\n",
           time_str, getpid(), (int)tobacco_cnt);
  }
  if (type == 2)
  {
    produceTobacco();
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Producer Pid : %d, produce tobacco. tobacco_cnt : %d\n",
           time_str, getpid(), (int)tobacco_cnt);
    producePaper();
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Producer Pid : %d, produce paper. paper_cnt : %d\n",
           time_str, getpid(), (int)paper_cnt);
  }
  fflush(stdout);
  return 0;
}

static inline int producerRun()
{
  while (1)
  {
    produceLoop(0);
    produceLoop(1);
    produceLoop(2);
    sleep(SLEEP_TIME);
  }
  return 0;
}

static inline int consumeLoop(int type, void* data_buf, size_t size)
{
  time_t current_time;
  time(&current_time);
  struct tm* time_info = localtime(&current_time);
  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
  if (type == 0)
  {
    consumePaper(data_buf, size);
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Consumer Pid : %d, consume paper. got data : %d\n", time_str,
           getpid(), *(int*)data_buf);
    consumeWater(data_buf, size);
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Consumer Pid : %d, consume water. got data : %d\n", time_str,
           getpid(), *(int*)data_buf);
  }
  else if (type == 1)
  {
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    consumeWater(data_buf, size);
    printf("[ %s ] Consumer Pid : %d, consume water. got data : %d\n", time_str,
           getpid(), *(int*)data_buf);
    consumeTobacco(data_buf, size);
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("[ %s ] Consumer Pid : %d, consume tobacco. got data : %d\n",
           time_str, getpid(), *(int*)data_buf);
  }
  else if (type == 2)
  {
    consumeTobacco(data_buf, size);
    printf("[ %s ] Consumer Pid : %d, consume tobacco. got data : %d\n",
           time_str, getpid(), *(int*)data_buf);
    consumePaper(data_buf, size);
    printf("[ %s ] Consumer Pid : %d, consume paper. got data : %d\n", time_str,
           getpid(), *(int*)data_buf);
  }
  fflush(stdout);
  return 0;
}
static inline int consumerRun(int type)
{
  int data_buf[1];
  while (1)
  {
    consumeLoop(type, data_buf, sizeof(data_buf));
    sleep(SLEEP_TIME);
  }
  return 0;
}
