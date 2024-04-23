#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#define Time_Quantum 50

using namespace std;

struct Process
{
    string name;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority; // New attribute for priority

    // Comparison function for priority scheduling
    bool operator<(const Process& other) const
    {
        return priority < other.priority;
    }
};

template<typename T> 
class Queue {

    void push()
    {

    }
    void pop()
    {

    }
    bool empty()
    {

    }

};

void checkArrivingProcesse()
{

}

void executeProcess()
{

}

void threadFunction()
{

}

int main()
{
	cout << "Hello World!\n";
    //code to add queue :)
    
}

