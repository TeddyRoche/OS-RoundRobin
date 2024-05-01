#include "RoundRobin.h"
#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

std::mutex coutMutex; // Mutex to synchronize access to standard output, ensuring thread-safe printing.

// Prints column headers for the round-robin scheduling output.
void RoundRobin::printColumnHeaders() {
    std::lock_guard<std::mutex> lock(coutMutex); // Locks mutex to prevent concurrent write access from multiple threads.
    // Print formatted headers using color codes for better readability.
    std::cout << std::endl << CYAN_Color << std::right << "Event" << std::setw(21) << RESET_Color
        << "| " << CYAN_Color << "Process ID" << std::setw(9) << RESET_Color <<
        " | " << CYAN_Color << "Remaining Time" << std::setw(9) << RESET_Color << " | " << CYAN_Color << "Time\t\t" << RESET_Color
        << "   | " << std::endl;
    std::cout << "----------------------------------------------------------------------------\n";
}

// Prints a formatted message for each process execution update.
void RoundRobin::printProcessMessage(const std::string& message, const Process& process, 
    const std::string& color, const std::string formattedTime) {
    std::lock_guard<std::mutex> lock(coutMutex); // Ensures that output statements are not interrupted by other threads.
    // Outputs the current state of the process, including the process ID and elapsed time.
    std::cout << color << std::right << message << std::setw(15) << RESET_Color << "| "
              << "Process " << std::setw(2) << process.processID << "\t" << RESET_Color << "|"
              << "\t\t" << color << " Time: " << formattedTime << RESET_Color << "  |";
    std::cout << std::endl << std::flush; // Flushes the stream to ensure immediate display of text.
}

// Executes a single process according to the round-robin scheduling algorithm.
void RoundRobin::executeProcess(const Process& process, int& currentTime) {
    int remainingTime = process.burstTime; // Tracks the remaining time needed to complete the process.
    while (remainingTime > 0) {
        auto startTime = std::chrono::steady_clock::now(); // Records start time of the current time slice.
        int timeSlice = std::min(quantum, remainingTime); // Calculates the time slice to be allocated (either the full quantum or whatever is left).
        std::this_thread::sleep_for(std::chrono::seconds(timeSlice)); // Simulates process execution by pausing the thread.
        currentTime += timeSlice; // Updates the global current time by the duration of the time slice.
        remainingTime -= timeSlice; // Reduces the remaining time by the duration of the executed time slice.
        auto endTime = std::chrono::steady_clock::now(); // Marks the end time of the current slice.
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count(); // Calculates the elapsed time.
        std::ostringstream formattedTimeStream; // Stream for formatting the time output.
        formattedTimeStream << std::setfill('0') << std::setw(2) << elapsedTime / 3600 << ":"
                            << std::setw(2) << (elapsedTime % 3600) / 60 << ":"
                            << std::setw(2) << elapsedTime % 60;
        printProcessMessage("Executing:\t", process, BLUE_Color, formattedTimeStream.str()); // Print the status update for the process.
    }
}

// Constructor to initialize the round-robin scheduler with a list of processes and a quantum time slice.
RoundRobin::RoundRobin(std::vector<Process>& procs, int quantum) : processes(procs), quantum(quantum) {}

// Main method to run the round-robin scheduling.
void RoundRobin::runRoundRobin() {
    auto startTime = std::chrono::steady_clock::now(); // Marks the start time of the round-robin scheduling.
    printColumnHeaders(); // Prints headers for output.

    int currentTime = 0; // Global current time tracker.
    std::vector<std::thread> threads; // Vector to hold threads, each running a process.

    // Creating a thread for each process to simulate concurrent execution.
    for (auto& process : processes) {
        threads.emplace_back([&, process]() {
            executeProcess(process, currentTime);
        });
    }

    // Wait for all threads to complete.
    for (auto& thread : threads) {
        thread.join();
    }

    auto endTime = std::chrono::steady_clock::now(); // Marks the end time of the entire round-robin cycle.
    auto totalDuration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count(); // Calculates total duration of the scheduling.
    std::cout << "Total Execution Time: " << totalDuration << " seconds" << std::endl; // Outputs the total execution time.
}
