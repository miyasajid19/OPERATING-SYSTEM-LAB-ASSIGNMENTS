#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits>
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
        waitingTime.resize(n, 0);
        completionTime.resize(n, 0);
        turnAroundTime.resize(n, 0);
        int completed = 0;
        int currentTime = 0;
        vector<int> remaining = burstTime;
        while (completed != n)
        {
            bool flag = true;
            int minAt = INT_MAX;
            int index = -1;
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime and burstTime[i] < minAt and remaining[i] > 0)
                {
                    minAt = arrivalTime[i];
                    index = i;
                }
            }
            if (index != -1)
            {
                currentTime += remaining[index];
                remaining[index] = 0;
                completed++;
                completionTime[index] = currentTime;
                turnAroundTime[index] = completionTime[index] - arrivalTime[index];
                waitingTime[index] = turnAroundTime[index] - burstTime[index];
                q.push(processId[index]);
            }
            else
            {
                currentTime++;
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
int scheduling ::count = 1;
int main()
{
    scheduling fcfs;
    fcfs.add(5, 3);
    fcfs.add(3, 2);
    fcfs.add(10, 3);
    fcfs.add(2, 1);
    fcfs.add(4, 2);
    fcfs.compute();
    fcfs.display();

    return EXIT_SUCCESS;
}
