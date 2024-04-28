#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MLFQ.h"

std::vector<Process> processes;

int ReadFile(std::string file) {
    std::ifstream inputFile(file);

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
    return 0;
}

int main()
{
    ReadFile("MLFQ_Test_File.txt");

    MLFQ mlfq(processes);
    mlfq.runMLFQ();

    return 0;
    
}

