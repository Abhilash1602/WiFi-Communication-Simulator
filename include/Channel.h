#ifndef CHANNEL_H
#define CHANNEL_H

class Channel {
public:
    Channel(int bandwidth); 

    bool checkChannelStatus() const; // Verifies if the channel is free (not locked)
    void lockChannel(); // Occupies the channel
    void freeChannel(); // Frees the channel
    int getBandwidth() const; 

private:
    int bandwidth;  // Bandwidth of the channel in MHz
    bool isLocked;  // Channel status (true if locked, false if free)
};

#endif
