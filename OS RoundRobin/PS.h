#ifndef PROCESS_SCHEDULING_H
#define PROCESS_SCHEDULING_H

#include <vector>

struct Pro
{
    int pID, aTime, bTime, priority;
};

bool compare(const Pro& a, const Pro& b);

void calcTimes(std::vector<Pro>& process, std::vector<int>& qTime, std::vector<int>& tTime);

void chart(const std::vector<Pro>& process, const std::vector<int>& qTime, const std::vector<int>& tTime);

void pScheduling(std::vector<Pro> process);

#endif // PROCESS_SCHEDULING_H
