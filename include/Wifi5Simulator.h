#ifndef WIFI5SIMULATOR_H
#define WIFI5SIMULATOR_H

#include "Simulator.h"
#include <deque>  // Using deque for managing packets

class WiFi5Simulator : public Simulator {
public:
    // Constructor that initializes the WiFi 5 simulator with the number of users and bandwidth
    WiFi5Simulator(int numUsers, int bandwidth);

    // Method to execute the simulation
    void executeSimulation() override;

    // Method to calculate throughput (Mbps)
    double calculateThroughput(int totalPackets, double totalTime) const;

    // Method to compute average latency (ms)
    double computeAverageLatency() const;

    // Method to compute maximum latency (ms)
    double computeMaxLatency() const;

private:
    std::deque<int> remainingPackets;  // Tracks remaining packets for each user
    std::vector<double> latencyData;   // Stores latency data for each packet
    std::vector<double> eventTimestamps;  // Stores event timestamps for tracking simulation progress
};

#endif  // WIFI5SIMULATOR_H
