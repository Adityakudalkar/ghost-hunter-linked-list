#include "LinkedList.hpp"
#include <iostream>

HallwayList::HallwayList() : head(nullptr) {}

HallwayList::~HallwayList() {
    clearList();
}

void HallwayList::buildDefaultHallway() {
    clearList();
    
    // Expanded Linked List (8 Nodes)
    head = new Room("Entrance", 0);
    head->next = new Room("Grand Hall", 10);
    head->next->next = new Room("Dining Room", 15);
    head->next->next->next = new Room("Library", 25);
    head->next->next->next->next = new Room("Secret Passage", 35);
    head->next->next->next->next->next = new Room("Haunted Gallery", 50);
    head->next->next->next->next->next->next = new Room("Attic", 70);
    head->next->next->next->next->next->next->next = new Room("Exit", 0);
}

int HallwayList::calculateDistance(Room* startNode, Room* targetNode) {
    if (!startNode || !targetNode) return -1;

    int distance = 0;
    Room* temp = startNode;

    while (temp != nullptr) {
        if (temp == targetNode) {
            return distance;
        }
        distance++;
        temp = temp->next;
    }

    return -1;
}

void HallwayList::clearList() {
    Room* current = head;
    while (current != nullptr) {
        Room* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}