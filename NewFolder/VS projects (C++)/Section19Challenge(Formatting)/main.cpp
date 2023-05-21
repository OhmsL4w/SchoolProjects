// Section 19
// Challenge 2
// Automated Grader
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
int main() {

    std::ifstream in_file;
    in_file.open("responses.txt");
    if (!in_file) {
        std::cerr << "problem opening file" << std::endl;
        return 1;
    }
    std::cout << "Student" << std::setw(15) << "Score";
    std::cout << "\n" << std::setfill('-') << std::setw(25) << " " << std::endl;
    std::cout << std::setfill(' ') << std::setw(0);

    //std::cout << "------------------------------------" << std::endl;
    std::string key{};
    std::getline(in_file, key);
    std::string temp{};
    int count{ 1 };
    while (!in_file.eof()) {
        
        std::getline(in_file, temp);
        if ((count%2) != 0) {
            std::cout << std::left << std::setw(15)<< temp;
            count++;
            continue;
        }
        else {
            int score{ 0 };
            for (size_t i = 0; i < temp.length(); i++)
            {
                
                if (temp[i] == key[i]) {
                    score++;
                }
                
            }
            std::cout << std::setw(5) << std::right << score << std::endl;
            count++;
        }
       
    }


    in_file.close();
    return 0;
}

