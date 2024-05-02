#pragma once
#ifndef SRTF_H
#define SRTF_H

#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <vector>
#include <sstream>


struct Process2 
{
    int pid;
    int bt;
    int art;

    Process2(int pid, int bt, int art) : pid(pid), bt(bt), art(art) {}
};

class SRTF 
{
public:
    SRTF(std::vector<Process2> processes);
    void schedule();
private:
    std::vector<Process2> processes;
    void findWaitingTime(int n, int rt[], int wt[], int at[], int bt[]);
    void findTurnAroundTime(int n, int bt[], int wt[], int tat[]);
};

#endif