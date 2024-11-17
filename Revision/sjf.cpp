#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits> // for INT_MAX
using namespace std;

class SJF
{
    static int count;
    vector<int> processid;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> completionTime;
    vector<int> turnAroundTime;
    vector<int> waitingTime;
    queue<int> q;

public:
    void add(int AT, int BT)
    {
        this->processid.push_back(count++);
        this->arrivalTime.push_back(AT);
        this->burstTime.push_back(BT);
    }

    void Compute()
    {
        int currentTime = 0;
        int completed = 0;
        int n = processid.size();
        vector<bool> isCompleted(n, false);
        completionTime.resize(n);
        waitingTime.resize(n);
        turnAroundTime.resize(n);

        while (completed != n)
        {
            int index = -1;
            int minimumBT = INT_MAX;

            // Find the process with the minimum burst time that has arrived
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && !isCompleted[i] && burstTime[i] < minimumBT)
                {
                    minimumBT = burstTime[i];
                    index = i;
                }
            }

            // If a process was found to schedule, do so
            if (index != -1)
            {
                currentTime += burstTime[index];
                completionTime[index] = currentTime;
                turnAroundTime[index] = completionTime[index] - arrivalTime[index];
                waitingTime[index] = turnAroundTime[index] - burstTime[index];
                isCompleted[index] = true;
                completed++;
                q.push(index+1);
            }
            else
            {
                currentTime++; // Increment time if no process is ready to execute
            }
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
            cout << waitingTime[i] << "\t\t";
            cout << turnAroundTime[i] << endl;

            avgTAT += turnAroundTime[i];
            avgWT += waitingTime[i];
        }
        cout<<"Sequence :: ";
while(not q.empty())
{
    cout<<q.front()<<"\t";
    q.pop();
}
cout<<endl;
        cout << "Average Waiting Time: " << avgWT / processid.size() << endl;
        cout << "Average Turn Around Time: " << avgTAT / processid.size() << endl;
    }
};

int SJF::count = 1;

int main()
{
    SJF sjf;
    sjf.add(0,4);
    sjf.add(0,3);
    sjf.add(0,2);
    sjf.add(0,3);
    sjf.Compute();
    sjf.display();
    return EXIT_SUCCESS;
}
