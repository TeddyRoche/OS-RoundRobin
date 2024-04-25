#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MLFQ.h"


int main()
{
    std::vector<Process> processes;

    // Read process data from the file
    std::ifstream inputFile("MLFQ_Test_File.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int pid, arrival, burst, priority;
        if (!(iss >> pid >> arrival >> burst >> priority)) {
            std::cerr << "Error: Invalid input format." << std::endl;
            return 1;
        }
        processes.emplace_back(pid, arrival, burst, priority);
    }


    MLFQ mlfq(processes);
    mlfq.runMLFQ();

    return 0;
    
}

