#include "Simulator.h"
#include <iostream>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::max_element
#include <cassert>

// Constructor initializes the simulator with number of users and bandwidth
Simulator::Simulator(int userCount, int bandwidth)
    : userCount(userCount), channelBandwidth(bandwidth) {}

// Calculates the throughput based on recorded timestamps (used for all simulators)
double Simulator::calculateThroughput() const
{
    if (eventTimestamps.empty())
        return 0.0;

    double totalData = eventTimestamps.size() * 1.0;      // 1 KB per packet
    double totalTime = eventTimestamps.back();            // Total time in ms
    return (totalData * 8.0) / (totalTime / 1000.0); // Throughput in Mbps
}

// Computes the average latency from the latencies recorded
double Simulator::computeAverageLatency() const
{
    if (latencyData.empty())
        return 0.0;

    double totalLatency = std::accumulate(latencyData.begin(), latencyData.end(), 0.0); // Sum all latencies
    return totalLatency / latencyData.size();  // Return the average latency
}

// Computes the maximum latency from the recorded latencies
double Simulator::computeMaxLatency() const
{
    if (latencyData.empty())
        return 0.0;

    return *std::max_element(latencyData.begin(), latencyData.end()); // Max latency
}
