#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>

/**
 * @brief Establishes a connection with the server.
 * 
 * This function creates a socket and attempts to connect to a server
 * specified by the given IP address and port number.
 * 
 * @param ip The server's IP address as a string (e.g., "192.168.0.1").
 * @param port The port number on which the server is listening.
 * @return int The socket file descriptor if the connection is successful, or -1 if an error occurs.
 */
int connectToServer(const std::string& ip, int port);

/**
 * @brief Sends a command to the server.
 * 
 * This function sends a string command to the server over the specified socket.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param command The command string to send to the server.
 */
void sendCommand(int socket, const std::string& command);

/**
 * @brief Receives a response from the server.
 * 
 * This function reads a response from the server over the specified socket.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @return std::string The response from the server as a string. If an error occurs, returns an error message.
 */
std::string receiveResponse(int socket);

/**
 * @brief Sends a command to create a file on the server.
 * 
 * This function sends a request to the server to create a file with the specified name.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file to create on the server.
 */
void createFile(int socket, const std::string& fileName);

/**
 * @brief Sends a command to save content to a file on the server.
 * 
 * This function sends a request to the server to save the specified content into a file with the given name.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file where the content should be saved.
 * @param content The content to save in the file.
 */
void saveToFile(int socket, const std::string& fileName, const std::string& content);

/**
 * @brief Sends a command to delete a file on the server.
 * 
 * This function sends a request to the server to delete a file with the specified name.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file to delete on the server.
 */
void deleteFile(int socket, const std::string& fileName);

#endif // CLIENT_H
