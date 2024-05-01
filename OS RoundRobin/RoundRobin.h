#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

// Define color codes for console output
#define CYAN_Color "\033[1;36m"
#define RESET_Color "\033[0m"
#define YELLOW_Color "\033[1;33m"
#define BLUE_Color "\033[1;34m"
#define GREEN_Color "\033[1;32m"
#define RED_Color "\033[1;31m"

struct Process {
    int processID;
    int burstTime;
    int arrivalTime;

    // Constructor to initialize all member variables
    Process(int id, int burst, int arrival) : processID(id), burstTime(burst), arrivalTime(arrival) {}

    // Default constructor, if needed
    Process() : processID(0), burstTime(0), arrivalTime(0) {}
};

class RoundRobin {
public:
    RoundRobin(std::vector<Process>& procs, int quantum);
    void runRoundRobin();

private:
    std::vector<Process> processes;
    int quantum;  // Time slice for each process

    void printColumnHeaders();
    void printProcessMessage(const std::string& message, const Process& process, const std::string& color, const std::string formattedTime);
    void executeProcess(const Process& process, int& currentTime);
};

#endif
