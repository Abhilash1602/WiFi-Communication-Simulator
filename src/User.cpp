#include "User.h"
#include "Packet.h"
#include <iostream>
#include <cstdlib>  // for rand()

User::User(int id) : id(id), packetCount(0), backoffTime(0) {}

int User::getUserId() const {
    return id;
}

Packet User::buildPacket() {
    // For simplicity, returning a packet of fixed size
    return Packet(1);  // 1 KB packet
}

int User::retrieveSentPacketCount() const {
    return packetCount;
}

void User::incrementPacketCount() {
    packetCount++;
}

void User::setBackoffTime(int time) {
    backoffTime = time;
}

int User::getBackoffTime() const {
    return backoffTime;
}

void User::resetBackoffTime() {
    backoffTime = rand() % 10 + 1;  // Assign a random backoff time between 1 and 10 ms
}

void User::decrementBackoffTime() {
    if (backoffTime > 0) {
        --backoffTime;
    }
}

bool User::hasBackoffExpired() const {
    return backoffTime <= 0;
}
