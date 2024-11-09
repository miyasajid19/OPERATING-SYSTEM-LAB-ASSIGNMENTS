#include <iostream>
#include <vector>
using namespace std;

bool isSafeState(vector<vector<int>>& alloc, vector<vector<int>>& max, vector<vector<int>>& avail, int P, int R) {
    vector<int> work(R);
    vector<bool> finish(P, false);
    for (int i = 0; i < R; i++) {
        work[i] = avail[0][i]; // Initially, work = available
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                // Check if process i can finish
                for (int j = 0; j < R; j++) {
                    if (max[i][j] - alloc[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // If process i can finish, release its resources
                    for (int j = 0; j < R; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            return false; // If no process can proceed, system is in a deadlock state
        }
    }
    return true; // If all processes can finish, it's a safe state
}

int main() {
    int P, R;
    cout << "Enter number of processes and resources: ";
    cin >> P >> R;

    vector<vector<int>> alloc(P, vector<int>(R)), max(P, vector<int>(R)), avail(1, vector<int>(R));

    cout << "Enter the Allocation Matrix: \n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cin >> alloc[i][j];
        }
    }

    cout << "Enter the Maximum Matrix: \n";
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the Available Resources: \n";
    for (int i = 0; i < R; i++) {
        cin >> avail[0][i];
    }

    if (isSafeState(alloc, max, avail, P, R)) {
        cout << "System is in a safe state.\n";
    } else {
        cout << "System is in a deadlock state.\n";
    }

    return 0;
}
