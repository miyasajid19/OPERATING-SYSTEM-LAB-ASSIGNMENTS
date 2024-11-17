#include <iostream>
#include <vector>
#include <queue>
#include <climits> // for INT_MAX
#include <algorithm> // for sort
using namespace std;

class PriorityScheduling
{
    static int count; // static counter to give each process a unique ID
    vector<int> processId;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> priority;
    vector<int> remainingTime;
    vector<int> completionTime;
    vector<int> turnAroundTime;
    vector<int> waitingTime;
    queue<int> executionQueue; // Queue to store execution order

public:
    // Constructor to initialize the priority scheduling algorithm
    PriorityScheduling()
    {
        // No time quantum needed for priority scheduling
    }

    // Add a new process to the system
    void add(int AT, int BT, int P)
    {
        this->processId.push_back(count++);
        this->arrivalTime.push_back(AT);
        this->burstTime.push_back(BT);
        this->priority.push_back(P);
        this->remainingTime.push_back(BT); // Initially, remaining time = burst time
    }

    // Function to compute the scheduling
    void compute()
    {
        int n = processId.size();
        remainingTime = burstTime; // Copy of remaining burst times
        completionTime.resize(n);
        turnAroundTime.resize(n);
        waitingTime.resize(n);
        int currentTime = 0; // Start from time 0
        int completed = 0;   // Track completed processes

        // Vector of processes to sort by arrival time and priority
        vector<int> readyQueue; // To store the indices of ready processes
        while (completed != n)
        {
            // Add processes that have arrived by currentTime to the ready queue
            readyQueue.clear();
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && remainingTime[i] > 0)
                {
                    readyQueue.push_back(i);
                }
            }

            // Sort readyQueue based on priority (ascending order) and arrival time (ascending order)
            sort(readyQueue.begin(), readyQueue.end(), [&](int a, int b) {
                if (priority[a] == priority[b])
                    return arrivalTime[a] < arrivalTime[b];
                return priority[a] < priority[b];
            });

            if (!readyQueue.empty())
            {
                // Select the process with the highest priority (lowest priority value)
                int processIndex = readyQueue[0];
                currentTime += remainingTime[processIndex];
                completionTime[processIndex] = currentTime;
                turnAroundTime[processIndex] = completionTime[processIndex] - arrivalTime[processIndex];
                waitingTime[processIndex] = turnAroundTime[processIndex] - burstTime[processIndex];
                remainingTime[processIndex] = 0; // Process completed
                completed++; // Increment completed processes
                executionQueue.push(processId[processIndex]);
            }
            else
            {
                // If no process is ready, increment time
                currentTime++;
            }
        }
    }

    // Function to print the results
    void printPriorityScheduling()
    {
        cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;

        // Print the detailed information for each process
        for (int i = 0; i < processId.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += turnAroundTime[i];
            cout << processId[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t"
                 << priority[i] << "\t\t" << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }

        // Print the sequence of execution (queue)
        cout << "\nExecution Sequence (Process IDs): ";
        while (!executionQueue.empty())
        {
            cout << executionQueue.front() << " ";
            executionQueue.pop();
        }
        cout << endl;

        // Print the average waiting time and turnaround time
        cout << "\nAverage Waiting Time: " << totalWaitingTime / processId.size() << endl;
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processId.size() << endl;
    }
};

// Initialize static count variable
int PriorityScheduling::count = 1;

int main()
{
    PriorityScheduling ps;

    // Adding processes to the system
    ps.add(0, 7, 2);   // Process 1, Arrival time = 0, Burst time = 7, Priority = 2
    ps.add(0, 30, 1); // Process 2, Arrival time = 10, Burst time = 30, Priority = 1
    ps.add(20, 13, 3); // Process 3, Arrival time = 20, Burst time = 13, Priority = 3

    // Perform Priority Scheduling computation
    ps.compute();

    // Print the result of Priority scheduling
    ps.printPriorityScheduling();

    return 0;
}
