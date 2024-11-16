#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // for min function
#include <climits>   // for INT_MAX
using namespace std;

class RoundRobin
{
    vector<int> processes;      // Process IDs
    vector<int> arrivalTime;    // Arrival times
    vector<int> burstTime;      // Burst times
    vector<int> remainingTime;  // Remaining burst times
    vector<int> waitingTime;    // Waiting times
    vector<int> turnaroundTime; // Turnaround times
    vector<int> completionTime; // Completion times
    vector<int> executionOrder; // Order in which processes were executed
    int timeQuantum;            // Time quantum for Round Robin

public:
    RoundRobin(int TQ)
    {
        this->timeQuantum = TQ;
    }

    // Add a process with its ID, arrival time, and burst time
    void addProcess(int pid, int At, int BT)
    {
        processes.push_back(pid);
        arrivalTime.push_back(At);
        burstTime.push_back(BT);
        remainingTime.push_back(BT);  // Initialize remaining time as burst time
        completionTime.push_back(0);
        turnaroundTime.push_back(0);
        waitingTime.push_back(0);
    }

    // Function to calculate waiting time for all processes
    void findWaitingTime()
    {
        int n = processes.size();
        vector<int> rem_bt = remainingTime;  // Copy of remaining burst times
        int t = 0;  // Current time
        while (1)
        {
            bool done = true;

            // Traverse all processes one by one repeatedly
            for (int i = 0; i < n; i++)
            {
                // If burst time of a process is greater than 0, then only need to process further
                if (rem_bt[i] > 0)
                {
                    done = false; // There is a pending process

                    if (rem_bt[i] > timeQuantum)
                    {
                        t += timeQuantum;  // Increase the time by quantum
                        rem_bt[i] -= timeQuantum;
                    }
                    else
                    {
                        // Process completes
                        t = t + rem_bt[i];
                        waitingTime[i] = t - burstTime[i];  // Waiting time = current time - burst time
                        rem_bt[i] = 0;  // Process is fully executed
                    }
                }
            }

            // If all processes are done, break the loop
            if (done)
                break;
        }
    }

    // Function to calculate turnaround time for all processes
    void findTurnaroundTime()
    {
        int n = processes.size();
        for (int i = 0; i < n; i++)
            turnaroundTime[i] = burstTime[i] + waitingTime[i];  // TAT = WT + BT
    }

    // Function to calculate completion time for all processes
    void findCompletionTime()
    {
        int n = processes.size();
        int t = 0;  // Current time
        vector<int> rem_bt = remainingTime;

        while (1)
        {
            bool done = true;
            for (int i = 0; i < n; i++)
            {
                if (rem_bt[i] > 0)
                {
                    done = false;

                    if (rem_bt[i] > timeQuantum)
                    {
                        t += timeQuantum;
                        rem_bt[i] -= timeQuantum;
                    }
                    else
                    {
                        t += rem_bt[i];
                        completionTime[i] = t;
                        rem_bt[i] = 0;
                    }
                }
            }

            if (done)
                break;
        }
    }

    // Function to display the results
    void display()
    {
        int n = processes.size();
        cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
        for (int i = 0; i < n; i++)
        {
            cout << processes[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << "\t"
                 << completionTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << endl;
        }

        // Display execution order (queue of process execution)
        cout << "Execution Order: ";
        for (auto pid : executionOrder)
            cout << pid << " ";
        cout << endl;
    }

    // Function to calculate and display average times
    void calculateAvgTime()
    {
        int n = processes.size();
        int totalWT = 0, totalTAT = 0;

        for (int i = 0; i < n; i++)
        {
            totalWT += waitingTime[i];
            totalTAT += turnaroundTime[i];
        }

        cout << "Average Waiting Time = " << (float)totalWT / n << endl;
        cout << "Average Turnaround Time = " << (float)totalTAT / n << endl;
    }

    // Main function to execute the scheduling
    void executeRoundRobin()
    {
        findCompletionTime();  // Calculate the completion times
        findWaitingTime();     // Calculate the waiting times
        findTurnaroundTime();  // Calculate the turnaround times
        display();             // Display process info
        calculateAvgTime();    // Display average times
    }
};

// Driver code
int main()
{
    RoundRobin rr(2); // Time quantum = 2
    rr.addProcess(1, 0, 10);  // PID 1, Arrival Time 0, Burst Time 10
    rr.addProcess(2, 1, 5);   // PID 2, Arrival Time 1, Burst Time 5
    rr.addProcess(3, 2, 8);   // PID 3, Arrival Time 2, Burst Time 8

    rr.executeRoundRobin();  // Execute the Round Robin scheduling

    return 0;
}
