#include <unistd.h>
#include "../Header Files/client.h"

int main() {
    std::string serverIp = "127.0.0.1";
    int port = 8081;

    // Connect to the server
    int socket = connectToServer(serverIp, port);
    if (socket == -1) {
        return -1;
    }

    // Execute commands
    createFile(socket, "example.txt");
    saveToFile(socket, "example.txt", "This is the file content");
    sendFileContent(socket, "example.txt");
    authenticate(socket, "tatis.txt", "password123");
    deleteFile(socket, "example.txt");

    // Close the socket
    close(socket);

    return 0;
}
