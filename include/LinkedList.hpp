#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Room.hpp"

class HallwayList {
public:
    Room* head;

    HallwayList();
    ~HallwayList();

    void buildDefaultHallway();
    int calculateDistance(Room* startNode, Room* targetNode);
    void clearList();
};

#endif