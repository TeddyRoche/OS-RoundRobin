#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MLFQ&DVFS.h"
#include "PS.h"
#include "SRTF.h"
#include "RoundRobinDylan.h"

std::vector<Process> processes;
std::vector<Process1> process;
std::vector<Process2> process2;
std::vector<Process3> process3;


const std::string RESET_Color = "\033[0m";
const std::string RED_Color = "\033[1;31m";
const std::string GREEN_Color = "\033[1;32m";
const std::string YELLOW_Color = "\033[1;33m";
const std::string BLUE_Color = "\033[1;34m";
const std::string MAGNETA_Color = "\033[1;35m";
const std::string CYAN_Color = "\033[1;36m";

int ReadFile(std::string file) 
{
    std::ifstream inputFile(file);

    if (!inputFile.is_open()) 
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) 
    {
        std::istringstream iss(line);
        int pid, arrival, burst, priority;
        if (!(iss >> pid >> arrival >> burst >> priority)) 
        {
            std::cerr << "Error: Invalid input format." << std::endl;
            return 1;
        }
        processes.emplace_back(pid, arrival, burst, priority);
        process.emplace_back(pid, arrival, burst, priority);
        process3.emplace_back(pid, arrival, burst);
        process2.emplace_back(pid, arrival, burst);

    }
    return 0;
}

int main()
{
    int choice;
    std::cout << CYAN_Color << "Choose who's Code you want to run:\n" << GREEN_Color << "Teddy(1)" << RESET_Color 
        << "," << YELLOW_Color << " Dylan(2)" << RESET_Color << "," << BLUE_Color << " Joseph(3)" << 
        RESET_Color << ", or" << MAGNETA_Color << " Duc(4)" << RESET_Color << ": ";
    std::cin >> choice;

    switch (choice)
    {
        case 1:
        {
            ReadFile("MLFQ_Test_File.txt");
            
            MLFQ_DVFS mlfq(processes);
            mlfq.runMLFQ();
            break;
        }
        case 2:
        {
            ReadFile("MLFQ_Test_File.txt");

            int quantum = 3; // Example quantum time slice
            RoundRobin rr(process3, quantum);
            rr.runRoundRobin();

            break;
        }
        case 3:
        {
            ReadFile("MLFQ_Test_File.txt");

            SRTF srtf(process2);
            srtf.schedule();


            break;
        }
        case 4:
        {
            ReadFile("MLFQ_Test_File.txt");

            
            pScheduling(process);
            break;
        }
        default: 
        {
            std::cout << RED_Color << "Error Invalid Input!" << RESET_Color;
            break;
        }
    }

    return 0;
    
}

