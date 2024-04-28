#pragma once
#ifndef MLFQ_H
#define MLFQ_H

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

class MLFQ
{
private:
    std::vector<Process> processes;
    std::vector<Process> queue0; // Highest priority
    std::vector<Process> queue1; // Medium priority
    std::vector<Process> queue2; // Lowest priority

public:
    MLFQ(std::vector<Process>& procs);
    void runMLFQ();
};


#endif