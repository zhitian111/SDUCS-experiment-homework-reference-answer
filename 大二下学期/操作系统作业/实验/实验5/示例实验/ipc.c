#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

int get_ipc_id(char *proc_file, key_t key) {
    FILE *pf;
    int i, j;
    char line[BUFSZ], colum[BUFSZ];

    pf = fopen(proc_file, "r");
    if (pf == NULL) {
        perror("Proc file not open");
        exit(EXIT_FAILURE);
    }
    fgets(line, BUFSZ, pf);
    while (!feof(pf)) {
        i = j = 0;
        fgets(line, BUFSZ, pf);
        while (line[i] == ' ') i++;
        while (line[i] != ' ') colum[j++] = line[i++];
        colum[j] = 0;
        if (atoi(colum) != key) continue;
        j = 0;
        while (line[i] == ' ') i++;
        while (line[i] != ' ') colum[j++] = line[i++];
        colum[j] = 0;
        i = atoi(colum);
        fclose(pf);
        return i;
    }
    fclose(pf);
    return -1;
}

char  *set_shm(key_t shm_key, int shm_num, int shm_flag) {
    int shm_id;
    void *shm_buf;

    shm_id = get_ipc_id("/proc/sysvipc/shm", shm_key);
    if (shm_id < 0) {
        shm_id = shmget(shm_key, shm_num, shm_flag);
        if (shm_id < 0) {
            perror("ShareMemory create failed");
            exit(EXIT_FAILURE);
        }
        shm_buf = shmat(shm_id, 0, 0);
        if (shm_buf < 0) {
            perror("ShareMemory attach failed");
            exit(EXIT_FAILURE);
        }
        memset(shm_buf, 0, shm_num);
        return shm_buf;
    }
    shm_buf = shmat(shm_id, 0, 0);
    if (shm_buf < 0) {
        perror("ShareMemory attach failed");
        exit(EXIT_FAILURE);
    }
    return shm_buf;
}

int set_msq(key_t msq_key, int msq_flag) {
    int msq_id;

    msq_id = get_ipc_id("/proc/sysvipc/msg", msq_key);
    if (msq_id < 0) {
        msq_id = msgget(msq_key, msq_flag);
        if (msq_id < 0) {
            perror("MessageQueue create failed");
            exit(EXIT_FAILURE);
        }
    }
    return msq_id;
}

int set_sem(key_t sem_key, int sem_val, int sem_flag) {
    int sem_id;
    Sem_uns sem_arg;

    sem_id = get_ipc_id("/proc/sysvipc/sem", sem_key);
    if (sem_id < 0) {
        sem_id = semget(sem_key, 1, sem_flag);
        if (sem_id < 0) {
            perror("Semaphore create failed");
            exit(EXIT_FAILURE);
        }
        sem_arg.val = sem_val;
        if (semctl(sem_id, 0, SETVAL, sem_arg) < 0) {
            perror("Semaphore set failed");
            exit(EXIT_FAILURE);
        }
    }
    return sem_id;
}

int P(int sem_id) {
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    if (semop(sem_id, &buf, 1) < 0) {
        perror("Operation P failed");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int V(int sem_id) {
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;
    if (semop(sem_id, &buf, 1) < 0) {
        perror("Operation V failed");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}