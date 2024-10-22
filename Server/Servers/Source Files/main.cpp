#include "../Header Files/filesystem.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

void handleCommand(Filesystem &fs, const std::string &command, int clientSocket) {
    if (command.find("createFile") == 0) {
        std::string fileName = command.substr(command.find(" ") + 1);
        if (fs.create(fileName)) {
            std::string response = "File created: " + fileName + "\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        } else {
            std::string response = "Error creating file: " + fileName + "\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    } else if (command.find("save") == 0) {
        size_t firstSpace = command.find(" ");
        size_t secondSpace = command.find(" ", firstSpace + 1);
        std::string fileName = command.substr(firstSpace + 1, secondSpace - firstSpace - 1);
        std::string data = command.substr(secondSpace + 1);

        if (fs.overwrite(fileName, data)) {
            std::string response = "File content saved: " + fileName + "\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        } else {
            std::string response = "Error saving content to: " + fileName + "\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    } else if (command.find("deleteFile") == 0) {
        std::string fileName = command.substr(command.find(" ") + 1);
        if (fs.remove(fileName)) {
            std::string response = "File deleted: " + fileName + "\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        } else {
            std::string response = "Error deleting file: " + fileName + "\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    } else if (command.find("authenticate") == 0) {
        size_t firstSpace = command.find(" ");
        size_t secondSpace = command.find(" ", firstSpace + 1);
        std::string username = command.substr(firstSpace + 1, secondSpace - firstSpace - 1);
        std::string password = command.substr(secondSpace + 1);

        int position = fs.search(username);
        if (position != -1 && fs.getFile(position).password == password) {
            std::string response = "Authentication successful\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        } else {
            std::string response = "Authentication failed\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    } else {
        std::string response = "Unrecognized command: " + command + "\n";
        send(clientSocket, response.c_str(), response.size(), 0);
    }
}

int main() {
    Filesystem fs;

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024] = {0};

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0) {
        std::cerr << "Error creating the server socket" << std::endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8081);

    // Bind the socket to an IP address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error in bind" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Error in listen" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server listening on port 8081" << std::endl;

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection" << std::endl;
            close(serverSocket);
            return -1;
        }

        // Keep the connection open until the client sends "exit"
        bool keepConnection = true;
        while (keepConnection) {
            memset(buffer, 0, 1024);
            int bytesRead = read(clientSocket, buffer, 1024);
            if (bytesRead <= 0) {
                keepConnection = false;
                break;
            }

            std::string command(buffer);
            std::cout << "Command received: " << command << std::endl;

            // Process the command
            if (command.find("exit") == 0) {
                keepConnection = false;
                std::string response = "Closing the connection...\n";
                send(clientSocket, response.c_str(), response.size(), 0);
            } else {
                handleCommand(fs, command, clientSocket);
            }
        }

        // Close the client socket after exiting the loop
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    return 0;
}
