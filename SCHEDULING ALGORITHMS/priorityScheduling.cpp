#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

// Structure to represent a Process
struct Process {
    int id;           // Process ID
    int burstTime;    // CPU Burst time (time required to finish the process)
    int priority;     // Priority of the process (lower value means higher priority)
    int arrivalTime;  // Arrival time of the process
    int startTime;    // Time when the process starts executing
    int completionTime; // Time when the process finishes execution
    int waitingTime;  // Waiting time for the process
    int turnAroundTime; // Turnaround time for the process
};

// Comparison function for sorting processes based on arrival time and priority
bool compareArrivalTime(Process a, Process b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.priority < b.priority;
    return a.arrivalTime < b.arrivalTime;
}

// Function to calculate waiting time and turn around time
void calculateTimes(vector<Process>& processes) {
    int totalTime = 0;  // Keep track of total elapsed time
    for (int i = 0; i < processes.size(); i++) {
        Process &p = processes[i];
        
        // Start time is either when the process arrives or after previous process finishes
        if (totalTime < p.arrivalTime) {
            totalTime = p.arrivalTime;
        }
        p.startTime = totalTime;
        p.completionTime = p.startTime + p.burstTime;
        p.turnAroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnAroundTime - p.burstTime;

        totalTime = p.completionTime;  // Update the current time
    }
}

// Priority Scheduling (Non-Preemptive)
void priorityScheduling(vector<Process>& processes) {
    // Sort processes by arrival time, and if they arrive at the same time, by priority
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // Calculate the completion time, turn-around time, and waiting time for each process
    calculateTimes(processes);

    // Output the results
    cout << "\nProcess ID | Arrival Time | Burst Time | Priority | Start Time | Completion Time | Waiting Time | Turnaround Time\n";
    cout << "-------------------------------------------------------------------------------------------\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" 
             << p.arrivalTime << "\t\t"
             << p.burstTime << "\t\t"
             << p.priority << "\t\t"
             << p.startTime << "\t\t"
             << p.completionTime << "\t\t"
             << p.waitingTime << "\t\t"
             << p.turnAroundTime << "\n";
    }

    // Calculate averages
    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (const auto& p : processes) {
        avgWaitingTime += p.waitingTime;
        avgTurnaroundTime += p.turnAroundTime;
    }
    avgWaitingTime /= processes.size();
    avgTurnaroundTime /= processes.size();

    cout << "\nAverage Waiting Time: " << avgWaitingTime;
    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    int n;  // Number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input for processes
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << "\n";
        processes[i].id = i + 1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Priority: ";
        cin >> processes[i].priority;
    }

    // Perform priority scheduling
    priorityScheduling(processes);

    return 0;
}
