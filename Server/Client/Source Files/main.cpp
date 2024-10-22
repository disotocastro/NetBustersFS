#include <unistd.h>  // Required for the close() function
#include "../Header Files/client.h"

int main() {
    std::string serverIp = "192.168.0.19";  // Change this IP if the server is on a different host or use "localhost" if necessary
    int port = 8081;

    // Connect to the server
    int socket = connectToServer(serverIp, port);
    if (socket == -1) {
        return -1;  // Exit if the connection fails
    }

    // Execute commands
    createFile(socket, "example.txt");
    saveToFile(socket, "example.txt", "This is the file content");
    deleteFile(socket, "example.txt");

    // Close the socket
    close(socket);

    return 0;
}
