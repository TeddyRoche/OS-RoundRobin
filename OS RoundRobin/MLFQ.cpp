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

// Helper function to print column headers
void printColumnHeaders() {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "\033[0m" << std::right << "Event" << std::setw(25)
        << "\033[0m" << std::right << "Process ID" << std::endl;
}

// Helper function to print process message
void printProcessMessage(const std::string& message, const Process& process, const std::string& color) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << color << std::right  << message << std::right << std::setw(MAX_PROCESS_ID_WIDTH) 
        << "Process " << std::setw(2) << process.processID << std::endl;
}

// Helper function to execute process
void executeProcess(const Process& process, int& currentTime) {
    // Print arrival message in yellow
    printProcessMessage("Arrival:\t\t", process, "\033[1;33m");

    // Print execution start message in green
    printProcessMessage("Execution Start:\t", process, "\033[1;34m");

    // Simulate processing time
    std::this_thread::sleep_for(std::chrono::seconds(process.burstTime));

    // Update current time
    currentTime += process.burstTime;

    // Print execution completion message in green
    printProcessMessage("Execution End:\t\t", process, "\033[1;32m");
}

MLFQ::MLFQ(std::vector<Process>& procs) : processes(procs) {}

void MLFQ::runMLFQ() {
    // Start the clock
    auto startTime = std::chrono::steady_clock::now();

    // Print column headers
    printColumnHeaders();

    // Sorting processes by arrival time and then by priority
    std::sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        if (p1.arrivalTime != p2.arrivalTime) {
            return p1.arrivalTime < p2.arrivalTime;
        }
        else {
            return p1.priority < p2.priority;
        }
        });

    int currentTime = processes.empty() ? 0 : processes[0].arrivalTime;

    // Create a thread for each process
    std::vector<std::thread> threads;
    for (const auto& process : processes) {
        threads.emplace_back([&]() {
            try {
                // Calculate the time remaining until the arrival time
                auto timeToWait = std::chrono::seconds(process.arrivalTime - currentTime);

                // Wait until the arrival time
                std::this_thread::sleep_for(timeToWait);

                // Update current time
                currentTime = process.arrivalTime;

                // Execute process
                executeProcess(process, currentTime);
            }
            catch (const std::exception& e) {
                // Print error message in red
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cerr << "\033[1;31mError: " << e.what() << "\033[0m" << std::endl;
            }
            });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Calculate total execution time
    auto endTime = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    // Print total execution time
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "\033[1;32m"; // Set color to green
    std::cout << "Total execution time: " << totalTime << " seconds\n";
    std::cout << "All processes finished.\033[0m\n"; // Finished message
}
