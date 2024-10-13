/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** test_NetworkEngine
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../src/client/NetworkEngine/NetworkEngine.hpp"
#include "../../src/client/NetworkEngine/Client.hpp"

void create_server(int port) {
    // Create a fake server on port 50000
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to bind socket");
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Failed to listen on socket");
        close(serverSocket);
        return;
    }

    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            perror("Failed to accept client connection");
            close(serverSocket);
            return;
        }

        const char* data = "hello";
        if (send(clientSocket, data, strlen(data), 0) == -1) {
            perror("Failed to send data to client");
            close(clientSocket);
            close(serverSocket);
            return;
        }

        close(clientSocket);
    }

    close(serverSocket);
}

Test(NetworkEngine, testConstructor) {
    std::shared_ptr<RType::NetworkEngine> networkEngine = std::make_shared<RType::NetworkEngine>();
    cr_assert_not_null(networkEngine);
}

Test(NetworkEngine, testUpdateData) {
    std::shared_ptr<RType::NetworkEngine> networkEngine = std::make_shared<RType::NetworkEngine>();
    cr_assert_not_null(networkEngine);

    cr_redirect_stdout();
    cr_redirect_stderr();

    create_server(50000);

    networkEngine->updateData();

    cr_assert_stdout_eq_str("hello\n");
}