#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <cstring>
using namespace std;
#define SHM_NAME "/posix_shm"
#define BUFFER_SIZE 10

struct SharedMemory
{
    char buffer[BUFFER_SIZE];
    sem_t full;
    sem_t empty;
};

int main()
{
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedMemory));

    SharedMemory *shared = (SharedMemory *)mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_init(&shared->full, 1, 0);
    sem_init(&shared->empty, 1, BUFFER_SIZE);

    if (fork() == 0)
    { // Consumer process
        while (true)
        {
            sem_wait(&shared->full);
            cout << "Consumed: " << shared->buffer << endl;
            sem_post(&shared->empty);
            sleep(1);
        }
    }
    else
    { // Producer process
        while (true)
        {
            sem_wait(&shared->empty);
            string data = "data";
            strncpy(shared->buffer, data.c_str(), BUFFER_SIZE);
            cout << "Produced: " << shared->buffer << endl;
            sem_post(&shared->full);
            sleep(1);
        }
    }

    shm_unlink(SHM_NAME);
    return 0;
}
