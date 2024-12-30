#include "WiFi6Simulator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <numeric> // For std::accumulate

// Custom class to represent latency data
class LatencyData {
public:
    LatencyData(double value = 0.0) : value(value) {}

    // Overload the + operator
    LatencyData operator+(const LatencyData& other) const {
        return LatencyData(value + other.value);
    }

    // Conversion operator to double
    operator double() const {
        return value;
    }

private:
    double value;
};

// Template function to calculate the average of a vector
template <typename T>
double calculateAverage(const std::vector<T>& data) {
    if (data.empty())
        return 0.0;

    T total = std::accumulate(data.begin(), data.end(), T(0));
    return static_cast<double>(total) / data.size();
}

// Constructor initializes WiFi 6 simulator with number of users and bandwidth
WiFi6Simulator::WiFi6Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth), subChannelWidth(4), dataRate(133.33) // Default data rate in Mbps
{
}

double WiFi6Simulator::calculateThroughput() const
{
    if (latencyData.empty())
        return 0.0;

    double totalData = latencyData.size() * 8192.0;    // Total data in bits (1 KB = 8192 bits)
    double totalTime = eventTimestamps.back();          // Total simulation time in ms
    return (totalData / (totalTime / 1000.0)) / 1e6;    // Throughput in Mbps
}

void WiFi6Simulator::executeSimulation()
{
    std::cout << "\n--- WiFi 6 OFDMA Simulation ---\n";

    // Ask the user for sub-channel width
    int userInputSubChannelWidth;
    std::cout << "Enter sub-channel width (2, 4, or 10 MHz): ";
    std::cin >> userInputSubChannelWidth;

    // Validate sub-channel width
    if (userInputSubChannelWidth != 2 && userInputSubChannelWidth != 4 && userInputSubChannelWidth != 10)
    {
        throw std::invalid_argument("Invalid sub-channel width! Only 2, 4, or 10 MHz are allowed.");
    }
    subChannelWidth = userInputSubChannelWidth;

    int numSubChannels = channelBandwidth / subChannelWidth;                            // Calculate sub-channels based on total bandwidth
    double dataRatePerSubChannel = (dataRate * subChannelWidth) / 20.0;          // Mbps per sub-channel
    double transmissionDuration = (8192.0 / (dataRatePerSubChannel * 1e6)) * 1000.0; // ms for 1 KB

    if (dataRatePerSubChannel <= 0)
    {
        std::cerr << "Error: Data rate per sub-channel is invalid. Exiting simulation.\n";
        return;
    }

    std::cout << "Total Bandwidth: " << channelBandwidth << " MHz\n";
    std::cout << "Sub-channel Width: " << subChannelWidth << " MHz\n";
    std::cout << "Number of Sub-channels: " << numSubChannels << "\n";
    std::cout << "Transmission Time per Packet: " << std::fixed << std::setprecision(4) << transmissionDuration << " ms\n\n";

    latencyData.clear();
    eventTimestamps.clear();

    int remainingUsers = userCount;
    double currentTime = 0.0;

    while (remainingUsers > 0)
    {
        std::cout << "--- Starting Frame at " << currentTime << " ms ---\n";

        int usersThisFrame = std::min(numSubChannels, remainingUsers);
        for (int i = 0; i < usersThisFrame; ++i)
        {
            int user = userCount - remainingUsers + i;
            double latency = currentTime + transmissionDuration;

            eventTimestamps.push_back(latency);
            latencyData.push_back(latency);

            std::cout << "User " << user << " transmits at " << std::fixed << std::setprecision(4) << latency << " ms.\n";
        }

        remainingUsers -= usersThisFrame;
        currentTime += 5.0; // Move to the next frame (frame duration is 5 ms)
    }

    std::cout << "\nSimulation Results:\n";                                  
    std::cout << "Throughput: " << calculateThroughput() << " Mbps\n";        
    std::cout << "Average Latency: " << computeAverageLatency() << " ms\n"; 
    std::cout << "Max Latency: " << computeMaxLatency() << " ms\n";         
}

double WiFi6Simulator::computeAverageLatency() const
{
    std::vector<LatencyData> latencyDataWrapped(latencyData.begin(), latencyData.end());
    return calculateAverage(latencyDataWrapped);
}

double WiFi6Simulator::computeMaxLatency() const
{
    if (latencyData.empty())
        return 0.0;

    return *std::max_element(latencyData.begin(), latencyData.end());
}