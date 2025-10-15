#ifndef UUIDGENERATOR_H
#define UUIDGENERATOR_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>

class UUIDGenerator {
public:
    static std::string generateUUID() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);
        std::uniform_int_distribution<> dis2(8, 11);

        std::stringstream ss;
        
        // Generate 32 hexadecimal characters
        for (int i = 0; i < 32; i++) {
            // Insert hyphens at appropriate positions (8-4-4-4-12 format)
            if (i == 8 || i == 12 || i == 16 || i == 20) {
                ss << "-";
            }
            
            // For position 13, set the 4 most significant bits to 4 (version 4)
            if (i == 13) {
                ss << "4";
                continue;
            }
            
            // For position 17, set the 2 most significant bits to 10 (variant 1)
            if (i == 17) {
                ss << std::hex << dis2(gen);
                continue;
            }
            
            ss << std::hex << dis(gen);
        }
        
        return ss.str();
    }
};

#endif // UUIDGENERATOR_H
