#include "../Header Files/filesystem.h"
#include <fstream>
#include <sstream>
#include <filesystem>

// Constructor
Filesystem::Filesystem() {
    directoryCount = 0;
    for (int i = 0; i < FAT_SIZE; ++i) {
        fatTable[i] = 0;
        directory[i] = File();
        for (int j = 0; j < FS_BLOCK_SIZE; ++j) {
            storageUnit[i].frame[j] = '\0';
        }
    }

    loadData();
}

Filesystem::~Filesystem() {
    // Save the data to the file when closing
    saveData();
}

bool Filesystem::create(const std::string& fileName) {
    bool result = false;
    int position = search(fileName);
    if (position == -1) {
        for (int i = 0; i < FAT_SIZE; i++) {
            if (directory[directoryCount].name == "") {
                directory[directoryCount].name = fileName;
                directoryCount++;
                result = true;
                return result;
            }
        }
    }

    return result;
}

bool Filesystem::open(const std::string& fileName) {
    int position = search(fileName);
    bool result = false;
    if (position != -1) {
        if (!directory[position].open) {
            directory[position].open = true;
            result = true;
        }
    }
    return result;
}

int Filesystem::search(const std::string& fileName) {
    for (int i = 0; i < FAT_SIZE; i++) {
        if (directory[i].name == fileName) {
            return i;
        }
    }
    return -1;
}

bool Filesystem::overwrite(const std::string& fileName, const std::string& data) {
    int position = search(fileName);
    if (position != -1) {
        File& file = directory[position];

        file.cursor = 0;
        file.size = 0;

        int currentBlock = file.startBlock;
        while (currentBlock != -1) {
            for (int i = 0; i < FS_BLOCK_SIZE; ++i) {
                storageUnit[currentBlock].frame[i] = '\0';
            }
            currentBlock = fatTable[currentBlock];
        }

        write(fileName, data);
    } else {
        std::cout << "Cannot overwrite the file; it does not exist." << std::endl;
        return false;
    }
    return true;
}

bool Filesystem::close(const std::string& fileName) {
    int position = search(fileName);
    bool result = false;
    if (position != -1) {
        if (directory[position].open) {
            directory[position].open = false;
            result = true;
        }
    }
    return result;
}

void Filesystem::listFiles() {
    if (directoryCount == 0) {
        std::cout << "No files in the system." << std::endl;
        return;
    }

    for (int i = 0; i < directoryCount; i++) {
        std::cout << "Directory index: " << i
                  << " | File name: " << directory[i].name
                  << " | Start block: " << directory[i].startBlock
                  << " | End block: " << directory[i].endBlock << " | Status: "
                  << (directory[i].open ? "Open" : "Closed") << std::endl;
    }
}

bool Filesystem::rename(const std::string& fileName, const std::string& newFileName) {
    // Search for the original file
    int originalPosition = search(fileName);
    bool result = true;

    if (originalPosition != -1) {
        int newPosition = search(newFileName);
        if (newPosition == -1) {
            directory[originalPosition].name = newFileName;
        } else {
            result = false;
        }
    } else if (originalPosition == -1) {
        result = false;
    }
    return result;
}

void Filesystem::print() {
    std::cout << "FAT Block Allocation Table:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Block " << i << ": " << fatTable[i] << std::endl;
    }

    std::cout << "\nBlock content:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Block " << i << ": ";
        for (int j = 0; j < 256; ++j) {
            if (storageUnit[i].frame[j] != '\0') {
                std::cout << storageUnit[i].frame[j];
            }
        }
        std::cout << std::endl;
    }
}

void Filesystem::write(const std::string& fileName, std::string data) {
    int position = search(fileName);  // Search the file by name
    if (position != -1) {
        File& file = directory[position];

        int cursor = file.cursor;  // Cursor position in the file
        int currentBlock = file.startBlock;  // Block where the file starts
        int dataCursor = data.length();  // Number of remaining characters to write
        int freeBlockSize;  // Free space in the current block

        // Check if the file has a block assigned
        if (currentBlock == -1) {
            for (int i = 0; i < FAT_SIZE; ++i) {
                if (fatTable[i] == 0) {  // Find a free block
                    currentBlock = i;
                    directory[position].startBlock = i;
                    fatTable[i] = -1;  // Mark as the last block
                    break;
                }
            }
        }

        // Write data in blocks until the data runs out
        while (!data.empty()) {
            freeBlockSize = FS_BLOCK_SIZE - (cursor % FS_BLOCK_SIZE);  // Remaining space in the current block

            // Write data to the current block
            for (int i = cursor % FS_BLOCK_SIZE; i < FS_BLOCK_SIZE && !data.empty(); ++i) {
                storageUnit[currentBlock].frame[i] = data[0];
                data.erase(0, 1);  // Remove the written character
                file.size++;
            }

            // If there is more data to write, assign a new block
            if (!data.empty()) {
                int newBlock = -1;
                for (int i = 0; i < FAT_SIZE; ++i) {
                    if (fatTable[i] == 0) {  // Find a free block
                        newBlock = i;
                        fatTable[currentBlock] = newBlock;  // Link the new block with the current block
                        fatTable[newBlock] = -1;  // Mark as the last block
                        currentBlock = newBlock;
                        break;
                    }
                }

                // If no free blocks are available, end the writing process
                if (newBlock == -1) {
                    std::cout << "No free blocks available to write more data." << std::endl;
                    return;
                }
            }

            // Reset the cursor for the new block
            cursor = 0;
        }

        // Update the file information (end block and cursor position)
        directory[position].endBlock = currentBlock;
        directory[position].cursor += dataCursor;  // Update the file cursor
    } else {
        std::cout << "Cannot write to the file; it does not exist: " << fileName << std::endl;
    }
}

void Filesystem::changeCursor(const std::string& fileName, int pos) {
    for (int i = 0; i < directoryCount; i++) {
        if (directory[i].name == fileName) {
            directory[i].cursor = pos;
        }
    }
}

std::string Filesystem::read(const std::string& fileName, int bytesToRead) {
    int position = search(fileName);
    syncCursor(position, 0);
    if (position == -1) {
        return "";
    }

    File& file = directory[position];
    // Prevent reading beyond the file size
    if (file.cursor + bytesToRead > file.size) {
        bytesToRead = file.size - file.cursor;
    }

    if (bytesToRead <= 0) {
        return "";
    }

    int cursor = file.cursor;
    int currentBlock = file.startBlock;
    std::string dataRead;
    int bytesRead = 0;

    // Traverse the FAT to reach the block where the cursor is
    while ((bytesRead < cursor) && currentBlock != -1) {
        currentBlock = fatTable[currentBlock];
        bytesRead += FS_BLOCK_SIZE;
    }

    // Calculate the offset within the current block
    int blockOffset = cursor % FS_BLOCK_SIZE;
    bytesRead = 0;

    while ((bytesRead < bytesToRead) && currentBlock != -1) {
        // Calculate how many bytes are left to read in this block
        int bytesRemainingInBlock = FS_BLOCK_SIZE - blockOffset;
        int bytesToReadInBlock = std::min(bytesRemainingInBlock, bytesToRead - bytesRead);

        // Read the data from the current block
        for (int i = blockOffset; i < blockOffset + bytesToReadInBlock; i++) {
            dataRead += storageUnit[currentBlock].frame[i];
        }

        bytesRead += bytesToReadInBlock;
        blockOffset = 0;  // For the next blocks, read from the start
        // Move to the next block in the FAT
        currentBlock = fatTable[currentBlock];
    }

    // Update the cursor
    file.cursor += bytesRead;

    return dataRead;
}

void Filesystem::syncCursor(int fileIndex, const int position) {
    directory[fileIndex].cursor = position;
}

void Filesystem::loadData() {
    std::filesystem::create_directory("users");  // Create the 'users' directory if it does not exist

    std::ifstream file("users/users_data.txt");
    if (file) {
        std::cout << "Loading data from 'users/users_data.txt'..." << std::endl;
        directoryCount = 0;  // Reset directory count when loading
        int currentBlock = 0;  // Variable to assign blocks to files

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream in(line);
            std::string part;
            std::vector<std::string> parts;

            // Split the line by commas
            while (std::getline(in, part, ',')) {
                parts.push_back(part);
            }

            // Verify the correct number of parts before processing
            if (parts.size() == 12) {
                std::string name = parts[0];
                std::string password = parts[1];  // Hashed password
                std::string email = parts[2];
                std::string fullName = parts[3];
                char adminType = static_cast<char>(std::stoi(parts[4]));  // Convert to char

                // Create the file in the system
                create(name);
                int pos = search(name);
                directory[pos].password = password;  // Load the password
                directory[pos].owner = email;
                directory[pos].fullName = fullName;
                directory[pos].adminType = adminType;

                std::cout << "Loaded user: " << name << std::endl;

                // Load access to floors and sensors
                for (int j = 0; j < 4; j++) {
                    directory[pos].floors[j] = std::stoi(parts[5 + j]);
                }
                for (int j = 0; j < 3; j++) {
                    directory[pos].sensors[j] = std::stoi(parts[9 + j]);
                }
            }
        }
    } else {
        std::cout << "'users_data.txt' file does not exist.\n";
    }
}

void Filesystem::saveData() {
    std::filesystem::create_directory("users");  // Create 'users' directory if it does not exist

    std::ofstream file("users/users_data.txt");

    if (file) {
        for (int i = 0; i < directoryCount; i++) {
            if (!directory[i].name.empty()) {
                std::string userData = directory[i].name + "," +
                                       directory[i].password + "," +  // Hashed password
                                       directory[i].owner + "," +
                                       directory[i].fullName + "," +
                                       std::to_string(static_cast<int>(directory[i].adminType)) + ",";

                // Save floor access
                for (int j = 0; j < 4; j++) {
                    userData += std::to_string(directory[i].floors[j]) + ",";
                }

                // Save sensor access
                for (int j = 0; j < 3; j++) {
                    userData += std::to_string(directory[i].sensors[j]);
                    if (j < 2) userData += ",";  // Add comma between sensor values
                }

                file << userData << "\n";  // Write the full line to the file
            }
        }
        std::cout << "Data successfully saved to users_data.txt.\n";
    } else {
        std::cout << "Unable to open users_data.txt for writing.\n";
    }
}

File& Filesystem::getFile(int position) {
    return directory[position];
}

void Filesystem::updateFile(int position, const std::string& password,
                            const std::string& email, const std::string& fullName,
                            int floor1, int floor2, int floor3, int floor4,
                            int humidity, int movement, int light, int adminType) {
    directory[position].password = password;  // Update password hash
    directory[position].owner = email;        // Update email
    directory[position].fullName = fullName;  // Update full name
    directory[position].floors[0] = floor1;   // Save access to first floor
    directory[position].floors[1] = floor2;   // Save access to second floor
    directory[position].floors[2] = floor3;   // Save access to third floor
    directory[position].floors[3] = floor4;   // Save access to fourth floor
    directory[position].sensors[0] = humidity;  // Save access to humidity/temperature sensor
    directory[position].sensors[1] = movement;  // Save access to movement sensor
    directory[position].sensors[2] = light;     // Save access to light sensor
    directory[position].adminType = adminType;  // Save user type
}

bool Filesystem::remove(const std::string& fileName) {
    int position = search(fileName);
    if (position != -1) {
        // Free the blocks used by the file in the FAT
        int currentBlock = directory[position].startBlock;
        while (currentBlock != -1) {
            int nextBlock = fatTable[currentBlock];  // Save the next block
            fatTable[currentBlock] = 0;  // Free the current block
            currentBlock = nextBlock;
        }

        // Clear the file data
        directory[position] = File();  // Reset the file structure to its default values
        directoryCount--;  // Decrease the file count
        return true;
    }
    return false;  // File not found
}
