#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;
class scheduling
{
    static int count;
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> completionTime;
    vector<int> waitingTime;
    vector<int> turnAroundTime;
    int timeQuantum;
    queue<int> Queue;

public:
    scheduling(int tq)
    {
        this->timeQuantum = tq;
    }
    void add(int at, int bt)
    {
        count++;
        this->processid.push_back(count);
        this->arrivalTime.push_back(at);
        this->burstTime.push_back(bt);
    }
    void compute()
    {
        vector<int> remaining = burstTime;
        int n = processid.size();
        waitingTime.resize(n, 0);
        completionTime.resize(n, 0);
        turnAroundTime.resize(n, 0);
        int completed = 0;
        int currentTime = 0;
        while (completed != n)
        {
            bool canExecute = false;
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime and remaining[i] > 0)
                {
                    canExecute = true;
                    if (remaining[i] > timeQuantum)
                    {
                        currentTime += timeQuantum;
                        remaining[i] -= timeQuantum;
                    }
                    else
                    {
                        currentTime += remaining[i];
                        remaining[i] = 0;
                        completed++;
                        Queue.push(i);
                        completionTime[i] = currentTime;
                        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
                        waitingTime[i] = turnAroundTime[i] - burstTime[i];
                    }
                }
            }
            if (not canExecute)
            {
                currentTime++;
            }
        }
    }
    void printRoundRobin()
    {
        cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;

        // Print the detailed information for each process
        for (int i = 0; i < processid.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += turnAroundTime[i];
            cout << processid[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t"
                 << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }

        // Print the sequence of execution (queue)
        cout << "\nExecution Sequence (Process IDs): ";
        while (!Queue.empty())
        {
            cout << Queue.front() << " ";
            Queue.pop();
        }
        cout << endl;

        // Print the average waiting time and turnaround time
        cout << "\nAverage Waiting Time: " << totalWaitingTime / processid.size() << endl;
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processid.size() << endl;
    }
};
int scheduling::count = 1;
int main()
{
    scheduling rr(2);

    // Adding processes to the system
    rr.add(0, 7);   // Process 1, Arrival time = 0, Burst time = 10
    rr.add(10, 30); // Process 2, Arrival time = 1, Burst time = 5
    rr.add(20, 13); // Process 3, Arrival time = 2, Burst time = 8

    // Perform Round Robin computation
    rr.compute();

    // Print the result of Round Robin scheduling
    rr.printRoundRobin();

    return EXIT_SUCCESS;
}