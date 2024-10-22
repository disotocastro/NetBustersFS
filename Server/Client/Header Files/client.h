#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Establishes a connection with the server.
 * 
 * @param ip The server's IP address as a string (e.g., "192.168.0.1").
 * @param port The port number on which the server is listening.
 * @return int The socket file descriptor if the connection is successful, or -1 if an error occurs.
 */
int connectToServer(const std::string& ip, int port);

/**
 * @brief Sends a command to the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param command The command string to send to the server.
 */
void sendCommand(int socket, const std::string& command);

/**
 * @brief Receives a response from the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @return std::string The response from the server as a string. If an error occurs, returns an error message.
 */
std::string receiveResponse(int socket);

/**
 * @brief Sends a command to create a file on the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file to create on the server.
 */
void createFile(int socket, const std::string& fileName);

/**
 * @brief Sends a command to save content to a file on the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file where the content should be saved.
 * @param content The content to save in the file.
 */
void saveToFile(int socket, const std::string& fileName, const std::string& content);

/**
 * @brief Sends a command to delete a file on the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file to delete on the server.
 */
void deleteFile(int socket, const std::string& fileName);

/**
 * @brief Opens a file and sends its content to the server.
 * 
 * This function opens a local file and sends its content along with the command to save it on the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param fileName The name of the file to open and send.
 */
void sendFileContent(int socket, const std::string& fileName);

/**
 * @brief Sends authentication data to the server.
 * 
 * This function sends a username and password to authenticate with the server.
 * 
 * @param socket The socket file descriptor for the server connection.
 * @param username The username for authentication.
 * @param password The password for authentication.
 */
void authenticate(int socket, const std::string& username, const std::string& password);

#endif // CLIENT_H
