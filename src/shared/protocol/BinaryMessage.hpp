/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** BinaryMessage
*/

#ifndef BINARYMESSAGE_HPP_
#define BINARYMESSAGE_HPP_

#include <iostream>
#include <fstream>
#include <cstring>

class BinaryMessage {
    private:
        unsigned int id;   // message ID (4 bytes)
        std::string content; // message content (256 bytes)

    public:
        // Function to serialize (write in binary)
        void serialize(std::ofstream &ofs) const
        {
            ofs.write(reinterpret_cast<const char *>(&id), sizeof(id)); // Write ID in binary
            ofs.write(content.c_str(), sizeof(content));                // Write content in binary
        }

        // Function to deserialize (read from binary)
        void deserialize(std::ifstream &ifs)
        {
            ifs.read(reinterpret_cast<char *>(&id), sizeof(id));            // Read ID in binary
            ifs.read(reinterpret_cast<char *>(&content), sizeof(content));  // Read content in binary
        }
};

#endif /* !BINARYMESSAGE_HPP_ */
