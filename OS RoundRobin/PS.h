#ifndef PROCESS_SCHEDULING_H
#define PROCESS_SCHEDULING_H

#include <vector>

struct P
{
    int pID, aTime, bTime, priority;
};

bool compare(const P& a, const P& b);

void calcTimes(std::vector<P>& process, std::vector<int>& qTime, std::vector<int>& tTime);

void chart(const std::vector<P>& process, const std::vector<int>& qTime, const std::vector<int>& tTime);

void pScheduling(std::vector<P> process);

#endif // PROCESS_SCHEDULING_H