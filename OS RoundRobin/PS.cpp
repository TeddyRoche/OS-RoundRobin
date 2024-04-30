
#include "PS.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

bool compare(const P& a, const P& b)
{
    if (a.priority == b.priority)
    {
        return a.aTime < b.aTime;
    }
    return a.priority < b.priority;
}

void calcTimes(std::vector<P>& process, std::vector<int>& qTime, std::vector<int>& tTime)
{
    int n = process.size();
    qTime.resize(n);
    tTime.resize(n);

    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        int startTime = std::max(currentTime, process[i].aTime);
        qTime[i] = startTime - process[i].aTime;
        currentTime = startTime + process[i].bTime;
        tTime[i] = currentTime - process[i].aTime;
    }
}

void chart(const std::vector<P>& process, const std::vector<int>& qTime, const std::vector<int>& tTime)
{
    int n = process.size();
    int totalQTime = 0, totalTTime = 0;

    std::cout << "Process No\t Start Time\t Complete Time\t Turnaround Time\t In Queue Time" << std::endl;
    for (int i = 0; i < n; i++)
    {
        totalQTime += qTime[i];
        totalTTime += tTime[i];
        
        std::chrono::seconds dura(process[i].bTime);
        std::this_thread::sleep_for(dura);

        std::cout << process[i].pID << "\t\t "
             << std::max(process[i].aTime, i == 0 ? 0 : process[i - 1].bTime) << "\t\t "
             << std::max(process[i].aTime, i == 0 ? 0 : process[i - 1].bTime) + process[i].bTime << "\t\t "
             << tTime[i] << "\t\t\t "
             << qTime[i] << std::endl;
             
    }

    std::cout << "Average in queue time: " << totalQTime << std::endl;
    std::cout << "Average turnaround time: " << totalTTime << std::endl;
}

void pScheduling(std::vector<P> process)
{

    std::vector<int> qTime, turnaroundTime; 
    
    std::sort(process.begin(), process.end(), compare);
    
    calcTimes(process, qTime, turnaroundTime);
    chart(process, qTime, turnaroundTime);
}