#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;
class solution
{
public:
    void firstfit(vector<int> memoryBlock, vector<int> processSize)
    {
        for (auto x : processSize)
        {
            bool flag = true;
            for (int j = 0; j < memoryBlock.size(); j++)
            {
                if(x<=memoryBlock[j])
                {
                    cout<<x<<"  is allocated to frame "<<j+1<< "and size is "<<memoryBlock[j]<<endl;
                    memoryBlock[j]-=x;
                    flag=false;
                    break;
                }
            }
            if(flag)
            {
                cout<<x<<" is not allocated"<<endl;
            }
        }
    }
    void bestfit(vector<int>memoryBlock,vector<int>processSize)
    {
        bool flag=true;
        for (auto x: processSize)
        {
            int minSize=INT_MAX;
            int index=-1;
            for (int i=0;i<memoryBlock.size();i++)
            {
                if(x<=memoryBlock[i] and memoryBlock[i]<minSize)
                {
                    minSize=memoryBlock[i];
                    index=i;
                }
            }
            if(index!=-1)
            {
                cout<<x<<"  is allcated to frame "<<index+1<< " and size is "<<memoryBlock[index]<<endl;
                memoryBlock[index]-=x;
            }else
            {
                cout<<x<<"  cannot be allocated"<<endl;
            }
        }
    }
    void worstfit(vector<int>memoryBlock,vector<int>processSize)
    {
        bool flag=true;
        for (auto x: processSize)
        {
            int maxSize=INT_MIN;
            int index=-1;
            for (int i=0;i<memoryBlock.size();i++)
            {
                if(x<=memoryBlock[i] and memoryBlock[i]>maxSize)
                {
                    maxSize=memoryBlock[i];
                    index=i;
                }
            }
            if(index!=-1)
            {
                cout<<x<<"  is allcated to frame "<<index+1<< " and size is "<<memoryBlock[index]<<endl;
                memoryBlock[index]-=x;
            }else
            {
                cout<<x<<"  cannot be allocated"<<endl;
            }
        }
    }
};
int main()
{
vector<int >processSize={21,3,43,56,67,89,90};
vector<int>memoryblock={10,20,30,40,50,60,70,80,90};
solution soln;
cout<<"First Fit"<<endl;
soln.firstfit(memoryblock,processSize);
cout<<"Best Fit"<<endl;
soln.bestfit(memoryblock,processSize);
cout<<"Worst Fit"<<endl;
soln.worstfit(memoryblock,processSize);
    return EXIT_SUCCESS;
}