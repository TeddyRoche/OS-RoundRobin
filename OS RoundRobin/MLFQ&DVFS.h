#pragma once
#ifndef MLFQ_DVFS_H
#define MLFQ_DVFS_H

#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <vector>
#include <sstream>

struct Process 
{
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;

    Process(int id, int arrival, int burst, int prio) :
        processID(id), arrivalTime(arrival), burstTime(burst), priority(prio) {}
};

class MLFQ_DVFS
{
private:
    std::vector<Process> processes;
    std::vector<Process> queue0; // Highest priority
    std::vector<Process> queue1; // Medium priority
    std::vector<Process> queue2; // Lowest priority

    const int MAX_PROCESS_ID_WIDTH = 10;
    const int MAX_TIMESTAMP_LENGTH = 10;

    const std::string RESET_Color = "\033[0m";
    const std::string RED_Color = "\033[1;31m";
    const std::string GREEN_Color = "\033[1;32m";
    const std::string YELLOW_Color = "\033[1;33m";
    const std::string BLUE_Color = "\033[1;34m";
    const std::string MAGENTA_Color = "\033[1;35m";
    const std::string CYAN_Color = "\033[1;36m";

    const double BASE_FREQUENCY = 2.5;
    const double MAX_FREQUENCY = 4.0;
    const double MIN_FREQUENCY = 1.0;
    const double BASE_POWER = 50.0;
    const double VOLTAGE_CONSTANT = 0.2;
    const int MAX_BURST_TIME = 100;

    void adjustCPUFrequency(int burstTime);
    void printColumnHeaders();
    void executeProcess(const Process& process, int& currentTime);
    void printProcessMessage(const std::string& message, const Process& process, 
        const std::string& color, const std::string formattedTime);

public:
    MLFQ_DVFS(std::vector<Process>& procs);
    void runMLFQ();
};


#endif