#include <iostream>
#include <fstream> 
#include <cstdint>

int main (int argc, char** argv) {
    // First argument is filename
    if (argc != 2) {
        std::cerr << "Unexpected number of arguments" << std::endl;
        return 1;
    }

    // Try to open file
    std::ifstream file;
    file.open(argv[1]);

    if (!file.is_open()){
        std::cout << "Unable to open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    //Initialize counter
    int16_t floor = 0;
    uint16_t basement = 0;
    uint8_t cross = false;

    //Read all characters in file
    for(char byte; file.get(byte); ) {
        if (byte == '(') {
            floor++;
        }
        else {
            floor--;
        }
        if(!cross) {
            if (floor < 0) {
                basement = file.tellg();
                cross = true;
            }
        }
    }

    //Don't need the file anymore.
    file.close();

    std::cout << "Final floor: " << floor << std::endl;
    std::cout << "Basement at command: " << basement << std::endl;

    return 0;
}