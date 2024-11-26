#include <iostream>
#include <vector>
using namespace std;

class BankersAlgorithm
{
    static int count;
    vector<int> processid;
    vector<vector<int>> maxRequired;
    vector<vector<int>> allocated;
    vector<vector<int>> need;
    vector<int> available;
    int no_of_resources;

public:
    BankersAlgorithm(int no_of_resources, vector<int> available)
    {
        this->no_of_resources = no_of_resources;
        this->available = available;
    }

    void allocate(vector<int> maxRequired, vector<int> allocated)
    {
        processid.push_back(count++);
        this->allocated.push_back(allocated);
        this->maxRequired.push_back(maxRequired);
    }

    vector<int> safeSequence()
    {
        need.clear();
        int n = processid.size();
        for (int i = 0; i < n; i++)
        {
            vector<int> temp;
            for (int j = 0; j < no_of_resources; j++)
            {
                temp.push_back(maxRequired[i][j] - allocated[i][j]);
            }
            need.push_back(temp);
        }
        vector<bool> isFinished(n, false);
        int alloted = 0;
        vector<vector<int>> work = need;
        vector<int> ans;
        while (alloted < n)
        {
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                if (not isFinished[i])
                {
                    bool canallocate = true;
                    for (int j = 0; j < no_of_resources; j++)
                    {
                        if (work[i][j] > available[j])
                        {
                            canallocate = false;
                            break;
                        }
                    }
                    if (canallocate)
                    {
                        isFinished[i] = true;
                        for (int j = 0; j < no_of_resources; j++)
                        {
                            available[j] += work[i][j];
                        }
                        ans.push_back(processid[i]);
                        alloted = false;
                    }
                }
            }
            if (not found)
            {
                return {};
            }
        }
        return ans;
    }
};

int BankersAlgorithm::count = 1;

int main()
{
    // Example Input
    int no_of_resources = 3;
    vector<int> available = {3, 3, 2};

    BankersAlgorithm bankers(no_of_resources, available);

    // Define processes with maxRequired and allocated resources
    bankers.allocate({7, 5, 3}, {0, 1, 0});
    bankers.allocate({3, 2, 2}, {2, 0, 0});
    bankers.allocate({9, 0, 2}, {3, 0, 2});
    bankers.allocate({2, 2, 2}, {2, 1, 1});
    bankers.allocate({4, 3, 3}, {0, 0, 2});

    vector<int> safeSequence = bankers.safeSequence();

    if (!safeSequence.empty())
    {
        cout << "Safe Sequence: ";
        for (int id : safeSequence)
        {
            cout << "P" << id << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "The system is in an unsafe state!" << endl;
    }

    return EXIT_SUCCESS;
}
