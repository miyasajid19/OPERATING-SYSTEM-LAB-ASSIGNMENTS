#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;
class RoundRobin
{
    static int count;
    int timeQuantum;
    vector<int> processId;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> completionTime;
    vector<int> waitingTime;
    vector<int> turnAroundTime;
    queue<int> Queue;

public:
    RoundRobin(int TQ)
    {
        this->timeQuantum = TQ;
    }
    void add(int AT, int BT)
    {
        this->processId.push_back(count++);
        this->arrivalTime.push_back(AT);
        this->burstTime.push_back(BT);
    }
    void compute()
    {
        int n = processId.size();
        vector<int> remainingBurstTime = burstTime;
        completionTime.resize(n,0);
        waitingTime.resize(n,0);
        turnAroundTime.resize(n,0);
        int completed = 0;
        int currentTime = 0;
        while (completed != n)
        {
            bool processExecuted = false;
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime and remainingBurstTime[i] > 0)
                {
                    processExecuted = true;
                    if (remainingBurstTime[i] > timeQuantum)
                    {
                        currentTime += timeQuantum;
                        remainingBurstTime[i] -= timeQuantum;
                    }
                    else
                    {
                        currentTime += remainingBurstTime[i];
                        completionTime[i] = currentTime;
                        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
                        waitingTime[i] = turnAroundTime[i] - burstTime[i];
                        completed++;
                        Queue.push(i+1);
                        remainingBurstTime[i] = 0;
                    }
                }
            }
            if (not processExecuted)
            {
                currentTime++;
            }
        }
    }
    // Function to print the results
    void printRoundRobin()
    {
        cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;

        // Print the detailed information for each process
        for (int i = 0; i < processId.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += turnAroundTime[i];
            cout << processId[i] << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t"
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
        cout << "\nAverage Waiting Time: " << totalWaitingTime / processId.size() << endl;
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processId.size() << endl;
    }
};
int RoundRobin::count = 1;
int main()
{
    RoundRobin rr(2);

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