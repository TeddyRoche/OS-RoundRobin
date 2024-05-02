#include "SRTF.h"

SRTF::SRTF(std::vector<Process2> processes) : processes(processes) {}

void SRTF::findWaitingTime(int n, int rt[], int wt[], int at[], int bt[]) 
{
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != n) 
    {
        for (int j = 0; j < n; j++) 
        {
            if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) 
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) 
        {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0) 
        {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void SRTF::findTurnAroundTime(int n, int bt[], int wt[], int tat[]) 
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void SRTF::schedule() 
{
    int n = processes.size();
    std::vector<int> rt(n), bt(n), at(n), wt(n), tat(n);


    for (int i = 0; i < n; i++) 
    {
        rt[i] = processes[i].bt;
        bt[i] = processes[i].bt;
        at[i] = processes[i].art;
    }

    findWaitingTime(n, rt.data(), wt.data(), at.data(), bt.data());
    findTurnAroundTime(n, bt.data(), wt.data(), tat.data());

    std::cout << "Processes    Burst Time     Waiting Time     Turn-Around Time\n";
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) 
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        std::cout << " " << processes[i].pid << "\t\t" << bt[i] << "\t\t " << wt[i] << "\t\t " << tat[i] << std::endl;
    }

    std::cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    std::cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}