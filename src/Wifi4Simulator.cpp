#include "WiFi4Simulator.h"
#include <iostream>
#include <unordered_map>
#include <random>
#include <algorithm>


WiFi4Simulator::WiFi4Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}


double WiFi4Simulator::calculateThroughput() const {
    if (eventTimestamps.empty())
        return 0.0;

    double totalData = eventTimestamps.size() * 8192;   // Total data in bits (1 KB = 8192 bits)
    double totalTime = eventTimestamps.back() / 1000.0; // Total time in seconds
    return (totalData / totalTime) / 1e6;               // Throughput in Mbps
}

// Resolves backoff time conflicts by reassigning backoff time to conflicting users
void WiFi4Simulator::resolveBackoffConflicts(std::unordered_map<int, double>& userBackoff) {
    for (auto it = userBackoff.begin(); it != userBackoff.end(); ++it) {
        for (auto jt = std::next(it); jt != userBackoff.end(); ++jt) {
            if (it->second == jt->second) {
                // Conflict found, resolve by assigning a new backoff time
                double newBackoffTime = static_cast<double>(rand() % 10 + 1); // Random between 1 and 10 ms
                jt->second = newBackoffTime;
                std::cout << "[Conflict Resolved] User " << jt->first 
                          << " had the same backoff time as User " << it->first 
                          << ". New backoff time: " << newBackoffTime << " ms\n";
            }
        }
    }
}

// Runs the simulation for WiFi 4 (CSMA/CA protocol)
void WiFi4Simulator::executeSimulation() {
    std::cout << "\nWiFi 4 Simulation Started: CSMA/CA Protocol\n";

    // Random number generator for backoff times
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<> backoffDist(1.0, 10.0);

    double currentTime = 0.0;
    double transmissionDuration = 0.0614; // Time for 1 KB packet (in ms)

    // Map to store user backoff times
    std::unordered_map<int, double> userBackoff;
    for (int i = 0; i < userCount; ++i) {
        userBackoff[i] = (i == 0) ? 0.0 : backoffDist(rng); // User 0 has backoff 0 for first transmission
        std::cout << "User " << i << " initial backoff time: " << userBackoff[i] << " ms\n";
    }

    latencyData.clear();
    eventTimestamps.clear();

    
    while (!userBackoff.empty()) {
        
        resolveBackoffConflicts(userBackoff);

        // Find the user with the smallest backoff time
        auto nextUser = std::min_element(userBackoff.begin(), userBackoff.end(),
                                         [](const auto& a, const auto& b) {
                                             return a.second < b.second;
                                         });

        currentTime = std::max(currentTime, nextUser->second);
        std::cout << "User " << nextUser->first << " starts transmission at " << currentTime << " ms.\n";

        currentTime += transmissionDuration;
        eventTimestamps.push_back(currentTime);
        latencyData.push_back(currentTime);

        std::cout << "User " << nextUser->first << " finishes transmission at " << currentTime << " ms.\n";

        // Remove the user from the queue after successful transmission
        userBackoff.erase(nextUser);
    }

    // Output simulation results
    std::cout << "\nResults:\n";
    std::cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    std::cout << "Average Latency: " << computeAverageLatency() << " ms\n";
    std::cout << "Max Latency: " << computeMaxLatency() << " ms\n";
}
