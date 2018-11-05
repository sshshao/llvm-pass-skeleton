#include <iostream>
int main(int argc, char **argv) {
    bool useless_flag = false;
    for (int i = 0 ; i < 500 ; i *= 2) {
        std::cout << "Although end condition seems pretty big, this line won't be printed too many times…" << std::endl;
        if ((i & 0x1) == 0) {
            std::cout << "Now i is an even number!" << std::endl;
            useless_flag = !useless_flag;
        } else {
            std::cout << "Now i is an odd number!" << std::endl;
            std::cout << "let's make this more interesting by introducing another if-else!" << std::endl;
        }
    }
    std::cout << "Finally the useless flag is: " << useless_flag << std::endl;
}