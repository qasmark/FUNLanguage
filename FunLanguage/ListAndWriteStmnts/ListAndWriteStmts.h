#include <iostream>
#include <string>
#include "../include.h"

const std::string SYNTAX_ERROR_READ = "Syntax error: expected 'READ(', line: pos:";

const std::string SYNTAX_ERROR_WRITE = "Syntax error: expected 'WRITE(', line: pos:";
const std::string SYNTAX_ERROR_MISSING_COMMA = "Syntax error: expected ',' after identifier, line: pos:";
const std::string SYNTAX_ERROR_MISSING_QUOTE = "Syntax error: expected closing '\"' for string, line: pos:";
const std::string SYNTAX_ERROR_UNEXPECTED_SYMBOL = "Syntax error: unexpected symbol in identifier, line: pos:";

void PrintSyntaxError(const std::string& errorMessage, size_t position)
{
    std::cout << errorMessage << position << std::endl;
}

void DeleteSpaceAndSemicolon(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    str.erase(std::remove(str.begin(), str.end(), ';'), str.end());
}

bool CheckIdentifier(const std::string& tempStr, size_t index, size_t findSymbol)
{
    if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z') || tempStr[0] == '_'))
    {
        return false;
    }
    return true;
}

bool ParseRead(std::string& str)
{
    size_t index = 0;
    DeleteSpaceAndSemicolon(str);
    if (str.substr(0, READ_TERMINAL.size()) != READ_TERMINAL)
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, 0);
        return false;
    }

    str.erase(0, READ_TERMINAL.size());
    index += READ_TERMINAL.size();

    size_t findSymbol = 0;
    bool firstIdentifier = true;

    while (findSymbol != std::string::npos)
    {
        if (!firstIdentifier)
        {
            if (str.substr(0, 1) != ",")
            {
                PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
                return false;
            }
            str.erase(0, 1);
            index++;
        }

        findSymbol = str.find(",");

        if (findSymbol == std::string::npos)
        {
            if (str == ")")
            {
                PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
                return false;
            }

            findSymbol = str.find(")");

            if (findSymbol == std::string::npos)
            {
                PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
                return false;
            }
            else
            {
                if (!CheckIdentifier(str.substr(0, findSymbol), index, findSymbol)) // ��������� ������������� ������
                {
                    PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
                    return false;
                }

                break;
            }
        }

        std::string tempStr = str.substr(0, findSymbol);

        if (!CheckIdentifier(str.substr(0, findSymbol), index, findSymbol))
        {
            PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
            return false;
        }

        str.erase(0, findSymbol);

        index += findSymbol;

        firstIdentifier = false;
    }

    return true;
}


bool ParseWrite(std::string& str)
{
    size_t index = 0;
    DeleteSpaceAndSemicolon(str);
    if (str.substr(0, WRITE_TERMINAL.size()) != WRITE_TERMINAL)
    {
        PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
        return false;
    }

    str.erase(0, WRITE_TERMINAL.size());
    index += WRITE_TERMINAL.size();

    size_t findSymbol = 0;
    bool firstIdentifier = true;

    while (findSymbol != std::string::npos)
    {
        if (!firstIdentifier)
        {
            if (str.substr(0, 1) != ",")
            {
                PrintSyntaxError(SYNTAX_ERROR_MISSING_COMMA, index + findSymbol);
                return false;
            }
            str.erase(0, 1);
            index++;
        }

        if (str.substr(0, 1) == "\"")
        {
            size_t closingQuote = str.find("\"", 1);
            if (closingQuote == std::string::npos)
            {
                PrintSyntaxError(SYNTAX_ERROR_MISSING_QUOTE, index + findSymbol);
                return false;
            }
            str.erase(0, closingQuote + 1);
            index += closingQuote + 1;
            firstIdentifier = false;
            continue;
        }

        findSymbol = str.find(",");

        if (findSymbol == std::string::npos)
        {
            if (str == ")")
            {
                PrintSyntaxError(SYNTAX_ERROR_MISSING_COMMA, index + findSymbol);
                return false;
            }

            findSymbol = str.find(")");

            if (findSymbol == std::string::npos)
            {
                PrintSyntaxError(SYNTAX_ERROR_MISSING_COMMA, index + findSymbol);
                return false;
            }
            else
            {
                if (!CheckIdentifier(str.substr(0, findSymbol), index, findSymbol))
                {
                    PrintSyntaxError(SYNTAX_ERROR_UNEXPECTED_SYMBOL, index + findSymbol);
                    return false;
                }

                break;
            }
        }

        std::string tempStr = str.substr(0, findSymbol);

        if (!CheckIdentifier(str.substr(0, findSymbol), index, findSymbol))
        {
            PrintSyntaxError(SYNTAX_ERROR_UNEXPECTED_SYMBOL, index + findSymbol);
            return false;
        }

        str.erase(0, findSymbol);

        index += findSymbol;

        firstIdentifier = false;
    }

    return true;
}