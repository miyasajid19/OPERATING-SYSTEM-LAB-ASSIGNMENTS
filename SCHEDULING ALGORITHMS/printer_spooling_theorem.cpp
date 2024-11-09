#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
queue<int> printQueue;  // Queue to hold print jobs
mutex mtx;              // Mutex for critical section
condition_variable cv;  // Condition variable for synchronization

void printer(int job) {
    // Simulate printing a job
    this_thread::sleep_for(chrono::seconds(2));  // Simulate time taken for printing
    cout << "Job " << job << " printed." << endl;
}

void printJob() {
    while (true) {
        unique_lock<mutex> lock(mtx);

        // Wait until there is a job in the queue
        cv.wait(lock, [](){ return !printQueue.empty(); });

        // Get the next job from the queue
        int job = printQueue.front();
        printQueue.pop();

        lock.unlock();  // Release lock for other threads

        // Print the job
        printer(job);
    }
}

void addJob(int job) {
    unique_lock<mutex> lock(mtx);

    // Add job to the print queue
    printQueue.push(job);
    cout << "Job " << job << " added to the queue." << endl;

    lock.unlock();  // Release lock for other threads

    // Notify the printer thread that a job has been added
    cv.notify_one();
}

int main() {
    thread printerThread(printJob);  // Start the printer thread

    // Add some print jobs to the queue
    this_thread::sleep_for(chrono::seconds(1)); // Simulate a small delay before adding jobs
    addJob(1);
    this_thread::sleep_for(chrono::seconds(1));
    addJob(2);
    this_thread::sleep_for(chrono::seconds(1));
    addJob(3);
    this_thread::sleep_for(chrono::seconds(1));
    addJob(4);

    // Wait for the printer thread to process jobs (in real-world applications, this would be more dynamic)
    this_thread::sleep_for(chrono::seconds(10));

    printerThread.join();  // Wait for the printer thread to finish

    return 0;
}
