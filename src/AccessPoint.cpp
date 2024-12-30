#include "AccessPoint.h"
#include <iostream>
#include <cstdlib>  // for rand()

AccessPoint::AccessPoint(int userCount, int bandwidth) : userCount(userCount), channel(bandwidth) {}

void AccessPoint::insertUser(const std::shared_ptr<User>& user) {
    users.push_back(user);
    std::cout << "Added User " << user->getUserId() << " to the Access Point.\n";
}

bool AccessPoint::isChannelAvailable() {
    return channel.checkChannelStatus();
}

void AccessPoint::acquireCommunicationChannel() {
    channel.lockChannel();
}

void AccessPoint::unlockCommunicationChannel() {
    channel.freeChannel();
}

int AccessPoint::fetchChannelBandwidth() const {
    return channel.getBandwidth();
}

void AccessPoint::resolveBackoffConflicts() {
    for (size_t i = 0; i < users.size(); ++i) {
        for (size_t j = i + 1; j < users.size(); ++j) {
            if (users[i]->getBackoffTime() == users[j]->getBackoffTime()) {
                // If there's a conflict, reassign the backoff time for the second user
                int newBackoffTime = rand() % 10 + 1;  // Assign a new random backoff time
                users[j]->setBackoffTime(newBackoffTime);
                std::cout << "[Conflict Resolved] User " << users[j]->getUserId() 
                          << " had the same backoff time as User " << users[i]->getUserId() 
                          << ". New backoff time: " << newBackoffTime << " ms\n";
            }
        }
    }
}

void AccessPoint::controlDataTransmission() {
    // Before processing the transmission, resolve any backoff time conflicts
    resolveBackoffConflicts();

    for (auto& user : users) {
        bool transmissionSuccessful = false;
        std::cout << "User " << user->getUserId() << " waiting (backoff: " 
                  << user->getBackoffTime() << " ms, current time: 0.0000 ms)\n";

        while (!transmissionSuccessful) {
            if (channel.checkChannelStatus()) {  // Channel is available
                channel.lockChannel();
                Packet packet = user->buildPacket();
                std::cout << "[Info] User " << user->getUserId() << " transmitted a packet of size "
                          << packet.getPacketSize() << " KB.\n";
                user->incrementPacketCount();
                transmissionSuccessful = true;
                channel.freeChannel();  // Release the channel after transmission
            } else {
                // Random backoff between 1-10 ms if the channel is busy
                int backoffDuration = rand() % 10 + 1;
                user->setBackoffTime(backoffDuration);  // Set the backoff time
                std::cout << "[Warning] User " << user->getUserId() << " backs off for " 
                          << backoffDuration << " ms.\n";
            }
        }
    }
}
