#include "UI.hpp"
#include <iostream>

const std::string UI::RESET   = "\033[0m";
const std::string UI::RED     = "\033[31m";
const std::string UI::GREEN   = "\033[32m";
const std::string UI::YELLOW  = "\033[33m";
const std::string UI::CYAN    = "\033[36m";
const std::string UI::MAGENTA = "\033[35m";
const std::string UI::BOLD    = "\033[1m";

void UI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void UI::drawHeader() {
    std::cout << BOLD << MAGENTA;
    std::cout << "=========================================================\n";
    std::cout << "          GHOST HUNTER: LINKED LIST EDITION              \n";
    std::cout << "=========================================================\n" << RESET;
}

void UI::drawMap(Room* head, Room* playerPos, Room* ghostPos) {
    std::cout << "\n" << BOLD << CYAN << "[ HAUNTED HALLWAY LINKED LIST MAP ]" << RESET << "\n";
    
    Room* temp = head;
    while (temp != nullptr) {
        std::cout << "[ " << temp->name << " ";
        
        // Character positions
        if (temp == playerPos && temp == ghostPos) {
            std::cout << RED << "P+G" << RESET;
        } else if (temp == playerPos) {
            std::cout << GREEN << "P" << RESET;
        } else if (temp == ghostPos) {
            std::cout << MAGENTA << "G" << RESET;
        }
        
        if (temp->hasTrap) {
            std::cout << YELLOW << " [TRAP]" << RESET;
        }

        std::cout << " ]";

        if (temp->next != nullptr) {
            std::cout << " -> ";
        }
        temp = temp->next;
    }
    std::cout << " -> " << RED << "[EXIT]" << RESET << "\n\n";
}

void UI::drawHUD(const std::string& currentRoom, int danger, int traps) {
    std::cout << BOLD << "+-------------------------------------------------------+\n";
    std::cout << "| Location: " << CYAN << currentRoom << RESET << BOLD << "\n";
    std::cout << "| Danger Level: " << RED << danger << RESET << BOLD << "\n";
    std::cout << "| Traps Left: " << YELLOW << traps << RESET << BOLD << "\n";
    std::cout << "+-------------------------------------------------------+\n" << RESET;
}