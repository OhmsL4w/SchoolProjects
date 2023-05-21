#include <string>
class Solution {
public:
    bool isPalindrome(int x) {
        auto s = std::to_string(x);
        char palindrome[10];
        strcpy(palindrome, s.c_str());

        int l{ 0 };
        size_t r{ palindrome.size() - 1 };
        bool istrue{ false };
        while (l != r) {
            if (strcmp(palindrome[l], palindrome){
            return false;
            }
            else {
                istrue = true;
            }
            l++;
            r--;

        }
    }
};