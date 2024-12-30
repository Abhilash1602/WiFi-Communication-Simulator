#include "WiFi5Simulator.h"
#include <iostream>
#include <iomanip>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::max_element
#include <deque>     // Using deque for managing packets

// Constructor initializes WiFi 5 simulator with number of users and bandwidth
WiFi5Simulator::WiFi5Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

void WiFi5Simulator::executeSimulation()
{
    std::cout << "WiFi 5 MU-MIMO Simulation\n";

    // User input for packets per user
    int packetsPerUser;
    std::cout << "Enter the number of packets per user: ";
    std::cin >> packetsPerUser;

    // Simulation parameters
    double timeElapsed = 0.0;
    double broadcastPacketTime = 0.0614;  // 1 KB broadcast packet transmission time (ms)
    double csiPacketTime = 0.012;         // CSI packet transmission time (ms)
    double dataPacketTime = 0.0614;       // Data packet transmission time (ms)
    double parallelSlotDuration = 15.0;   // Time slot for parallel communication (ms)

    int totalDataPackets = userCount * packetsPerUser; // Total packets to be sent by all users
    int totalPacketsSent = 0;                          // Track total packets sent

    // Use a deque to track remaining packets per user
    std::deque<int> remainingPackets(userCount, packetsPerUser); // Track packets left for each user

    // Step 1: Run the simulation until all packets are sent
    while (totalPacketsSent < totalDataPackets)
    {
        // Step 1: Broadcast a packet (common to all users)
        timeElapsed += broadcastPacketTime;

        // Step 2: Collect CSI packets sequentially from each user
        int userIndex = 0;
        while (userIndex < userCount)
        {
            timeElapsed += csiPacketTime;
            userIndex++;
        }

        // Step 3: Start parallel data transmission within the time slot
        double slotStartTime = timeElapsed;  // Start of the parallel transmission time slot
        int userIndexForSlot = 0;

        // Now, send data packets in parallel for each user
        while (userIndexForSlot < userCount)
        {
            // Continue sending packets for the current user as long as they have remaining packets
            while (remainingPackets[userIndexForSlot] > 0)
            {
                double packetEndTime = timeElapsed + dataPacketTime;

                // If the transmission exceeds the parallel time slot, break
                if (packetEndTime > slotStartTime + parallelSlotDuration)
                {
                    break;
                }

                // Send the packet for this user
                remainingPackets[userIndexForSlot]--;
                totalPacketsSent++;
                timeElapsed = packetEndTime; // Update the time after packet transmission
                latencyData.push_back(timeElapsed);  // Record the latency time
                eventTimestamps.push_back(timeElapsed); // Record the timestamp of the event
            }

            // Move to the next user for parallel transmission
            userIndexForSlot++;
        }
    }

    // Display the results of the simulation
    std::cout << "Simulation Complete:\n";
    std::cout << "Throughput: " << calculateThroughput(totalDataPackets, timeElapsed) << " Mbps\n"; // Throughput
    std::cout << "Average Latency: " << computeAverageLatency() << " ms\n"; // Average Latency
    std::cout << "Max Latency: " << computeMaxLatency() << " ms\n"; // Maximum Latency
}

double WiFi5Simulator::calculateThroughput(int totalDataPackets, double totalSimulationTime) const
{
    assert(totalSimulationTime > 0); // Ensure valid simulation time

    // Convert total data to kilobits (1 KB = 8 kilobits)
    double totalDataInKilobits = totalDataPackets * 8.0;
    double totalSimulationTimeInSeconds = totalSimulationTime / 1000.0; // Convert time from ms to seconds
    return totalDataInKilobits / totalSimulationTimeInSeconds / 1000.0; // Throughput in Mbps
}

double WiFi5Simulator::computeAverageLatency() const
{
    if (latencyData.empty())
    {
        return 0.0;
    }

    // Calculate average latency using accumulate
    double totalLatency = std::accumulate(latencyData.begin(), latencyData.end(), 0.0);
    return totalLatency / latencyData.size(); // Average latency in ms
}

double WiFi5Simulator::computeMaxLatency() const
{
    if (latencyData.empty())
    {
        return 0.0;
    }

    // Find the maximum latency using max_element
    return *std::max_element(latencyData.begin(), latencyData.end()); // Maximum latency in ms
}
