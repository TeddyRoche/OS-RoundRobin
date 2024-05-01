#include "RoundRobin.h"  // Include the header for the RoundRobin class
#include <vector>
#include <iostream>

// Assuming that the 'Process' structure and color constants are defined in RoundRobinDylan.h
// If not, they need to be defined or included appropriately.

int main() {
    // Define a list of processes with IDs, burst times, and arrival times
    std::vector<Process> processes = {
        Process(1, 5, 0),
        Process(2, 3, 0),
        Process(3, 6, 0),
        Process(4, 1, 0),
        Process(5, 4, 0)
    };

    int quantum = 2; // Quantum time slice

    // Instantiate the RoundRobin scheduler with the defined processes and quantum
    RoundRobin scheduler(processes, quantum);

    // Run the round-robin scheduling
    scheduler.runRoundRobin();

    return 0;
}