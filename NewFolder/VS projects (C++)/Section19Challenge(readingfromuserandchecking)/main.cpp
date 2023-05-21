// Section 19
// Challenge 3
// Word counter
#include <iostream>
#include <fstream>

bool find_Word(const std::string& target, const std::string &word_to_find) {
    size_t found = target.find(word_to_find);
    if (found == std::string::npos)
        return false;
    else
        return true;
}
int main() {
    std::string user_word{};
    std::string file_word{};
    int word_count{0};
    int words_searched{ 0 };
    std::ifstream in_file;
    in_file.open("romeoandjuliet.txt");
    if (!in_file) {
        std::cerr << "Error opening file" << std::endl;
    }
    std::cout << "Enter the word to be searched in Romeo and Juliet: ";
    std::cin >> user_word;
    while (in_file >> file_word) {
        words_searched++;
        if (find_Word(file_word,user_word)) {
            word_count++;
           
        }
    }
    std::cout << "\n" << "Total words searched " << words_searched;
    std::cout <<"\n" << user_word << " found in Romeo and Juliet " << word_count << " times";
    std::cout << std::endl;
    return 0;
}

