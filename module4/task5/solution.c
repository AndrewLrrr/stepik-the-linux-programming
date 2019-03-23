#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    key_t SHM_KEY_RESULT = 19900610;

    const int SHM_SIZE = 1000;

    key_t shm_key_1 = atoi(argv[1]);
    key_t shm_key_2 = atoi(argv[2]);

    int debug = (argc > 3) ? atoi(argv[3]) : 0;

    int shm_id_1 = shmget(shm_key_1, SHM_SIZE, 0600);
    int shm_id_2 = shmget(shm_key_2, SHM_SIZE, 0600);

    if (shm_id_1 < 0 || shm_id_2 < 0) {
        perror("shmget 1 or 2");
        exit(1);
    }

    int *shm_1 = shmat(shm_id_1, NULL, 0);
    int *shm_2 = shmat(shm_id_2, NULL, 0);

    int shm_id = shmget(SHM_KEY_RESULT, SHM_SIZE, IPC_CREAT | 0666);

    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    int *shm = shmat(shm_id, 0, 0);

    int i;
    for (i = 0; i < 100; ++i) {
        shm[i] = shm_1[i] + shm_2[i];
        if (debug == 1) {
            printf("%d + %d = %d\n", shm_1[i], shm_2[i], shm[i]);
        }
    }

    printf("%d\n", SHM_KEY_RESULT);

    return 0;
}