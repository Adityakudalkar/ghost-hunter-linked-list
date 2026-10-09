#include "Game.hpp"
#include "UI.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

Game::Game() : playerPos(nullptr), ghostPos(nullptr), trapsRemaining(2), isRunning(true) {}

void Game::start() {
    hallway.buildDefaultHallway();
    
    playerPos = hallway.head; // Player starts at Entrance
    
    // Ghost starts at Dining Room
    Room* temp = hallway.head;
    while (temp != nullptr && temp->name != "Dining Room") {
        temp = temp->next;
    }
    ghostPos = temp;

    while (isRunning) {
        processTurn();
    }
}

void Game::moveGhost() {
    if (ghostPos == nullptr) return;

    // 40% chance ghost stays in place
    int roll = rand() % 100;
    if (roll < 40) {
        std::cout << UI::MAGENTA << "\n👻 Ghost is haunting " << ghostPos->name << " and stayed still!\n" << UI::RESET;
        return;
    }

    if (ghostPos->next != nullptr) {
        ghostPos = ghostPos->next;
        std::cout << UI::MAGENTA << "\n👻 Ghost moved forward to " << ghostPos->name << "!\n" << UI::RESET;
    }

    // Check Trap Condition
    if (ghostPos->hasTrap) {
        UI::clearScreen();
        UI::drawHeader();
        UI::drawMap(hallway.head, playerPos, ghostPos);
        std::cout << UI::GREEN << UI::BOLD << "\n💥 BOOM! Ghost stepped into a TRAP in " << ghostPos->name << "!\n";
        std::cout << "🏆 YOU CAPTURED THE GHOST! YOU WIN!\n" << UI::RESET;
        isRunning = false;
        return;
    }

    // Check Escape Condition
    if (ghostPos->name == "Exit") {
        UI::clearScreen();
        UI::drawHeader();
        UI::drawMap(hallway.head, playerPos, ghostPos);
        std::cout << UI::RED << UI::BOLD << "\n😱 The ghost reached the Exit! YOU LOSE!\n" << UI::RESET;
        isRunning = false;
    }
}

void Game::processTurn() {
    UI::clearScreen();
    UI::drawHeader();
    UI::drawMap(hallway.head, playerPos, ghostPos);
    UI::drawHUD(playerPos->name, playerPos->danger, trapsRemaining);

    if (playerPos == ghostPos) {
        std::cout << UI::GREEN << UI::BOLD << "\n💥 You walked directly into the Ghost! You caught it! YOU WIN!\n" << UI::RESET;
        isRunning = false;
        return;
    }

    std::cout << UI::BOLD << "\nActions:\n" << UI::RESET;
    std::cout << "1. Move Forward (1 room)\n";
    std::cout << "2. Scan Room (Distance check)\n";
    std::cout << "3. Set Trap in NEXT room ahead\n";
    std::cout << "4. Quit\n";
    std::cout << UI::CYAN << "Choice: " << UI::RESET;

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    bool validTurn = true;

    switch (choice) {
        case 1:
            if (playerPos->next != nullptr) {
                playerPos = playerPos->next;
            } else {
                std::cout << "⚠️ Reached the end of the hallway.\n";
            }
            break;

        case 2: {
            int dist = hallway.calculateDistance(playerPos, ghostPos);
            std::cout << UI::YELLOW << "\n🔦 SCANNING...\n" << UI::RESET;
            if (dist > 0) {
                std::cout << UI::CYAN << "👻 Ghost detected " << dist << " room(s) ahead!\n" << UI::RESET;
            } else if (dist == 0) {
                std::cout << UI::RED << "👻 Ghost is in your room!\n" << UI::RESET;
            } else {
                std::cout << "❓ Ghost is behind you or unreachable.\n";
            }
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 3:
            if (trapsRemaining > 0) {
                if (playerPos->next != nullptr) {
                    Room* targetRoom = playerPos->next;
                    if (!targetRoom->hasTrap) {
                        targetRoom->hasTrap = true;
                        trapsRemaining--;
                        std::cout << UI::GREEN << "\n🪤 Trap set in " << targetRoom->name << "!\n" << UI::RESET;
                    } else {
                        std::cout << "\n⚠️ That room already has a trap!\n";
                        validTurn = false;
                    }
                } else {
                    std::cout << "\n⚠️ Cannot place a trap past the end!\n";
                    validTurn = false;
                }
            } else {
                std::cout << "\n⚠️ No traps left!\n";
                validTurn = false;
            }
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;

        case 4:
            isRunning = false;
            return;

        default:
            validTurn = false;
            break;
    }

    if (isRunning && validTurn) {
        moveGhost();
    }
}