#ifndef GAME_HPP
#define GAME_HPP

#include "Room.hpp"       // Fix: Direct reference to Room struct
#include "LinkedList.hpp"

class Game {
private:
    HallwayList hallway;
    Room* playerPos;
    Room* ghostPos;
    int trapsRemaining;
    bool isRunning;

    void moveGhost();

public:
    Game();
    void start();
    void processTurn();
};

#endif