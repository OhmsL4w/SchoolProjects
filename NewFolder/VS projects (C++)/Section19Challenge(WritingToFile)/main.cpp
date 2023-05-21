// Section 19
// Challenge 4
// Copy Romeo and Juliet with line numbers
#include <iostream>
#include <fstream>
#include <istream>
#include <iomanip>
#include <string>

int main() {
    std::ofstream out_file{ "Romeo&JulietWnums.txt"};
    std::ifstream in_file;
    std::string line{};
    int lineNumber{ 0 };
    in_file.open("romeoandjuliet.txt");

    if (!in_file) {
      std::cerr << "Error opening input file" << std::endl;
    }

    if (!out_file) {
        std::cerr << "Error opening output file" << std::endl;
    }

    while (std::getline(in_file,line)) {
        if (line.size() == 0) {
            out_file <<"             " << line << std::endl;
            continue;
        }
        out_file << lineNumber << "             " << line << std::endl;
        
        lineNumber++;
    }
    std::cout << "file copy complete";
    in_file.close();
    out_file.close();
    return 0;
}

