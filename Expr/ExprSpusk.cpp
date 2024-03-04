#include <fstream>
#include <sstream>
#include "ExprSpusk.h"

int main() {
    std::string line;
    //Например: ( id / 3 ) + 2 = 5 * not id
    std::cout << "Enter expression: ";
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::vector<std::string> input = std::vector<std::string>((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    std::size_t pos = 0;

    if (RuleExpr(input, pos) && pos == input.size()) {
        std::cout << "OK\n";
    }
    else {
        std::cout << "ERROR\n";
    }

    return 0;
}
