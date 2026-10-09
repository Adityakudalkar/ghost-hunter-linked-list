#ifndef GAME_HPP
#define GAME_HPP

#include "Room.hpp"
#include "LinkedList.hpp"
#include "UI.hpp" // Integrated UI class

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