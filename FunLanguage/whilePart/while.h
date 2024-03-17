#pragma once
#include <vector>
#include "../include.h"

bool ParseSt(std::string& str);

bool ParseWhile(std::string& str)
{
    size_t index = 0, tempPosition = 0;
    DeleteSpaces(str);
    std::string tempStr = "";

    if (str.substr(0, 6) != WHILE_START_TERMINAL)
    {
        std::cout << "Syntax error: expected \'" + WHILE_START_TERMINAL + "\', line: pos:" << std::endl; // from lexer
        return false;
    }
    index += 6;
    tempPosition = str.find(DO_TERMINAL);
    if (tempPosition == std::string::npos)
    {
        std::cout << "Syntax error: expected \'" + DO_TERMINAL + "\', line: pos:" << std::endl;
        return false;
    }
    tempStr = str.substr(index, tempPosition);
    if (!RuleExpr(tempStr))
    {
        std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
        return false;
    }
    index = tempPosition;
    tempPosition = str.find(WHILE_END_TERMINAL);
    if (tempPosition == std::string::npos)
    {
        std::cout << "Syntax error: expected \'" + WHILE_END_TERMINAL + "\', line: pos:" << std::endl;
        return false;
    }
    tempStr = str.substr(index, tempPosition);
    if (!ParseSt(tempStr))
    {
        std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
        return false;
    }
    return true;
}