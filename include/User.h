#ifndef USER_H 
#define USER_H

#include "Packet.h"
#include <memory>
#include <iostream>
#include <cstdlib>

class User {
private:
    int id;                // Unique identifier for the user
    int packetCount;       // Number of packets sent by this user
    int backoffTime;       // Backoff time for the user in milliseconds

public:
    User(int id);                          // Constructor to initialize user
    int getUserId() const;                 // Gets the user's ID
    Packet buildPacket();               // Generates a new packet for transmission
    int retrieveSentPacketCount() const;        // Gets the count of sent packets
    void incrementPacketCount();      // Increments the number of packets sent

    void setBackoffTime(int time);         // Sets the backoff time for the user
    int getBackoffTime() const;            // Gets the current backoff time
    void resetBackoffTime();               // Resets the backoff time to a random value
    void decrementBackoffTime();           // Decrements the backoff time after each cycle
    bool hasBackoffExpired() const;        // Checks if the backoff time has ended
};

#endif
