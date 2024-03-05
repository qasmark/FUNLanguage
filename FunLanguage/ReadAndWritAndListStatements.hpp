#include <iostream>
#include <string>

const std::string READ_TERMINAL = "Read(";
const std::string WRITE_TERMINAL = "Write(";
const std::string ASSIGNMENT_TERMINAL = "{";

const std::string SYNTAX_ERROR_READ = "Syntax error: expected 'Read(', line: pos:";
const std::string SYNTAX_ERROR_WRITE = "Syntax error: expected 'Write(', line: pos:";
const std::string SYNTAX_ERROR_ASSIGNMENT = "Syntax error: expected '{', line: pos:";

void PrintSyntaxError(const std::string& errorMessage, size_t position)
{
    std::cout << errorMessage << position << std::endl;
}

void DeleteSpace(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

bool CheckIdentifier(const std::string& tempStr, size_t index, size_t findSymbol)
{
    if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z') || tempStr[0] == '_'))
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
        return false;
    }
}

bool ParseRead(std::string& str)
{
    size_t index = 0;
    DeleteSpace(str);
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

            if (findSymbol != std::string::npos && !firstIdentifier)
            {
                if (!CheckIdentifier(str.substr(0, findSymbol), index, findSymbol)) // последний идентификатор чекаем
                {
                    return false;
                }

                break;
            }
            else
            {
                PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
                return false;
            }
        }

        std::string tempStr = str.substr(0, findSymbol);

        if (!CheckIdentifier(str.substr(0, findSymbol), index, findSymbol)) 
        {
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
    DeleteSpace(str);
    if (str.substr(0, WRITE_TERMINAL.size()) != WRITE_TERMINAL)
    {
        PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
        return false;
    }

    str.erase(0, WRITE_TERMINAL.size() + 1);
    size_t findSymbol = str.find(",");

    if (findSymbol == std::string::npos)
    {
        PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
        return false;
    }

    std::string tempStr = str.substr(0, findSymbol);

    if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
    {
        PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
        return false;
    }

    str.erase(0, findSymbol + 1);
    findSymbol = str.find(")");

    if (findSymbol == std::string::npos)
    {
        PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
        return false;
    }

    tempStr = str.substr(0, findSymbol);

    if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
    {
        PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
        return false;
    }

    return true;
}
