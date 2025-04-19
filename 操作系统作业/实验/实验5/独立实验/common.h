#include <cstdlib>
#include <iostream>
#include <ostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#define SHM_SIZE sizeof(double)
#define SHM_MODE 0666 | IPC_CREAT
#define SEM_MODE 0666 | IPC_CREAT
#define SEM_VALUE 1
#define PATH "./common.h"
#define RECEIVER_TIME_INTERVAL 1     // 接受新顾客的耗时
#define BARBER_BARBE_TIME_INTERVAL 1 // 理发师理发的耗时
#define CASHIER_CASH_TIME_INTERVAL 1 // 收银的耗时
#define MOVER_MOVE_TIME_INTERVAL 1   // 移动顾客的耗时
#define MANAGER_TIME_INTERVAL 1      // 管理顾客付钱的耗时
#define WAIT_ROOM_SIZE 13            // 等待区大小
#define SOFA_SIZE 4                  // 座位大小
#define BARBERSHOP_SIZE 20           // 理发店总容量
#define REST_CHECK_TIME_INTERVAL 1   // 休息检查的耗时
#define SHOP_RUNNING_TIME 12         // 店铺运行时间
static inline void log_prefix()
{
  time_t current_time;
  struct tm* time_info;
  time(&current_time);
  char time_str[100];
  time_info = localtime(&current_time);
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
  printf("[ %s ] Pid : %d, ", time_str, getpid());
  fflush(stdout);
}
static std::ostream& log()
{
  log_prefix();
  return std::cout;
}

static inline void error_prefix()
{
  time_t current_time;
  struct tm* time_info;
  time(&current_time);
  char time_str[100];
  time_info = localtime(&current_time);
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
  fprintf(stderr, "[ %s ] Pid : %d, ", time_str, getpid());
  fflush(stdout);
}
static int key_cnt = 0;
class sem
{
private:
  key_t key;
  int sem_id;

public:
  sem()
  {
    key = ftok(PATH, key_cnt);
    if (key == -1)
    {
      error_prefix();
      perror("ftok");
      throw std::runtime_error("syscall failed");
    }
    key_cnt++;
    sem_id = semget(key, SEM_VALUE, SEM_MODE);
  }
  sem(int value)
  {
    key = ftok(PATH, key_cnt);
    if (key == -1)
    {
      error_prefix();
      perror("ftok");
      throw std::runtime_error("syscall failed");
    }
    key_cnt++;
    sem_id = semget(key, SEM_VALUE, SEM_MODE);
    if (semctl(sem_id, 0, SETVAL, value) == -1)
    {
      error_prefix();
      perror("semctl");
      throw std::runtime_error("syscall failed");
    }
  }
  ~sem()
  {
    if (semctl(sem_id, 0, IPC_STAT, 0) != 1)
    {
      return;
    }
    if (semctl(sem_id, 0, IPC_RMID, 0) == -1)
    {
      error_prefix();
      perror("semctl");
    }
  }
  void down()
  {

    struct sembuf sem[1];
    sem[0].sem_num = 0;
    sem[0].sem_op = -1;
    sem[0].sem_flg = SEM_UNDO;
    if (semop(sem_id, sem, 1) == -1)
    {
      error_prefix();
      perror("semop");
      throw std::runtime_error("syscall failed");
    }
  }
  void up()
  {

    struct sembuf sem[1];
    sem[0].sem_num = 0;
    sem[0].sem_op = 1;
    sem[0].sem_flg = SEM_UNDO;
    if (semop(sem_id, sem, 1) == -1)
    {
      error_prefix();
      perror("semop");
      throw std::runtime_error("syscall failed");
    }
  }
};

class shm
{
private:
  key_t key;
  int shm_id;
  void* shm_ptr;
  int shm_size;

public:
  shm()
  {
    key = ftok(PATH, key_cnt);
    if (key == -1)
    {
      error_prefix();
      perror("ftok");
      throw std::runtime_error("syscall failed");
    }
    key_cnt++;
    shm_id = shmget(key, SHM_SIZE, SHM_MODE);
    if (shm_id == -1)
    {
      error_prefix();
      perror("shmget");
      throw std::runtime_error("syscall failed");
    }
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*)-1)
    {
      error_prefix();
      perror("shmat");
      throw std::runtime_error("syscall failed");
    }
    shm_size = SHM_SIZE;
  }
  shm(int size)
  {
    key = ftok(PATH, key_cnt);
    if (key == -1)
    {
      error_prefix();
      perror("ftok");
      throw std::runtime_error("syscall failed");
    }
    key_cnt++;
    shm_id = shmget(key, size, SHM_MODE);
    if (shm_id == -1)
    {
      error_prefix();
      perror("shmget");
      throw std::runtime_error("syscall failed");
    }
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*)-1)
    {
      error_prefix();
      perror("shmat");
      throw std::runtime_error("syscall failed");
    }
    shm_size = size;
  }
  ~shm()
  {
    if (shmdt(shm_ptr) == -1)
    {
      error_prefix();
      perror("shmdt");
    }
    if (shmctl(shm_id, IPC_STAT, 0) != 1)
    {
      return;
    }
    if (shmctl(shm_id, IPC_RMID, 0) == -1)
    {
      error_prefix();
      perror("shmctl");
    }
  }
  template <typename T> void write(const T data)
  {
    if (sizeof(T) > shm_size)
    {
      error_prefix();
      fprintf(stderr, "shm size is not enough to write data");
      throw std::runtime_error("syscall failed");
    }
    memcpy(shm_ptr, (void*)&data, sizeof(T));
  }
  template <typename T> void read(T& data)
  {
    if (sizeof(T) > shm_size)
    {
      error_prefix();
      fprintf(stderr, "shm size is not enough to read data");
      throw std::runtime_error("syscall failed");
    }
    memcpy((void*)&data, shm_ptr, sizeof(T));
  }
};

static shm barber_shop_capacity(sizeof(int));
static shm for_sys_key_cnt(sizeof(int));
static shm money_trade_buffer(sizeof(double));
static shm sum_money(sizeof(double));
static sem new_customer_in(0);
static sem new_customer_come(0);
static sem is_someone_is_paying(1);
static sem is_someone_is_receiving_money(1);
static sem the_man_who_is_paying_is_done(0);
static sem is_someone_is_entrying(1);
static sem needed_services_cnt(0);
static sem needed_pay_money_cnt(0);
static sem barber_finish_service(0);
static sem barber_finish_receive_money(0);
class user_sems
{
private:
  sem move_to_sofa;
  sem get_service;
  sem give_money;

public:
  void wait_for_move_to_sofa() { move_to_sofa.down(); }
  void wait_for_get_service() { get_service.down(); }
  void wair_for_give_money() { give_money.down(); }
};
static int service_cnt = 0;
class service_sems
{
private:
  sem user_move_to_sofa;
  sem support_service;
  sem receive_money;
  int id;

public:
  void let_user_move_to_sofa()
  {
    user_move_to_sofa.up();
    needed_services_cnt.up();
  }

  void support_service_for_user()
  {
    support_service.up();
    needed_pay_money_cnt.up();
  }
  void let_user_pay_money() { receive_money.up(); }
  service_sems()
  {
    int customer_num = 0;
    barber_shop_capacity.read(customer_num);
    customer_num++;
    barber_shop_capacity.write(customer_num);
    id = service_cnt++;
  }
  int get_id() { return id; }
};
static shm is_closing(sizeof(int));
