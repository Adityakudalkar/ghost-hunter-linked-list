#ifndef UI_HPP
#define UI_HPP

#include "Room.hpp"
#include <string>

class UI {
public:
    // ANSI Color Codes
    static const std::string RESET;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string CYAN;
    static const std::string MAGENTA;
    static const std::string BOLD;

    static void clearScreen();
    static void drawHeader();
    static void drawMap(Room* head, Room* playerPos, Room* ghostPos);
    static void drawHUD(const std::string& currentRoom, int danger, int traps);
};

#endif