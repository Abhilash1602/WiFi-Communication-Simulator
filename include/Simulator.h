#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <memory>
#include <cassert>

class Simulator {
protected:
    int userCount;             // Number of users in the simulation
    int channelBandwidth;      // Bandwidth available for communication
    std::vector<double> latencyData;  // Stores latency values for each packet
    std::vector<double> eventTimestamps;  // Records the timestamps of events

public:
    Simulator(int userCount, int bandwidth); // Constructor for simulation setup

    virtual void executeSimulation() = 0; // Executes the simulation
    virtual double calculateThroughput() const; // Calculates throughput of the system

    double calculateThroughput(int totalPackets, double totalDuration)
    {
        assert(totalDuration > 0);  // Ensure total duration is positive
        double totalDataInKB = totalPackets * 1.0; // Total data in KB
        return (totalDataInKB * 8.0) / (totalDuration / 1000.0); // Throughput in Mbps
    }

    double computeAverageLatency() const;  // Calculates the average latency
    double computeMaxLatency() const;      // Calculates the maximum latency
};

#endif
