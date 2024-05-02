#include "RoundRobinDylan.h"
#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

std::mutex coutMutex1;

void RoundRobin::printColumnHeaders() {
    std::lock_guard<std::mutex> lock(coutMutex1);
    std::cout << std::endl << CYAN_Color << std::right << "Event" << std::setw(21) << RESET_Color
              << "| " << CYAN_Color << "Process ID" << std::setw(9) << RESET_Color <<
              " | " << CYAN_Color << "Remaining Time" << std::setw(9) << RESET_Color << " | " << CYAN_Color << "Time\t\t" << RESET_Color
              << "   | " << std::endl;
    std::cout << "----------------------------------------------------------------------------\n";
}

void RoundRobin::printProcessMessage(const std::string& message, const Process3& process, 
                                     const std::string& color, const std::string formattedTime) {
    std::lock_guard<std::mutex> lock(coutMutex1);
    std::cout << color << std::right << message << std::setw(15) << RESET_Color << "| "
              << "Process " << std::setw(2) << process.processID << "\t" << RESET_Color << "|"
              << "\t\t" << color << " Time: " << formattedTime << RESET_Color << "  |";
    std::cout << std::endl << std::flush;
}

void RoundRobin::executeProcess(const Process3& process, int& currentTime) {
    int remainingTime = process.burstTime;
    while (remainingTime > 0) {
        auto startTime = std::chrono::steady_clock::now();
        int timeSlice = std::min(quantum, remainingTime);
        std::this_thread::sleep_for(std::chrono::seconds(timeSlice));
        currentTime += timeSlice;
        remainingTime -= timeSlice;
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
        std::ostringstream formattedTimeStream;
        formattedTimeStream << std::setfill('0') << std::setw(2) << elapsedTime / 3600 << ":"
                            << std::setw(2) << (elapsedTime % 3600) / 60 << ":"
                            << std::setw(2) << elapsedTime % 60;
        printProcessMessage("Executing:\t", process, BLUE_Color, formattedTimeStream.str());
    }
}

RoundRobin::RoundRobin(std::vector<Process3>& procs, int quantum) : processes(procs), quantum(quantum) {}

void RoundRobin::runRoundRobin() {
    auto startTime = std::chrono::steady_clock::now();
    printColumnHeaders();

    int currentTime = 0;
    std::vector<std::thread> threads;

    for (auto& process : processes) {
        threads.emplace_back([&, process]() {
            executeProcess(process, currentTime);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto endTime = std::chrono::steady_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::cout << "Total Execution Time: " << totalDuration << " seconds" << std::endl;
}

