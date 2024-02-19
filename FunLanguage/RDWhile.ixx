#include <iostream>

export module RDWhile;


bool ParseWhile(std::string& line)
{
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    if (line.substr(0, 6) != "while(")
        return false;
    line.erase(0, 6);
    if (!ParseExpression(line))
        return false;
    if (line[0] != ')')
        return false;
    if (!ParseSt(line))
        return false;

    return true;
}