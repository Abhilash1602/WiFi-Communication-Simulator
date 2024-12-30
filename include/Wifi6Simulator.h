#ifndef WIFI6SIMULATOR_H
#define WIFI6SIMULATOR_H

#include "Simulator.h"
#include <vector>

class WiFi6Simulator : public Simulator
{
public:
    WiFi6Simulator(int numUsers, int bandwidth);
    void executeSimulation() override;  // Simulates WiFi 6 (OFDMA) process
    double calculateThroughput() const override; // Calculates WiFi 6 throughput

    double computeAverageLatency() const;
    double computeMaxLatency() const;

private:
    int subChannelWidth; 
    double dataRate;     // Data rate in Mbps
};

#endif
