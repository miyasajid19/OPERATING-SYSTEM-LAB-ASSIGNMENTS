#include <iostream>
#include <vector>
#include <algorithm>
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
    vector<int> queues;
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
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && remainingBurstTime[i] > 0)
                {
                    done = false;
                    if (remainingBurstTime[i] < minRT)
                    {
                        minRT = remainingBurstTime[i];
                        idx = i;
                    }
                }
            }

            if (idx != -1)
            {
                remainingBurstTime[idx]--;
                if (remainingBurstTime[idx] == 0)
                {
                    completed++;
                    minRT = INT_MAX;
                    completionTime[idx] = currentTime + 1;
                    TurnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                    waitingTime[idx] = TurnAroundTime[idx] - BrustTime[idx];
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
        for (int i = 0; i < processid.size(); i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += TurnAroundTime[i];
            cout << processid[i] << "\t\t" << arrivalTime[i] << "\t\t" << BrustTime[i] << "\t\t" << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << TurnAroundTime[i] << "\n";
        }
        cout << "Average Waiting Time: " << totalWaitingTime / processid.size() << "\n";
        cout << "Average Turnaround Time: " << totalTurnaroundTime / processid.size() << "\n";
    }
};
int SRJF::count = 0;

int main()
{
    SRJF srjf;
    srjf.add(0, 7);
    srjf.add(2, 4);
    srjf.add(4, 1);
    srjf.add(5, 4);
    srjf.computeSRJF();
    srjf.printSRJF();
    return 0;
}
