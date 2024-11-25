#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <queue>
using namespace std;
class scheduling
{
    static int count;
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> priority;
    vector<int> completionTime;
    vector<int> TurnAroundTime;
    vector<int> WaitingTime;

public:
    void add(int at, int bt, int p)
    {
        count++;
        this->processid.push_back(count);
        this->arrivalTime.push_back(at);
        this->burstTime.push_back(bt);
        this->priority.push_back(p);
    }
    void compute()
    {
        vector<int> remainingTime = burstTime;
        int n = processid.size();
        WaitingTime.resize(n, 0);
        completionTime.resize(n, 0);
        TurnAroundTime.resize(n, 0);
        int completed = 0;
        int currentTime = 0;
        auto compare = [&](int a, int b)
        {
            if (priority[a] == priority[b])
                return arrivalTime[a] > arrivalTime[b];
            return priority[a] > priority[b];
        };
        priority_queue<int, vector<int>, decltype(compare)> readyQueue(compare);
        set<int> isinReadyQueue;
        while (completed != n)
        {
            // adding in queue
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime and remainingTime[i] > 0 and isinReadyQueue.find(i) == isinReadyQueue.end())
                {
                    readyQueue.push(i);
                    isinReadyQueue.insert(i);
                }
            }

            if (not readyQueue.empty())
            {
                int topIndex = readyQueue.top();
                readyQueue.pop();
                if (remainingTime[topIndex] > 0 and priority[topIndex] > priority[readyQueue.top()])
                {
                    // need to preempt
                    readyQueue.push(topIndex);
                    continue;
                }
                remainingTime[topIndex]--;
                currentTime++;
                if (remainingTime[topIndex] == 0)
                {
                    completionTime[topIndex] = currentTime;
                    TurnAroundTime[topIndex] = completionTime[topIndex] - arrivalTime[topIndex];
                    WaitingTime[topIndex] = TurnAroundTime[topIndex] - burstTime[topIndex];
                    completed++;
                }
                else
                {
                    readyQueue.push(topIndex);
                }
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
            totalWaitingTime += WaitingTime[i];
            totalTurnaroundTime += TurnAroundTime[i];
            cout << processid[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t"
                 << priority[i] << "\t\t" << completionTime[i] << "\t\t" << WaitingTime[i] << "\t\t" << TurnAroundTime[i] << endl;
        }

        // Print the average waiting time and turnaround time
        cout << "\nAverage Waiting Time: " << totalWaitingTime / processid.size() << endl;
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processid.size() << endl;
    }
};
int scheduling ::count = 0;
int main()
{
    scheduling ps;
    ps.add(0, 3, 3);
    ps.add(1, 4, 2);
    ps.add(2, 6, 4);
    ps.add(3, 4, 6);
    ps.add(5, 2, 10);

    // Perform Priority Scheduling computation
    ps.compute();

    // Print the result of Priority scheduling
    ps.print();

    return 0;
}
