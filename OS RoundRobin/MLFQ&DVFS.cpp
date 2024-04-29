#include "MLFQ&DVFS.h"

std::mutex coutMutex;

void MLFQ_DVFS::adjustCPUFrequency(int burstTime)
{
    double percentage = static_cast<double>(burstTime) / MAX_BURST_TIME;
    double targetFrequency = MAX_FREQUENCY - percentage * (MAX_FREQUENCY - MIN_FREQUENCY);

    std::cout << BLUE_Color << " CPU: " << targetFrequency << " GHz\t" << RESET_Color << " |\t\t   |";
}


void MLFQ_DVFS::printColumnHeaders()
{
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << std::endl << CYAN_Color << std::right << "Event" << std::setw(21) << RESET_Color
        << "| " << CYAN_Color << "Process ID" << std::setw(9) << RESET_Color << 
        " | " << CYAN_Color << "Frequency" << std::setw(9) << RESET_Color << " | " << CYAN_Color << "Time\t\t" << RESET_Color 
        << "   | " << std::endl;
    std::cout << "----------------------------------------------------------------------------\n";
}

void MLFQ_DVFS::printProcessMessage(const std::string& message, const Process& process, 
    const std::string& color, const std::string formattedTime)
{
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << color << std::right << message << std::right << std::setw(MAX_PROCESS_ID_WIDTH) 
        << RESET_Color << "|\t" << color << "Process " << std::setw(2) << process.processID << "\t" << RESET_Color << "|";
    if (color == "\033[1;33m")
    {
        std::cout << RESET_Color << "\t\t |\t\t   |";
        std::cout << std::endl << std::flush;
    }
    else if (color == "\033[1;32m")
    {
        std::cout << "\t\t" << RESET_Color << " |" << color << " Time: " << formattedTime << RESET_Color << "  |";
        std::cout << std::endl << std::flush;
    }
    else if (color == "\033[1;34m")
    {
        adjustCPUFrequency(process.burstTime);
        std::cout << std::endl << std::flush;
    }
}

void MLFQ_DVFS::executeProcess(const Process& process, int& currentTime)
{
    auto startTime = std::chrono::steady_clock::now();

    printProcessMessage("Arrival:\t", process, YELLOW_Color, "");

    printProcessMessage("Execution Start:", process, BLUE_Color, "");

    std::this_thread::sleep_for(std::chrono::seconds(process.burstTime));
    currentTime += process.burstTime;

    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    int hours = elapsedTime / 3600;
    int minutes = (elapsedTime % 3600) / 60;
    int seconds = elapsedTime % 60;

    std::ostringstream formattedTimeStream;
    formattedTimeStream << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setw(2) << minutes << ":"
        << std::setw(2) << seconds;

    // Get the formatted time string
    std::string formattedTime = formattedTimeStream.str();


    printProcessMessage("Execution End:\t", process, GREEN_Color, formattedTime);
}

MLFQ_DVFS::MLFQ_DVFS(std::vector<Process>& procs) : processes(procs) {}

void MLFQ_DVFS::runMLFQ()
{
    auto startTime = std::chrono::steady_clock::now();

    printColumnHeaders();

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

    for (auto& thread : threads)
    {
        thread.join();
    }

    auto endTime = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "----------------------------------------------------------------------------\n";
    std::cout << GREEN_Color;
    std::cout << "Total execution time: " << totalTime << " seconds\n";
    std::cout << "All processes finished.\n" << RESET_Color;
}
