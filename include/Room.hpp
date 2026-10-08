#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>

struct Room {
    std::string name;
    int danger;
    bool hasTrap;
    Room* next;

    Room(std::string roomName, int dangerLevel = 10)
        : name(roomName), danger(dangerLevel), hasTrap(false), next(nullptr) {}
};

#endif