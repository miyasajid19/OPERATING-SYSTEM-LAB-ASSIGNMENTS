#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm> // for min function
#include <climits>   // for INT_MAX
using namespace std;

class RoundRobin
{
    vector<int> processes;
    vector<int> arrivalTime;
    vector<int> BurstTime;
    vector<int> RemainingTime;
    vector<int> ComplectionTime;
    vector<int> TurnAroundTime;
    vector<int> WaitingTime;
    vector<string> Queue;
    int timeQuantum;

public:
    RoundRobin(int TQ)
    {
        this->timeQuantum = TQ;
    }

    void addProcess(int pid, int At, int BT)
    {
        this->processes.push_back(pid);
        this->arrivalTime.push_back(At);
        this->BurstTime.push_back(BT);
        this->RemainingTime.push_back(BT);  // Initialize remaining time as burst time
        this->ComplectionTime.push_back(0);
        this->TurnAroundTime.push_back(0);
        this->WaitingTime.push_back(0);
    }

    void Turn_Around_Time()
    {
        // Calculate turnaround time after completion times are available
        for (int i = 0; i < processes.size(); i++)
            TurnAroundTime[i] = ComplectionTime[i] - arrivalTime[i];
    }

    void Waiting_Time()
    {
        // Waiting time is turnaround time minus burst time
        for (int i = 0; i < processes.size(); i++)
            WaitingTime[i] = TurnAroundTime[i] - BurstTime[i];
    }

    void Completion_Time()
    {
        vector<int> Remainingtime = RemainingTime;
        int currentTime = 0;
        int n = processes.size();
        queue<int> readyQueue;
        vector<bool> isInQueue(n, false); // Track if a process is in the queue

        while (true)
        {
            bool addedProcess = false;
            // Add processes that have arrived to the ready queue
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && Remainingtime[i] > 0 && !isInQueue[i])
                {
                    readyQueue.push(i);
                    isInQueue[i] = true;
                    addedProcess = true;
                }
            }

            // If no processes are in the ready queue, and no new processes are added, break
            if (readyQueue.empty() && !addedProcess)
            {
                // Find the smallest arrival time among remaining processes that have not finished
                int nextArrival = INT_MAX;
                for (int i = 0; i < n; i++)
                {
                    if (Remainingtime[i] > 0 && arrivalTime[i] > currentTime)
                    {
                        nextArrival = min(nextArrival, arrivalTime[i]);
                    }
                }

                // If no more processes are arriving, break out of the loop
                if (nextArrival == INT_MAX)
                    break;

                currentTime = nextArrival;
                continue;
            }

            // Process the first item in the queue
            if (!readyQueue.empty())
            {
                int i = readyQueue.front();
                readyQueue.pop();

                // Execute the process for time quantum or until it finishes
                if (Remainingtime[i] > timeQuantum)
                {
                    currentTime += timeQuantum;
                    Remainingtime[i] -= timeQuantum;
                    Queue.push_back("Process " + to_string(processes[i]));

                    // Re-queue if not finished
                    readyQueue.push(i);
                }
                else
                {
                    // Process completes
                    currentTime += Remainingtime[i];
                    ComplectionTime[i] = currentTime;
                    Remainingtime[i] = 0;
                    Queue.push_back("Process " + to_string(processes[i]));
                }
            }

            // Check if all processes are finished
            if (all_of(Remainingtime.begin(), Remainingtime.end(), [](int x)
                       { return x == 0; }))
                break;
        }
    }

    void display()
    {
        cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
        for (int i = 0; i < processes.size(); i++)
        {
            cout << processes[i] << "\t" << arrivalTime[i] << "\t" << BurstTime[i] << "\t"
                 << ComplectionTime[i] << "\t\t" << TurnAroundTime[i] << "\t\t" << WaitingTime[i] << endl;
        }
        cout << "Sequence:\n";
        for (auto x : Queue)
            cout << x << "\t";
        cout << endl;
    }
};

int main()
{
    RoundRobin RR(3); // Set time quantum to 2
    RR.addProcess(1, 1, 2);  // PID 1, Arrival Time 1, Burst Time 2
    RR.addProcess(2, 4, 2); // PID 2, Arrival Time 41, Burst Time 2
    RR.addProcess(3, 3, 2); // PID 3, Arrival Time 31, Burst Time 2
    RR.addProcess(4, 2, 12);// PID 4, Arrival Time 12, Burst Time 12
    RR.addProcess(5, 1, 1);  // PID 5, Arrival Time 1, Burst Time 1
    RR.addProcess(6, 0, 10); // PID 6, Arrival Time 0, Burst Time 10

    RR.Completion_Time();    // Calculate completion time
    RR.Turn_Around_Time();   // Calculate turnaround time
    RR.Waiting_Time();       // Calculate waiting time
    RR.display();            // Display results

    return EXIT_SUCCESS;
}
