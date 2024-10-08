/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** server
*/

#include "network/Server.hpp"
#include <thread>
#include "GameLogique/GameLogique.hpp"

int main(int argc, char* argv[])
{
    int frequency = 60;

    if ((argc != 2 && argc != 3) || !std::all_of(argv[1], argv[1] + std::strlen(argv[1]), ::isdigit))  {
        return 84;
    }
    if (argc == 3 && std::all_of(argv[2], argv[2] + std::strlen(argv[2]), ::isdigit)) {
        frequency = atoi(argv[2]);
    }
    GameLogique gameLogique(atoi(argv[1]), frequency);
    gameLogique.runGame();

    return 0;
}
