#include <iostream>
#include <vector>
#include <queue>
#include <climits>   // for INT_MAX
#include <set>       // for std::set
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

public:
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
        completionTime.resize(n, 0);
        turnAroundTime.resize(n, 0);
        waitingTime.resize(n, 0);
        int currentTime = 0; // Start from time 0
        int completed = 0;   // Track completed processes

        // Min-heap to store processes based on priority (higher priority first)
        auto compare = [&](int a, int b)
        {
            if (priority[a] == priority[b])
            {
                return arrivalTime[a] > arrivalTime[b]; // If same priority, earliest arrival first
            }
            return priority[a] > priority[b]; // Higher priority first (lower priority number)
        };

        priority_queue<int, vector<int>, decltype(compare)> readyQueue(compare);
        set<int> addedToQueue; // Set to track which processes are in the queue

        while (completed != n)
        {
            // Add all processes that have arrived by currentTime to the readyQueue
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && addedToQueue.find(i) == addedToQueue.end())
                {
                    readyQueue.push(i);
                    addedToQueue.insert(i); // Mark the process as added to the queue
                }
            }

            if (!readyQueue.empty())
            {
                // Select the process with the highest priority (top of the min-heap)
                int processIndex = readyQueue.top();
                readyQueue.pop();

                // If preemption happens (higher priority process arrives)
                if (remainingTime[processIndex] > 0 && priority[processIndex] > priority[readyQueue.top()])
                {
                    // Preempt the current process
                    readyQueue.push(processIndex); // Re-insert the current process back into the queue
                    cout << "Process " << processId[processIndex] << " preempted." << endl;
                    continue; // Immediately pick the new highest priority process
                }

                // Execute this process for its remaining time
                remainingTime[processIndex] -= 1;
                currentTime++;
                if (remainingTime[processIndex] == 0)
                {
                    completionTime[processIndex] = currentTime;
                    turnAroundTime[processIndex] = completionTime[processIndex] - arrivalTime[processIndex];
                    waitingTime[processIndex] = turnAroundTime[processIndex] - burstTime[processIndex];
                    remainingTime[processIndex] = 0; // Process completed
                    completed++;
                }
                else
                {
                    cout << "preempted" << endl;
                    readyQueue.push(processIndex);
                }
            }
            else
            {
                // If no process is ready, increment time (simulate idle time)
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
    ps.add(0, 3, 3);
    ps.add(1, 4, 2);
    ps.add(2, 6, 4);
    ps.add(3, 4, 6);
    ps.add(5, 2, 10);

    // Perform Priority Scheduling computation
    ps.compute();

    // Print the result of Priority scheduling
    ps.printPriorityScheduling();

    return 0;
}
