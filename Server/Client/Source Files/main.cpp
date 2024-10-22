#include <unistd.h>
#include "../Header Files/client.h"

int main() {
    std::string serverIp = "192.168.0.19";
    int port = 8081;

    // Connect to the server
    int socket = connectToServer(serverIp, port);
    if (socket == -1) {
        return -1;  // Exit if the connection fails
    }

    // Execute commands
    createFile(socket, "example.txt");
    saveToFile(socket, "example.txt", "This is the file content");
    sendFileContent(socket, "example.txt");  // Send file content
    authenticate(socket, "tatis.txt", "password123");
    deleteFile(socket, "example.txt");

    // Close the socket
    close(socket);

    return 0;
}
