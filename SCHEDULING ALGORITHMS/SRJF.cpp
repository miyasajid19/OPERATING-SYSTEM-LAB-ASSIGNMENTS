#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // For INT_MAX
using namespace std;

class SRJF
{
    static int count;

public:
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> BrustTime;
    vector<int> remainingTime;
    vector<int> waitingTime;
    vector<int> completionTime;
    vector<int> TurnAroundTime;
    vector<int> queues;  // To track the sequence of execution

    void add(int AT, int BT)
    {
        count++;
        this->processid.push_back(count);
        this->arrivalTime.push_back(AT);
        this->BrustTime.push_back(BT);
        this->remainingTime.push_back(BT);
    }

    void computeSRJF()
    {
        int n = processid.size();
        vector<int> remainingBurstTime = BrustTime;
        int currentTime = 0, completed = 0;
        int minRT = INT_MAX, idx = -1;

        completionTime.resize(n);
        waitingTime.resize(n);
        TurnAroundTime.resize(n);

        while (completed != n)
        {
            bool done = true;
            minRT = INT_MAX; // Reset minRT each iteration

            for (int i = 0; i < n; i++)
            {
                // Only consider processes that have arrived and still need execution
                if (arrivalTime[i] <= currentTime && remainingBurstTime[i] > 0)
                {
                    done = false;

                    // Select the process with the shortest remaining time
                    if (remainingBurstTime[i] < minRT)
                    {
                        minRT = remainingBurstTime[i];
                        idx = i;
                    }
                }
            }

            if (idx != -1)
            {
                remainingBurstTime[idx]--; // Decrement remaining burst time

                // If the process is completed
                if (remainingBurstTime[idx] == 0)
                {
                    completed++;
                    completionTime[idx] = currentTime + 1;
                    TurnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                    waitingTime[idx] = TurnAroundTime[idx] - BrustTime[idx];
                    queues.push_back(idx); // Store the process ID in execution order
                }
                currentTime++;
            }
            else
            {
                // If no process is ready to execute, increment the time
                currentTime++;
            }
        }
    }

    void printSRJF()
    {
        cout << "processid\tarrivaltime\tbrusttime\tcompletiontime\twaitingtime\tturnaroundtime\n";
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;
        for (int i = 0; i < processid.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += TurnAroundTime[i];
            cout << processid[i] << "\t\t" << arrivalTime[i] << "\t\t" << BrustTime[i] << "\t\t"
                 << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << TurnAroundTime[i] << "\n";
        }
        
        // Print the sequence of execution (queue)
        cout << "Execution Sequence (Process IDs): ";
        for (auto x : queues)
            cout << processid[x] << "\t";  // Print actual Process ID
        cout << endl;

        cout << "Average Waiting Time: " << totalWaitingTime / processid.size() << "\n";
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processid.size() << "\n";
    }
};

int SRJF::count = 0;

int main()
{
    SRJF srjf;
    srjf.add(2, 6);  // Process 1 arrives at time 2, burst time 6
    srjf.add(5, 2);  // Process 2 arrives at time 5, burst time 2
    srjf.add(1, 8);  // Process 3 arrives at time 1, burst time 8
    srjf.add(0, 3);  // Process 4 arrives at time 0, burst time 3
    srjf.add(4, 4);  // Process 5 arrives at time 4, burst time 4

    srjf.computeSRJF();
    srjf.printSRJF();

    return 0;
}
