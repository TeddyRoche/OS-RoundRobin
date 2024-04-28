#include "MLFQ.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <vector>

// Mutex for ensuring thread-safe access to cout
std::mutex coutMutex;

// Named constants
const int MAX_PROCESS_ID_WIDTH = 10;
const int MAX_TIMESTAMP_LENGTH = 10;

const std::string RESET_Color = "\033[0m";
const std::string RED_Color = "\033[1;31m";
const std::string GREEN_Color = "\033[1;32m";
const std::string YELLOW_Color = "\033[1;33m";
const std::string BLUE_Color = "\033[1;34m";





// Helper function to print column headers
void printColumnHeaders() 
{
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << RESET_Color << std::right << "Event" << std::setw(25) << RESET_Color << std::right << "Process ID" << std::endl;
}

// Helper function to print process message
void printProcessMessage(const std::string& message, const Process& process, const std::string& color) 
{
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << color << std::right  << message << std::right << std::setw(MAX_PROCESS_ID_WIDTH) << "Process " << std::setw(2) << process.processID << std::endl;
}

// Helper function to execute process
void executeProcess(const Process& process, int& currentTime) 
{
    printProcessMessage("Arrival:\t\t", process, YELLOW_Color);
    printProcessMessage("Execution Start:\t", process, BLUE_Color);

    std::this_thread::sleep_for(std::chrono::seconds(process.burstTime));
    currentTime += process.burstTime;

    printProcessMessage("Execution End:\t\t", process, GREEN_Color);
}

MLFQ::MLFQ(std::vector<Process>& procs) : processes(procs) {}

void MLFQ::runMLFQ() 
{
    // Start the clock
    auto startTime = std::chrono::steady_clock::now();

    // Print column headers
    printColumnHeaders();

    // Sorting processes by arrival time and then by priority
    std::sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) 
        {
        if (p1.arrivalTime != p2.arrivalTime) 
        {
            return p1.arrivalTime < p2.arrivalTime;
        }
        else 
        {
            return p1.priority < p2.priority;
        }
        });

    int currentTime = processes.empty() ? 0 : processes[0].arrivalTime;

    // Create a thread for each process
    std::vector<std::thread> threads;
    for (const auto& process : processes) 
    {
        threads.emplace_back([&]() 
            {
            try 
            {
                auto timeToWait = std::chrono::seconds(process.arrivalTime - currentTime);
                std::this_thread::sleep_for(timeToWait);
                currentTime = process.arrivalTime;

                executeProcess(process, currentTime);
            }
            catch (const std::exception& e) 
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cerr << RED_Color << "Error: " << e.what() << RESET_Color << std::endl;
            }
            });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) 
    {
        thread.join();
    }

    // Calculate total execution time
    auto endTime = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << GREEN_Color;
    std::cout << "Total execution time: " << totalTime << " seconds\n";
    std::cout << "All processes finished.\n" << RESET_Color;
}
