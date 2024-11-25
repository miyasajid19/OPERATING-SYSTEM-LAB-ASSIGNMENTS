#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;
class scheduling
{
    static int count;
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> BurstTime;
    vector<int> complectionTime;
    vector<int> TurnAroundTime;
    vector<int> waitingTime;
    vector<int> priority;

public:
    void add(int at, int bt, int p)
    {
        count++;
        this->processid.push_back(count);
        this->arrivalTime.push_back(at);
        this->BurstTime.push_back(bt);
        this->priority.push_back(p);
    }
    void compute()
    {
        vector<int> RemainingTime = BurstTime;
        int n = processid.size();
        waitingTime.resize(n, 0);
        TurnAroundTime.resize(n, 0);
        complectionTime.resize(n, 0);
        int currentTime = 0;
        int completed = 0;
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
        set<int> isinreadyQueue;
        while (completed != n)
        {
            // adding all process in ready queue
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime and RemainingTime[i] > 0 and isinreadyQueue.find(i) == isinreadyQueue.end())
                {
                    readyQueue.push(i);
                    isinreadyQueue.insert(i);
                }
            }

            if (not readyQueue.empty())
            {
                int topIndex = readyQueue.top();
                readyQueue.pop();
                currentTime += RemainingTime[topIndex];
                RemainingTime[topIndex] = 0;
                complectionTime[topIndex] = currentTime;
                TurnAroundTime[topIndex] = complectionTime[topIndex] - arrivalTime[topIndex];
                waitingTime[topIndex] = TurnAroundTime[topIndex] - BurstTime[topIndex];
                completed++;
            }
            else
            {
                currentTime++;
            }
        }
    }
    void print()
    {
        cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;

        // Print the detailed information for each process
        for (int i = 0; i < processid.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += TurnAroundTime[i];
            cout << processid[i] << "\t\t" << arrivalTime[i] << "\t\t" << BurstTime[i] << "\t\t"
                 << priority[i] << "\t\t" << complectionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << TurnAroundTime[i] << endl;
        }

        // Print the average waiting time and turnaround time
        cout << "\nAverage Waiting Time: " << totalWaitingTime / processid.size() << endl;
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processid.size() << endl;
    }
};
int scheduling::count = 0;
int main()
{
    scheduling ps;
    // Adding processes to the system
    ps.add(0, 3, 2);
    ps.add(2, 5, 6);
    ps.add(1, 4, 3);
    ps.add(4, 2, 5);
    ps.add(6, 9, 7);
    ps.add(5, 4, 4);
    ps.add(7, 10, 10);

    // Perform Priority Scheduling computation
    ps.compute();

    // Print the result of Priority scheduling
    ps.print();

    return 0;
}
