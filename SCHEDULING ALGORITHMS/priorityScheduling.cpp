#include <iostream>
#include <vector>
#include <queue>
#include <climits>   // for INT_MAX
#include <algorithm> // for sort

using namespace std;

class PriorityScheduling
{
private:
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
    void addProcess(int arrival, int burst, int priorityValue)
    {
        processId.push_back(count++);
        arrivalTime.push_back(arrival);
        burstTime.push_back(burst);
        priority.push_back(priorityValue);
        remainingTime.push_back(burst); // Initialize remaining time with burst time
    }

    void calculateTimes()
    {
        int n = processId.size();

        // Vector to store the process info as pairs (priority, processId)
        vector<pair<int, int>> readyQueue;

        // Variables to store times
        int currentTime = 0;
        int completedProcesses = 0;
        completionTime.resize(n, -1);  // Initialize completion time to -1
        waitingTime.resize(n, 0);
        turnAroundTime.resize(n, 0);

        // While all processes are not completed
        while (completedProcesses != n)
        {
            // Add processes that have arrived to the ready queue
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && find_if(readyQueue.begin(), readyQueue.end(), [i](const pair<int, int>& p){ return p.second == i; }) == readyQueue.end())
                {
                    readyQueue.push_back(make_pair(priority[i], i)); // Store process index with priority
                }
            }

            // If the readyQueue is empty, move time forward
            if (readyQueue.empty())
            {
                currentTime++;
                continue;
            }

            // Sort by priority, ascending order (lower priority number = higher priority)
            sort(readyQueue.begin(), readyQueue.end());

            // Get the process with the highest priority (lowest priority number)
            int idx = readyQueue[0].second;

            // Execute the process for one unit of time
            remainingTime[idx]--;
            currentTime++;

            // If the process is finished, calculate its times
            if (remainingTime[idx] == 0)
            {
                completionTime[idx] = currentTime;  // Set the actual completion time
                turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                waitingTime[idx] = turnAroundTime[idx] - burstTime[idx];
                completedProcesses++;
            }

            // Clear the ready queue for the next cycle
            readyQueue.clear();
        }
    }

    void printResults()
    {
        int n = processId.size();
        float totalTurnAroundTime = 0, totalWaitingTime = 0;

        cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
        for (int i = 0; i < n; i++)
        {
            totalTurnAroundTime += turnAroundTime[i];
            totalWaitingTime += waitingTime[i];
            cout << processId[i] << "\t\t"
                 << arrivalTime[i] << "\t\t"
                 << burstTime[i] << "\t\t"
                 << priority[i] << "\t\t"
                 << completionTime[i] << "\t\t"
                 << turnAroundTime[i] << "\t\t"
                 << waitingTime[i] << endl;
        }

        cout << "\nAverage Turnaround Time: " << (totalTurnAroundTime / n) << endl;
        cout << "Average Waiting Time: " << (totalWaitingTime / n) << endl;
    }
};

// Initialize static member
int PriorityScheduling::count = 0;

int main()
{
    PriorityScheduling scheduler;

    // Example input for adding processes
    scheduler.addProcess(0, 3, 3);
    scheduler.addProcess(1, 6, 4);
    scheduler.addProcess(3, 1, 9);
    scheduler.addProcess(2, 2, 7);
    scheduler.addProcess(4, 4, 8);

    scheduler.calculateTimes();
    scheduler.printResults();

    return 0;
}
