#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;
class scheduling
{
    static int count;
    vector<int> processId;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> completionTime;
    vector<int> waitingTime;
    vector<int> turnAroundTime;
    queue<int> q;

public:
    void add(int at, int bt)
    {
        this->processId.push_back(count++);
        this->arrivalTime.push_back(at);
        this->burstTime.push_back(bt);
    }
    void compute()
    {
        int n = processId.size();
        vector<int> remainging = burstTime;
        waitingTime.resize(n, 0);
        completionTime.resize(n, 0);
        turnAroundTime.resize(n, 0);
        int completed = 0;
        int currenttime = 0;
        while (completed != n)
        {
            int minBT = INT_MAX;
            int index = -1;
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currenttime and remainging[i] > 0 and remainging[i] < minBT)
                {
                    minBT = remainging[i];
                    index = i;
                }
            }
            if (index != -1)
            {
                currenttime++;
                remainging[index]--;
                if (remainging[index] == 0)
                {
                    completed++;
                    currenttime += remainging[index];
                    remainging[index] = 0;
                    completionTime[index] = currenttime;
                    turnAroundTime[index] = completionTime[index] - arrivalTime[index];
                    waitingTime[index] = turnAroundTime[index] - burstTime[index];
                    q.push(processId[index]);
                }
            }
            else
            {
                currenttime++;
            }
        }
    }
    void display()
    {
        float avgTAT = 0;
        float avgWT = 0;

        cout << "Process Id\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurn Around Time\n";
        for (int i = 0; i < processId.size(); i++)
        {
            cout << processId[i] << "\t\t";
            cout << arrivalTime[i] << "\t\t";
            cout << burstTime[i] << "\t\t";
            cout << completionTime[i] << "\t\t";
            cout << waitingTime[i] << "\t\t";
            cout << turnAroundTime[i] << endl;

            avgTAT += turnAroundTime[i];
            avgWT += waitingTime[i];
        }
        cout << "Sequence :: ";
        while (not q.empty())
        {
            cout << q.front() << "\t";
            q.pop();
        }
        cout << endl;
        cout << "Average Waiting Time: " << avgWT / processId.size() << endl;
        cout << "Average Turn Around Time: " << avgTAT / processId.size() << endl;
    }
};

int scheduling::count = 1;

int main()
{
    scheduling srjf;
      srjf.add(2, 6); // Process 1 arrives at time 2, burst time 6
    srjf.add(5, 2); // Process 2 arrives at time 5, burst time 2
    srjf.add(1, 8); // Process 3 arrives at time 1, burst time 8
    srjf.add(0, 3); // Process 4 arrives at time 0, burst time 3
    srjf.add(4, 4); // Process 5 arrives at time 4, burst time 4

    srjf.compute();
    srjf.display();

    return 0;
}