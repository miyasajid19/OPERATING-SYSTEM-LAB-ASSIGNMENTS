#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SJF
{
    static int count;

public:
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> BrustTime;
    vector<int> waitingTime;
    vector<int> completionTime;
    vector<int> TurnAroundTime;

    void add(int AT, int BT)
    {
        count++;
        this->processid.push_back(count);
        this->arrivalTime.push_back(AT);
        this->BrustTime.push_back(BT);
    }

    void computeSJF()
    {
        int n = processid.size();
        vector<bool> done(n, false);
        int currentTime = 0, completed = 0;

        completionTime.resize(n);
        waitingTime.resize(n);
        TurnAroundTime.resize(n);

        while (completed != n)
        {
            int idx = -1;
            int minBT = INT_MAX;

            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && !done[i] && BrustTime[i] < minBT)
                {
                    minBT = BrustTime[i];
                    idx = i;
                }
            }

            if (idx != -1)
            {
                currentTime += BrustTime[idx];
                completionTime[idx] = currentTime;
                waitingTime[idx] = completionTime[idx] - arrivalTime[idx] - BrustTime[idx];
                TurnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                done[idx] = true;
                completed++;
            }
            else
            {
                currentTime++;
            }
        }
    }

    void printSJF()
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
int SJF::count = 0;

int main()
{
    SJF sjf;
    sjf.add(0, 7);
    sjf.add(2, 4);
    sjf.add(4, 1);
    sjf.add(5, 4);
    sjf.computeSJF();
    sjf.printSJF();
    return 0;
}
