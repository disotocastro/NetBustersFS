#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>  // For creating and managing directories
#include <sstream>

#define FS_BLOCK_SIZE 256
#define UNIT_SIZE 65536
#define FAT_SIZE 256

/**
 * @struct File
 * @brief Structure that represents a file in the FAT filesystem.
 *
 * This structure contains the metadata of a file, including its name,
 * permissions, owner, and other attributes necessary to manage its state and location in the system.
 */
struct File {
    ///< Name of the file.
    std::string name;
    ///< File permissions (e.g., "r--", "rw-").
    std::string permissions;
    ///< File owner (username).
    std::string owner;
    ///< Full name associated with the file owner.
    std::string fullName;  // New field for the full name

    ///< Hashed password of the file owner.
    std::string password;  // New field for the hashed password

    ///< Admin type (privilege level).
    char adminType;
    ///< Boolean array for floor access permissions.
    bool floors[4];
    ///< Boolean array for sensor access permissions.
    bool sensors[3];

    ///< Flag indicating if the file is currently open.
    bool open;
    ///< Index of the file's starting block in the FAT table.
    int startBlock;
    ///< Index of the file's ending block in the FAT table.
    int endBlock;
    ///< Process ID associated with the open file (if applicable).
    int processId;
    ///< Current cursor position for read/write operations.
    int cursor;
    ///< File size in bytes.
    int size;

    /**
     * @brief Default constructor for the File structure.
     *
     * Initializes default values for the file attributes.
     */
    File()
        : name(""),
        permissions("r--"),
        owner(""),
        fullName(""),
        password(""),
        adminType(0),
        open(false),
        startBlock(-1),
        endBlock(-1),
        processId(-1),
        size(0),
        cursor(0) {
        for (int i = 0; i < 4; i++) floors[i] = false;
        for (int i = 0; i < 3; i++) sensors[i] = false;
    }
};

/**
 * @struct Frame
 * @brief Represents a block (frame) in the FAT system, each with a size of BLOCK_SIZE.
 */
struct Frame {
    char frame[FS_BLOCK_SIZE];  ///< Data content of the block.
};

/**
 * @class Filesystem
 * @brief Class that simulates a FAT-based filesystem.
 *
 * This class implements a basic filesystem using a FAT table to manage files.
 * It allows file creation, opening, closing, reading, writing, renaming, deletion, and directory management.
 */
class Filesystem {
private:
    ///< Number of directories in the system.
    int directoryCount;

    ///< FAT block table, where each block contains 8 characters.
    int fatTable[FAT_SIZE];

    ///< Array of frames that represent the storage unit.
    Frame storageUnit[FAT_SIZE];

public:

    ///< Directory containing all files in the system.
    File directory[FAT_SIZE];

    /**
     * @brief Constructor for the Filesystem class.
     * Initializes the filesystem and its components.
     */
    Filesystem();

    /**
     * @brief Destructor for the Filesystem class.
     */
    ~Filesystem();

    /**
     * @brief Opens a file and positions the cursor at the start.
     * @param fileName Name of the file to open.
     * @return True if the file is opened successfully, False otherwise.
     */
    bool open(const std::string& fileName);

    /**
     * @brief Closes a previously opened file.
     * @param fileName Name of the file to close.
     * @return True if the file is closed successfully, False otherwise.
     */
    bool close(const std::string& fileName);

    /**
     * @brief Creates a new file in the directory.
     * @param fileName Name of the file to create.
     * @return True if the file is created successfully, False otherwise.
     */
    bool create(const std::string& fileName);

    /**
     * @brief Reads a specific number of characters from the current cursor position in a file.
     * @param fileName Name of the file to read from.
     * @param bytesToRead Number of characters to read.
     * @return The data read.
     */
    std::string read(const std::string& fileName, int bytesToRead);

    /**
     * @brief Searches for a file in the directory.
     * @param fileName Name of the file to search for.
     * @return The index of the file if found, -1 otherwise.
     */
    int search(const std::string& fileName);

    /**
     * @brief Deletes a file from the directory and frees its blocks in the FAT table.
     * @param fileName Name of the file to delete.
     * @return True if the file is deleted successfully, False otherwise.
     */
    bool remove(const std::string& fileName);

    /**
     * @brief Appends data to an existing file.
     * @param fileName Name of the file.
     * @param data Data to append.
     * @return True if the data is appended successfully, False otherwise.
     */
    bool append(const std::string& fileName, std::vector<char>& data);

    /**
     * @brief Renames an existing file.
     * @param fileName Current name of the file.
     * @param newFileName New name for the file.
     * @return True if the file is renamed successfully, False otherwise.
     */
    bool rename(const std::string& fileName, const std::string& newFileName);

    /**
     * @brief Lists all the files present in the directory.
     */
    void listFiles();

    /**
     * @brief Writes data to a file from the current cursor position.
     *
     * This method writes data to the specified file starting at the current cursor position.
     * If the file does not exist, the corresponding error will be handled.
     *
     * @param fileName Name of the file to write data to.
     * @param data String of characters containing the data to write.
     */
    void write(const std::string& fileName, std::string data);

    /**
     * @brief Synchronizes the cursor of a file to a specific position.
     *
     * This method updates the cursor position for a specific file.
     * It ensures the cursor is in the correct position before performing read or write operations.
     *
     * @param fileIndex Index of the file in the filesystem.
     * @param position New position to move the cursor to.
     */
    void syncCursor(int fileIndex, const int position);

    /**
     * @brief Prints the content of the filesystem.
     *
     * This method displays information about all the files stored in the filesystem,
     * along with relevant metadata such as names and block positions.
     */
    void print();

    /**
     * @brief Changes the cursor position in a file.
     *
     * This method is used for testing, allowing the cursor to be moved to a specific position within the specified file.
     * It is useful for verifying the correct functionality of read and write operations.
     *
     * @param fileName Name of the file whose cursor is to be moved.
     * @param position New cursor position within the file.
     */
    void changeCursor(const std::string& fileName, int position);

    /**
     * @brief Overwrites a file's data.
     * @param fileName Name of the file to overwrite.
     * @param data New data to write to the file.
     * @return True if the data is overwritten successfully, False otherwise.
     */
    bool overwrite(const std::string& fileName, const std::string& data);

    /**
     * @brief Loads data into the filesystem from persistent storage.
     */
    void loadData();

    /**
     * @brief Saves the current state of the filesystem to persistent storage.
     */
    void saveData();

    /**
     * @brief Retrieves a file by its position.
     * @param position Position of the file in the directory.
     * @return Reference to the file at the specified position.
     */
    File& getFile(int position);

    /**
     * @brief Updates the email and full name of a file's owner.
     * @param position Position of the file in the directory.
     * @param password New hashed password.
     * @param email New email address.
     * @param fullName New full name.
     * @param floor1 Access permission to Floor 1.
     * @param floor2 Access permission to Floor 2.
     * @param floor3 Access permission to Floor 3.
     * @param floor4 Access permission to Floor 4.
     * @param humidity Access permission to the humidity sensor.
     * @param movement Access permission to the movement sensor.
     * @param light Access permission to the light sensor.
     * @param adminType New admin type (privilege level).
     */
    void updateFile(int position, const std::string& password, const std::string& email,
                    const std::string& fullName, int floor1, int floor2, int floor3,
                    int floor4, int humidity, int movement, int light, int adminType);

};

#endif // FILESYSTEM_H
