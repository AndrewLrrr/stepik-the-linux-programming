#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>

void create_shared_memory(key_t shm_key)
{
    const int SHM_SIZE = 1000;

    int shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);

    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    int *shm = shmat(shm_id, 0, 0);

    int i;
    for (i = 0; i < 300; ++i) {
        shm[i] = rand() % 100 + 1;
    }
}

int main(int argc, char const *argv[])
{
    key_t shm_key_1 = atoi(argv[1]);
    key_t shm_key_2 = atoi(argv[2]);
  
    create_shared_memory(shm_key_1);
    create_shared_memory(shm_key_2);
  
    return 0;
}
