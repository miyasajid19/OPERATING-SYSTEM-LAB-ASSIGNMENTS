#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t readLock, writeLock;
int readCount = 0;

void reader(int id) {
    sem_wait(&readLock);
    readCount++;
    if (readCount == 1)
        sem_wait(&writeLock);  // First reader locks the writer

    sem_post(&readLock);
    cout << "Reader " << id << " is reading the data." << endl;

    sem_wait(&readLock);
    readCount--;
    if (readCount == 0)
        sem_post(&writeLock);  // Last reader releases the writer

    sem_post(&readLock);
}

void writer(int id) {
    sem_wait(&writeLock);  // Writer locks the write lock
    cout << "Writer " << id << " is writing data." << endl;
    sem_post(&writeLock);
}

int main() {
    sem_init(&readLock, 0, 1);
    sem_init(&writeLock, 0, 1);

    thread t1(reader, 1), t2(reader, 2), t3(writer, 1), t4(reader, 3);
    t1.join(); t2.join(); t3.join(); t4.join();

    sem_destroy(&readLock);
    sem_destroy(&writeLock);

    return 0;
}
