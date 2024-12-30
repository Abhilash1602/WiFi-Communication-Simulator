#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int sizeInKB;              // Size of the packet in KB
    double transmissionDuration; // Time taken to transmit the packet

public:
    Packet(int size = 1);                  // Default to 1 KB packets
    int getPacketSize() const;             // Gets the size of the packet
    void setTransmissionDuration(double time); // Sets the time required for transmission
    double fetchTransmissionDuration() const;    // Retrieves the transmission time
};

#endif
