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

bool ParseRead(std::string& str)
{
    DeleteSpace(str);
    if (str.substr(0, READ_TERMINAL.size()) != READ_TERMINAL)
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, 0);
        return false;
    }

    str.erase(0, READ_TERMINAL.size());
    size_t findSymbol = str.find(",");

    if (findSymbol == std::string::npos)
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, 0);
        return false;
    }

    std::string tempStr = str.substr(0, findSymbol);

    if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, 0);
        return false;
    }

    str.erase(0, findSymbol + 1);
    findSymbol = str.find(")");

    if (findSymbol == std::string::npos)
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, 0);
        return false;
    }

    tempStr = str.substr(0, findSymbol);

    if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
    {
        PrintSyntaxError(SYNTAX_ERROR_READ, 0);
        return false;
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

bool ParseSt(std::string& line)
{
    if (line[0] == ASSIGNMENT_TERMINAL[0])
    {
        line.erase(line.begin());
        if (!ParseListStatements(line))
        {
            return false;
        }
        if (line[0] != '}')
        {
            PrintSyntaxError(SYNTAX_ERROR_ASSIGNMENT, 0);
            return false;
        }
        line.erase(line.begin());
        return true;
    }

    return false;
}

bool ParseListStatements(std::string& line)
{
    while (!line.empty() && line[0] != '}')
    {
        if (!ParseSt(line))
        {
            return false;
        }
    }

    return true;
}