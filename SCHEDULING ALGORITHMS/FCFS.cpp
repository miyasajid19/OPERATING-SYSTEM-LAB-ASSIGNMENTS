#include <iostream>
#include <vector>
using namespace std;

class FCFS
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

    void computeFCFS()
    {
        completionTime.clear();
        waitingTime.clear();
        TurnAroundTime.clear();
        for (int i = 0; i < processid.size(); i++)
        {
            if (i == 0)
            {
                completionTime.push_back(arrivalTime[0] + BrustTime[0]);
            }
            else
            {
                completionTime.push_back(max(completionTime[i - 1], arrivalTime[i]) + BrustTime[i]);
            }
            waitingTime.push_back(completionTime[i] - arrivalTime[i] - BrustTime[i]);
            TurnAroundTime.push_back(completionTime[i] - arrivalTime[i]);
        }
    }

    void printFCFS()
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
int FCFS::count = 0;

int main()
{
    FCFS fcfs;
    fcfs.add(0, 1);
    fcfs.add(2, 5);
    fcfs.add(1, 3);
    fcfs.computeFCFS();
    fcfs.printFCFS();
    return 0;
}
