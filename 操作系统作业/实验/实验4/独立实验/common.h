#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SHM_MODE 0666 | IPC_CREAT
#define PATH "common.h"

key_t shm_key_for_paper;
key_t shm_key_for_water;
key_t shm_key_for_tobacco;

int shmids[3];
void* shm_ptrs[3];
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
  shmids[0] = createSharedMemory(shm_key_for_paper, SHM_SIZE);
  shmids[1] = createSharedMemory(shm_key_for_water, SHM_SIZE);
  shmids[2] = createSharedMemory(shm_key_for_tobacco, SHM_SIZE);
  if (shmids[0] == -1 || shmids[1] == -1 || shmids[2] == -1)
  {
    perror("shmget");
    return -1;
  }
  return 0;
}

static inline int getKeys()
{
  shm_key_for_paper = ftok(PATH, 'p');
  shm_key_for_water = ftok(PATH, 'w');
  shm_key_for_tobacco = ftok(PATH, 't');
  if (shm_key_for_paper == -1 || shm_key_for_water == -1 ||
      shm_key_for_tobacco == -1)
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
  if (getKeys() == -1)
  {
    perror("ftok");
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
