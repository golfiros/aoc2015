#include <iostream>
#include <fstream> 
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

//Useful: Parse string into tokens with delimeter

std::vector<std::string> delSplit(std::string s, std::string del) {
    size_t start = 0, len = del.length();
    std::vector<std::string> out;

    for (size_t end; (end = s.find(del,start)) != std::string::npos; start = end + len) {
        out.push_back(s.substr(start, end - start));
    }

    out.push_back(s.substr(start));
    return out;
}

int main(int argc, char** argv) {
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
    
    /*
    //Declare present datatype
    struct Present {
        private:
            uint8_t a, b, c;
        public:
            Present(uint8_t a0, uint8_t b0, uint8_t c0) {
                a = a0; b = b0; c = c0;
            };
            uint16_t getArea() {
                uint16_t A, B, C;
                A = b * c; B = c * a; C = a * b
                return 2*A+2*B+2*C+std::min({A, B, C});
            }
    }
    */

    //Read and process the data
    uint32_t paper = 0;
    uint32_t ribbon = 0;
    for(std::string entry; std::getline(file,entry); ) {
 
        std::vector<std::string> sides = delSplit(entry, "x");
        uint16_t a, b, c;
        a = std::stoi(sides[0]);
        b = std::stoi(sides[1]);
        c = std::stoi(sides[2]);

        uint16_t A, B, C;
        A = b * c; B = c * a; C = a * b;
        paper += 2 * A + 2 * B + 2 * C + std::min({A, B, C});

        ribbon += a * b * c + 2 * (a + b + c - std::max({a, b, c}));
    }

    //Don't need the file anymore.
    file.close();

    std::cout << "Minimum paper needed: " << paper << std::endl;
    std::cout << "Minimum ribbon needed: " << ribbon << std::endl;
    return 0;
}