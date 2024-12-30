#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <vector>
#include <memory>
#include "User.h"
#include "Channel.h"

class AccessPoint {
private:
    int userCount;  // Total number of users connected
    Channel channel;  // Channel for communication
    std::vector<std::shared_ptr<User>> users;  // List of connected users

public:
    AccessPoint(int userCount, int bandwidth); // Constructor to initialize the AP
    void insertUser(const std::shared_ptr<User>& user);  // Adds a user to the AP
    void controlDataTransmission();  // Manages communication between users and AP
    bool isChannelAvailable();  
    void acquireCommunicationChannel(); 
    void unlockCommunicationChannel();  
    int fetchChannelBandwidth() const;  

    void resolveBackoffConflicts(); // Resolves any backoff time conflicts
};

#endif
