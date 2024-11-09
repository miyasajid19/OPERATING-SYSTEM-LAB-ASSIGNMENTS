#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t empty, full;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);  // Wait if buffer is full
        buffer[in] = item;  // Add item to buffer
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&full);  // Signal that there is a new item
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait if buffer is empty
        item = buffer[out];  // Consume item from buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&empty);  // Signal that there is space in the buffer
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Buffer is empty initially
    sem_init(&full, 0, 0);  // No items to consume initially

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Join threads (in real programs, you might want to use a condition to stop)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
