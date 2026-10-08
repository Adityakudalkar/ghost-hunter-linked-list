#include "Game.hpp"
#include <iostream>
#include <limits>
#include <cstdlib> // For rand()

Game::Game() : playerPos(nullptr), ghostPos(nullptr), trapsRemaining(2), isRunning(true) {}

void Game::start() {
    hallway.buildDefaultHallway();
    
    playerPos = hallway.head; // Player at Entrance
    
    // Ghost starts at Dining Room (Room 3)
    Room* temp = hallway.head;
    while (temp != nullptr && temp->name != "Dining Room") {
        temp = temp->next;
    }
    ghostPos = temp;

    std::cout << "\n========================================\n";
    std::cout << "   👻 GHOST HUNTER: BALANCED LOGIC       \n";
    std::cout << "========================================\n";

    while (isRunning) {
        processTurn();
    }
}

void Game::moveGhost() {
    if (ghostPos == nullptr) return;

    // 40% chance the ghost idle/scares instead of moving forward
    int roll = rand() % 100;
    if (roll < 40) {
        std::cout << "👻 [Ghost is haunting " << ghostPos->name << " and didn't move!]\n";
        return;
    }

    // Ghost moves forward
    if (ghostPos->next != nullptr) {
        ghostPos = ghostPos->next;
        std::cout << "👻 [Ghost moved forward to " << ghostPos->name << "]\n";
    }

    // Check Trap Condition
    if (ghostPos->hasTrap) {
        std::cout << "\n💥 BOOM! Ghost stepped into a TRAP in " << ghostPos->name << "!\n";
        std::cout << "🏆 YOU CAPTURED THE GHOST! YOU WIN!\n";
        isRunning = false;
        return;
    }

    // Check Escape Condition
    if (ghostPos->name == "Exit") {
        std::cout << "\n😱 The ghost reached the Exit! YOU LOSE!\n";
        isRunning = false;
    }
}

void Game::processTurn() {
    std::cout << "\n----------------------------------------\n";
    std::cout << "📍 Player Location: " << playerPos->name << "\n";

    if (playerPos == ghostPos) {
        std::cout << "\n💥 You walked right into the Ghost! You caught it!\n";
        isRunning = false;
        return;
    }

    std::cout << "\nActions:\n";
    std::cout << "1. Move Forward (1 room)\n";
    std::cout << "2. Scan Room (Traversal Distance)\n";
    std::cout << "3. Set Trap in NEXT room ahead\n";
    std::cout << "4. Quit\n";
    std::cout << "Choice: ";

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    bool validTurn = true;

    switch (choice) {
        case 1:
            if (playerPos->next != nullptr) {
                playerPos = playerPos->next;
                std::cout << "--> Moved to " << playerPos->name << "\n";
            } else {
                std::cout << "⚠️ Reached the end of the hallway.\n";
            }
            break;

        case 2: {
            int dist = hallway.calculateDistance(playerPos, ghostPos);
            std::cout << "\n🔦 SCANNING...\n";
            if (dist > 0) {
                std::cout << "👻 Ghost detected " << dist << " room(s) ahead!\n";
            } else if (dist == 0) {
                std::cout << "👻 Ghost is in your room!\n";
            } else {
                std::cout << "❓ Ghost is behind you or unreachable.\n";
            }
            break;
        }

        case 3:
            if (trapsRemaining > 0) {
                if (playerPos->next != nullptr) {
                    Room* targetRoom = playerPos->next; // Trap node ahead!
                    if (!targetRoom->hasTrap) {
                        targetRoom->hasTrap = true;
                        trapsRemaining--;
                        std::cout << "🪤 Trap armed ahead in " << targetRoom->name << "! (" << trapsRemaining << " left)\n";
                    } else {
                        std::cout << "⚠️ That room already has a trap!\n";
                        validTurn = false;
                    }
                } else {
                    std::cout << "⚠️ Cannot place a trap past the end!\n";
                    validTurn = false;
                }
            } else {
                std::cout << "⚠️ No traps left!\n";
                validTurn = false;
            }
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