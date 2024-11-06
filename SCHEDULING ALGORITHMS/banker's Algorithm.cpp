#include <iostream>
#include <vector>

using namespace std;

// Function to check if the system is in a safe state
bool isSafeState(const vector<int>& available, const vector<vector<int>>& maximum, const vector<vector<int>>& allocation, vector<int>& safeSequence) {
    int numProcesses = maximum.size();
    int numResources = available.size();
    
    vector<int> work = available;  // Work vector (initially equal to available resources)
    vector<bool> finish(numProcesses, false);  // Finish vector to track if a process can complete
    
    int count = 0;  // To count the number of processes that can finish
    while (count < numProcesses) {
        bool progressMade = false;
        
        // Try to find a process that can finish
        for (int i = 0; i < numProcesses; ++i) {
            if (!finish[i]) {
                // Calculate the need for process i
                vector<int> need(numResources);
                bool canFinish = true;
                for (int j = 0; j < numResources; ++j) {
                    need[j] = maximum[i][j] - allocation[i][j];
                    if (need[j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                
                // If process i can finish
                if (canFinish) {
                    // "Allocate" the resources to process i
                    for (int j = 0; j < numResources; ++j) {
                        work[j] += allocation[i][j];  // Add allocated resources back to work
                    }
                    finish[i] = true;  // Mark the process as finished
                    safeSequence.push_back(i);  // Add process i to safe sequence
                    count++;  // Increment finished process count
                    progressMade = true;  // Indicate progress was made
                    break;
                }
            }
        }
        
        // If no process could finish, the system is in an unsafe state
        if (!progressMade) {
            return false;
        }
    }
    
    return true;
}

// Function to simulate resource allocation using the Banker's Algorithm
void bankersAlgorithm(const vector<int>& available, const vector<vector<int>>& maximum, const vector<vector<int>>& allocation) {
    vector<int> safeSequence;
    bool safe = isSafeState(available, maximum, allocation, safeSequence);
    
    if (safe) {
        cout << "The system is in a safe state." << endl;
        cout << "Safe sequence is: ";
        for (int i = 0; i < safeSequence.size(); ++i) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "The system is in an unsafe state." << endl;
    }
}

int main() {
    // Number of processes and resources
    int P = 3;  // Number of processes
    int R = 4;  // Number of resources

    // Example 1: Safe state (safe sequence exists)
    
    cout << "Test Case 1: Safe State (Safe Sequence Exists)" << endl;
    // Available resources in the system
    vector<int> available = {3, 3, 2, 2};  // Available instances of each resource type
    
    // Maximum demand matrix (Maximum[i][j] is the max demand of process i for resource j)
    vector<vector<int>> maximum = {
        {7, 5, 3, 2},  // Process 0
        {3, 2, 2, 1},  // Process 1
        {9, 0, 2, 3},  // Process 2
    };
    
    // Allocation matrix (Allocation[i][j] is the number of instances of resource j allocated to process i)
    vector<vector<int>> allocation = {
        {0, 1, 0, 2},  // Process 0
        {2, 0, 0, 1},  // Process 1
        {3, 0, 2, 2},  // Process 2
    };
    
    // Run the Banker's Algorithm for Safe State
    bankersAlgorithm(available, maximum, allocation);
    
    // Example 2: Unsafe state (no safe sequence exists)
    
    cout << "\nTest Case 2: Unsafe State (No Safe Sequence)" << endl;
    // Available resources in the system
    available = {3, 2, 2, 2};  // Available instances of each resource type
    
    // Maximum demand matrix (Maximum[i][j] is the max demand of process i for resource j)
    maximum = {
        {7, 5, 3, 2},  // Process 0
        {3, 2, 2, 1},  // Process 1
        {9, 0, 2, 3},  // Process 2
    };
    
    // Allocation matrix (Allocation[i][j] is the number of instances of resource j allocated to process i)
    allocation = {
        {0, 1, 0, 2},  // Process 0
        {2, 1, 1, 1},  // Process 1
        {3, 0, 2, 2},  // Process 2
    };
    
    // Run the Banker's Algorithm for Unsafe State
    bankersAlgorithm(available, maximum, allocation);
    
    return 0;
}
