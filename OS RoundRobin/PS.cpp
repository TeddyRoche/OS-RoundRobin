#include "PS.h"


bool compare(const Process1& a, const Process1& b)
{
    if (a.priority == b.priority)
    {
        return a.aTime < b.aTime;
    }
    return a.priority < b.priority;
}

void calcTimes(std::vector<Process1>& process, std::vector<int>& qTime, std::vector<int>& tTime)
{
    qTime.resize(process.size());
    tTime.resize(process.size());

    int currentTime = 0;
    for (int i = 0; i < process.size(); i++)
    {
        int startTime = std::max(currentTime, process[i].aTime);
        qTime[i] = startTime - process[i].aTime;
        currentTime = startTime + process[i].bTime;
        tTime[i] = currentTime - process[i].aTime;
    }
}

void chart(const std::vector<Process1>& process, const std::vector<int>& qTime, const std::vector<int>& tTime)
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

void pScheduling(std::vector<Process1> process)
{

    std::vector<int> qTime, turnaroundTime; 
    
    std::sort(process.begin(), process.end(), compare);
    
    calcTimes(process, qTime, turnaroundTime);
    chart(process, qTime, turnaroundTime);
}
