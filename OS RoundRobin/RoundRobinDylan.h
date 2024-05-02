#pragma once
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


struct Process3 {
    int processID;
    int burstTime;
    int arrivalTime;

    // Constructor to initialize all member variables
    Process3(int id, int burst, int arrival) : processID(id), burstTime(burst), arrivalTime(arrival) {}

    // Default constructor, if needed
    Process3() : processID(0), burstTime(0), arrivalTime(0) {}
};

class RoundRobin {
public:
    // Constructor that takes a list of processes and the time quantum
    RoundRobin(std::vector<Process3>& procs, int quantum);

    // Starts the round-robin scheduling
    void runRoundRobin();

private:
    const std::string RESET_Color = "\033[0m";
    const std::string RED_Color = "\033[1;31m";
    const std::string GREEN_Color = "\033[1;32m";
    const std::string YELLOW_Color = "\033[1;33m";
    const std::string BLUE_Color = "\033[1;34m";
    const std::string MAGNETA_Color = "\033[1;35m";
    const std::string CYAN_Color = "\033[1;36m";
    std::vector<Process3> processes;  // List of processes to be scheduled
    int quantum;  // Time slice for each process in seconds

    // Prints column headers for the round-robin output
    void printColumnHeaders();
    // Prints a process message update during scheduling
    void printProcessMessage(const std::string& message, const Process3& process, const std::string& color, const std::string formattedTime);
    // Executes a single process for its time slice
    void executeProcess(const Process3& process, int& currentTime);
};

#endif
