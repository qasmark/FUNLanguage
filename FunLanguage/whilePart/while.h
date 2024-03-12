#pragma once
#include "iostream"
#include <vector>

const std::string WHILE_START_TERMINAL = "WHILE";
const std::string WHILE_END_TERMINAL = "ENDWHILE";
const std::string EXPRESSION_CLOSE_TERMINAL = ")";

void DeleteSpaces(std::string& line)
{
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
}

bool ParseWhile(std::vector<std::string>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        DeleteSpaces(vec[i]);
    }

    if (vec[0] != WHILE_START_TERMINAL)
    {
        std::cout << "Syntax error: expected \'" + WHILE_START_TERMINAL + "\', line: pos:" << std::endl; // from lexer
        return false;
    }
    if (!ParseExpression(vec[1]))
    {
        std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
        return false;
    }
    if (vec[2] != EXPRESSION_CLOSE_TERMINAL)
    {
        std::cout << "Syntax error: expected \'" + EXPRESSION_CLOSE_TERMINAL + "\', line: pos:" << std::endl; // from lexer
        return false;
    }
    if (!ParseSt(vec[3]))
    {
        std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
        return false;
    }
    if (vec[3] != WHILE_END_TERMINAL)
    {
        std::cout << "Syntax error: expected \'" + WHILE_END_TERMINAL + "\', line: pos:" << std::endl; // from lexer
        return false;
    }
    return true;
}