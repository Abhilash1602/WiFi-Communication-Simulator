#include "Packet.h"
#include <iostream>

// Constructor initializes packet with a given size (default is 1 KB)
Packet::Packet(int size) : sizeInKB(size), transmissionDuration(0.0) {}

// Gets the size of the packet
int Packet::getPacketSize() const
{
    return sizeInKB;
}

// Sets the time required to transmit the packet
void Packet::setTransmissionDuration(double time)
{
    transmissionDuration = time;
    std::cout << "[Info] Transmission time set to: " << transmissionDuration << " ms.\n";
}

// Gets the time taken to transmit the packet
double Packet::fetchTransmissionDuration() const
{
    return transmissionDuration;
}
