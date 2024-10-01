/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** server
*/

#include "network/Server.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    NetworkLib::Server server(50000);

    while (1)
    {
        sleep(1);
        server.sendToAll("test\n");
    }
}
