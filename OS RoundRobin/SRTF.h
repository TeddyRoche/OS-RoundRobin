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
    const int bt;
    int art;
};

class SRTF 
{
public:
    SRTF(std::vector<Process2> processes);
    void schedule();
private:
    const std::string RESET_Color = "\033[0m";
    const std::string RED_Color = "\033[1;31m";
    const std::string GREEN_Color = "\033[1;32m";
    const std::string YELLOW_Color = "\033[1;33m";
    const std::string BLUE_Color = "\033[1;34m";
    const std::string MAGNETA_Color = "\033[1;35m";
    const std::string CYAN_Color = "\033[1;36m";
    std::vector<Process2> processes;
    void findWaitingTime(int n, int rt[], int wt[], int at[]);
    void findTurnAroundTime(int n, int bt[], int wt[], int tat[]);
};

#endif