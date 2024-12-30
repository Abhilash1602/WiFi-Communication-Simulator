#include "Channel.h"
#include <iostream>

// Constructor to initialize the channel with a given bandwidth
Channel::Channel(int bandwidth) : bandwidth(bandwidth), isLocked(false) {}

// Verifies if the channel is free for communication
bool Channel::checkChannelStatus() const
{
    return !isLocked; // Channel is free if it's not locked
}

// Locks the channel, marking it as occupied
void Channel::lockChannel()
{
    isLocked = true;
    std::cout << "[Action] Channel is now occupied.\n";
}

// Releases the channel, marking it as free for others to use
void Channel::freeChannel()
{
    isLocked = false;
    std::cout << "[Action] Channel is now released.\n";
}

// Returns the bandwidth of the channel
int Channel::getBandwidth() const
{
    return bandwidth;
}
