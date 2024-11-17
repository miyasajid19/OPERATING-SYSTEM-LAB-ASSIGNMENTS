#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;
class SRJF
{
    static int count;
    vector<int> processId;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> completionTime;
    vector<int> turnAroundTime;
    vector<int> waitingTime;
    vector<int> remainingTime;
    queue<int> Queue;

public:
    void add(int AT, int BT)
    {
        this->processId.push_back(count++);
        this->arrivalTime.push_back(AT);
        this->burstTime.push_back(BT);
        this->remainingTime.push_back(BT);
    }
    void compute()
    {
        int n = processId.size();
        vector<int> remainingBurstTime = burstTime;
        int index = -1;
        int completed = 0;
        completionTime.resize(n);
        turnAroundTime.resize(n);
        waitingTime.resize(n);
        int currentTime = 0;
        while (completed != n)
        {
            int minRT = INT_MAX;
            // checking
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime and remainingBurstTime[i] > 0)
                {
                    if (remainingBurstTime[i] < minRT)
                    {
                        minRT = remainingBurstTime[i];
                        index = i;
                    }
                }
            }

            if (index != -1)
            {
                remainingBurstTime[index]--;
                if (remainingBurstTime[index] == 0)
                {
                    completed++;
                    completionTime[index] = currentTime + 1;
                    turnAroundTime[index] = completionTime[index] - arrivalTime[index];
                    waitingTime[index] = turnAroundTime[index] - burstTime[index];
                    Queue.push(index);
                }
                currentTime++;
            }
            else
            {
                currentTime++;
            }
        }
    }
    void printSRJF()
    {
        cout << "processid\tarrivaltime\tbrusttime\tcompletiontime\twaitingtime\tturnaroundtime\n";
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;
        for (int i = 0; i < processId.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += turnAroundTime[i];
            cout << processId[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t"
                 << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << "\n";
        }

        // Print the sequence of execution (queue)
        cout << "Execution Sequence (Process IDs): ";
        while (not Queue.empty())
        {
            cout << Queue.front() << "\t";
            Queue.pop();
        }
        cout << endl;

        cout << "Average Waiting Time: " << totalWaitingTime / processId.size() << "\n";
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processId.size() << "\n";
    }
};
int SRJF::count = 1;

int main()
{
    SRJF srjf;
    srjf.add(2, 6); // Process 1 arrives at time 2, burst time 6
    srjf.add(5, 2); // Process 2 arrives at time 5, burst time 2
    srjf.add(1, 8); // Process 3 arrives at time 1, burst time 8
    srjf.add(0, 3); // Process 4 arrives at time 0, burst time 3
    srjf.add(4, 4); // Process 5 arrives at time 4, burst time 4

    srjf.compute();
    srjf.printSRJF();

    return 0;
}