#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class bankers_algorithm{
  vector<int>processes;
  vector<vector<int>>maxResources;
  vector<vector<int>>Allocated;
  vector<vector<int>>Needed;
  vector<int>Available;
  queue<int> safeSequece;
  int No_of_resources;
  static int count;
  public:
  bankers_algorithm(int no_of_resources, vector<int>available)
  {
      this->No_of_resources=no_of_resources;
      this->Available=available;
  }
  void allocate(vector<int>MaxRequired,vector<int>Allocated)
  {
      count++;
      this->processes.push_back(count);
      this->maxResources.push_back(MaxRequired);
      this->Allocated.push_back(Allocated);
  }
  void checkSafety()
  {
      //calculating need matrix
      for (int i=0;i<count;i++)
      {
          vector<int>temp;
          for(int j=0;j<No_of_resources;j++)
          {
              temp.push_back(maxResources[i][j]-Allocated[i][j]);
          }
          Needed.push_back(temp);
      }
      //working vector
      vector<int>work=Available;
      //book mark for the completion of the process
      vector<bool>finished(count-1,false);
      int completed=0;
      while(completed<count)
      {
          bool found=false;
          for (int i=0;i<count;i++)
          {
              if(not finished[i])
              {
                  bool canAllocate=true;
                  for (int j=0;j<No_of_resources;j++)
                  {
                     if(Needed[i][j]>Available[j]){
                         canAllocate=false;
                         break;
                     }
                  }
                  if(canAllocate)
                  {
                      for (int j=0;j<No_of_resources;j++)
                      {
                          Available[i]+=Needed[i][j];}
                          completed++;
                          finished[i]=true;
                          found=true;
                          safeSequece.push(processes[i]);
                      }
                  }
              
          }
          if(not found)
          {
          cout<<"Not in safe sequence"<<endl;
          break;
          }
      }
     cout<<" is in safe sequence"<<endl;
     while(not safeSequece.empty())
     {
         cout<< safeSequece.front()<<"\t";
         safeSequece.pop();
     }
     cout<<endl;
  }
};
int bankers_algorithm :: count=0;
int main()
{
     // Example Input
    int no_of_resources = 3;
    vector<int> available = {3, 3, 2};

    bankers_algorithm bankers(no_of_resources, available);

    // Define processes with maxRequired and allocated resources
    bankers.allocate({7, 5, 3}, {0, 1, 0});
    bankers.allocate({3, 2, 2}, {2, 0, 0});
    bankers.allocate({9, 0, 2}, {3, 0, 2});
    bankers.allocate({2, 2, 2}, {2, 1, 1});
    bankers.allocate({4, 3, 3}, {0, 0, 2});

    bankers.checkSafety();

    return EXIT_SUCCESS;


    
    
    
}