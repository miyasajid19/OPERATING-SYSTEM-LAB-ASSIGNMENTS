#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class AllocationStrategy
{
public:
    void bestFit(vector<int> memoryBlock, vector<int> processSize)
    {
        for (int i = 0; i < processSize.size(); i++)
        {
            int minimumBlock = INT_MAX, index = -1;
            for (int j = 0; j < memoryBlock.size(); j++)
            {
                if (processSize[i] <= memoryBlock[j] && memoryBlock[j] < minimumBlock)
                {
                    minimumBlock = memoryBlock[j];
                    index = j;
                }
            }
            if (index != -1)
            {
                cout << processSize[i] << " is allocated in frame " << index << endl;
                memoryBlock[index] -= processSize[i];
            }
            else
            {
                cout << processSize[i] << " cannot be allocated" << endl;
            }
        }
    }

    void worstFit(vector<int> memoryBlock, vector<int> processSize)
    {
        for (int i = 0; i < processSize.size(); i++)
        {
            int maximumBlock = INT_MIN, index = -1;
            for (int j = 0; j < memoryBlock.size(); j++)
            {
                if (processSize[i] <= memoryBlock[j] && memoryBlock[j] > maximumBlock)
                {
                    maximumBlock = memoryBlock[j];
                    index = j;
                }
            }
            if (index != -1)
            {
                cout << processSize[i] << " is allocated in frame " << index << endl;
                memoryBlock[index] -= processSize[i];
            }
            else
            {
                cout << processSize[i] << " cannot be allocated" << endl;
            }
        }
    }

    void firstFit(vector<int> memoryBlock, vector<int> processSize)
    {
        for (int i = 0; i < processSize.size(); i++)
        {
            bool allocated = false;
            for (int j = 0; j < memoryBlock.size(); j++)
            {
                if (processSize[i] <= memoryBlock[j])
                {
                    cout << processSize[i] << " is allocated in frame " << j << endl;
                    memoryBlock[j] -= processSize[i];
                    allocated = true;
                    break;
                }
            }
            if (!allocated)
            {
                cout << processSize[i] << " cannot be allocated" << endl;
            }
        }
    }
};

int main()
{
    vector<int> memoryBlock = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    AllocationStrategy alloc;

    cout << "\nFirst Fit Allocation:" << endl;
    alloc.firstFit(memoryBlock, processSize);

    cout << "Best Fit Allocation:" << endl;
    alloc.bestFit(memoryBlock, processSize);

    cout << "\nWorst Fit Allocation:" << endl;
    alloc.worstFit(memoryBlock, processSize);

    return EXIT_SUCCESS;
}
