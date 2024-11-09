#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t chopstick[5];

void philosopher(int id) {
    while (true) {
        cout << "Philosopher " << id << " is thinking." << endl;
        
        sem_wait(&chopstick[id]);          // Pick up left chopstick
        sem_wait(&chopstick[(id + 1) % 5]); // Pick up right chopstick
        
        cout << "Philosopher " << id << " is eating." << endl;
        
        sem_post(&chopstick[id]);          // Put down left chopstick
        sem_post(&chopstick[(id + 1) % 5]); // Put down right chopstick
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);  // Initialize all chopsticks
    }

    thread t1(philosopher, 0), t2(philosopher, 1), t3(philosopher, 2), t4(philosopher, 3), t5(philosopher, 4);
    t1.join(); t2.join(); t3.join(); t4.join(); t5.join();

    for (int i = 0; i < 5; i++) {
        sem_destroy(&chopstick[i]); // Clean up the semaphore
    }

    return 0;
}
