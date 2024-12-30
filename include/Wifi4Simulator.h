#ifndef WIFI4SIMULATOR_H
#define WIFI4SIMULATOR_H

#include "Simulator.h"
#include <vector>
#include <random>
#include <unordered_map>

class WiFi4Simulator : public Simulator {
public:
    WiFi4Simulator(int numUsers, int bandwidth);

    void executeSimulation() override;  // Executes the simulation logic

    double calculateThroughput() const override;  // Calculates throughput for the simulation
    void resolveBackoffConflicts(std::unordered_map<int, double>& userBackoff);  // Resolves any backoff time conflicts
};

#endif
