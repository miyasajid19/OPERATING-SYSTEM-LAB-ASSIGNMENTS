#include <iostream>
#include <vector>
using namespace std;

class FCFS
{
    static int count;

public:
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> completionTime;
    vector<int> turnAroundTime;
    vector<int> waitingtime;

    void add(int AT, int BT)
    {
        processid.push_back(count++);
        arrivalTime.push_back(AT);
        burstTime.push_back(BT);
    }

    void Sort()
    {
        for (int i = 0; i < processid.size(); i++)
        {
            for (int j = 0; j < processid.size() - i - 1; j++)
            {
                if (arrivalTime[j] > arrivalTime[j + 1])
                {
                    swap(arrivalTime[j], arrivalTime[j + 1]);
                    swap(burstTime[j], burstTime[j + 1]);
                    swap(processid[j], processid[j + 1]);
                }
            }
        }
    }

    void Compute()
    {
        Sort();
        turnAroundTime.clear();
        waitingtime.clear();
        completionTime.clear();

        for (int i = 0; i < processid.size(); i++)
        {
            if (i == 0)
            {
                completionTime.push_back(arrivalTime[i] + burstTime[i]);
            }
            else
            {
                int startTime = max(completionTime[i - 1], arrivalTime[i]);
                completionTime.push_back(startTime + burstTime[i]);
            }
            turnAroundTime.push_back(completionTime[i] - arrivalTime[i]);
            waitingtime.push_back(turnAroundTime[i] - burstTime[i]);
        }
    }

    void display()
    {
        float avgTAT = 0;
        float avgWT = 0;

        cout << "Process Id\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurn Around Time\n";
        for (int i = 0; i < processid.size(); i++)
        {
            cout << processid[i] << "\t\t";
            cout << arrivalTime[i] << "\t\t";
            cout << burstTime[i] << "\t\t";
            cout << completionTime[i] << "\t\t";
            cout << waitingtime[i] << "\t\t";
            cout << turnAroundTime[i] << endl;

            avgTAT += turnAroundTime[i];
            avgWT += waitingtime[i];
        }

        cout << "Average Waiting Time: " << avgWT / processid.size() << endl;
        cout << "Average Turn Around Time: " << avgTAT / processid.size() << endl;
    }
};

int FCFS::count = 1;

int main()
{
    FCFS fcfs;
    fcfs.add(5, 3);
    fcfs.add(3, 2);
    fcfs.add(10, 3);
    fcfs.add(2, 1);
    fcfs.add(4, 2);
    fcfs.Compute();
    fcfs.display();

    return EXIT_SUCCESS;
}
