#pragma once
#ifndef PROCESS_SCHEDULING_H
#define PROCESS_SCHEDULING_H

#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

struct Process1
{
    int pID, aTime, bTime, priority;

    Process1(int id, int arrival, int burst, int prio) :
        pID(id), aTime(arrival), bTime(burst), priority(prio) {}
};

bool compare(const Process1& a, const Process1& b);

void calcTimes(std::vector<Process1>& process, std::vector<int>& qTime, std::vector<int>& tTime);

void chart(const std::vector<Process1>& process, const std::vector<int>& qTime, const std::vector<int>& tTime);

void pScheduling(std::vector<Process1> process);

#endif // PROCESS_SCHEDULING_H
