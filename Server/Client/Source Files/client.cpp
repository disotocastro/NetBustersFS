#include "../Header Files/client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int connectToServer(const std::string& ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid or unsupported address" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection error with server" << std::endl;
        return -1;
    }

    std::cout << "Connected to server" << std::endl;
    return sock;
}

void sendCommand(int socket, const std::string& command) {
    send(socket, command.c_str(), command.length(), 0);
}

std::string receiveResponse(int socket) {
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    if (valread > 0) {
        return std::string(buffer);
    }
    return "Error receiving response";
}

void createFile(int socket, const std::string& fileName) {
    std::string command = "createFile " + fileName;
    sendCommand(socket, command);
    std::string response = receiveResponse(socket);
    std::cout << "Server response: " << response << std::endl;
}

void saveToFile(int socket, const std::string& fileName, const std::string& content) {
    std::string command = "save " + fileName + " " + content;
    sendCommand(socket, command);
    std::string response = receiveResponse(socket);
    std::cout << "Server response: " << response << std::endl;
}

void deleteFile(int socket, const std::string& fileName) {
    std::string command = "deleteFile " + fileName;
    sendCommand(socket, command);
    std::string response = receiveResponse(socket);
    std::cout << "Server response: " << response << std::endl;
}


void sendFileContent(int socket, const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::ofstream newFile(fileName);
        newFile << "Initial content";
        newFile.close();
        file.open(fileName);
        if (!file.is_open()) {
            std::cerr << "Error creating or opening file: " << fileName << std::endl;
            return;
        }
    }

    std::ostringstream fileContent;
    fileContent << file.rdbuf();
    file.close();

    std::string command = "save " + fileName + " " + fileContent.str();
    sendCommand(socket, command);
    std::string response = receiveResponse(socket);
    std::cout << "Server response: " << response << std::endl;
}


void authenticate(int socket, const std::string& username, const std::string& password) {
    std::string command = "authenticate " + username + " " + password;
    sendCommand(socket, command);
    std::string response = receiveResponse(socket);
    std::cout << "Authentication response: " << response << std::endl;
}
