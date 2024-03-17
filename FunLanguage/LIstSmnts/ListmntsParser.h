#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../include.h"




bool ParseSt(std::string& str);

void LogError(std::string errorTerminal, int line)
{
    std::cout << "Syntax Error: Expected: " + errorTerminal + ", line pos: " + std::to_string(line) << std::endl;
}

bool ParseAssigment(std::string& str)
{
    int null = 0;
    if (!ParseIdentifier(str, null))
    {
        return false;
    }

    if (str.substr(0, ASSIGNMENT_TERMINAL.length()) != ASSIGNMENT_TERMINAL)
    {
        LogError(ASSIGNMENT_TERMINAL, 0);
        return false;
    }
    str.erase(0, ASSIGNMENT_TERMINAL.length());

    if (!RuleExpr(str))
    {
        return false;
    }

    return true;
}

bool ParseListstmnts(std::string& str)
{
    DeleteSpaces(str);

    if (!ParseSt(str))
    {
        LogError(LISTSTMNTS_NAME, 0);
        return false;
    }

    if (str.substr(0, END_PROGRAM_TERMINAL.length()) != END_PROGRAM_TERMINAL)
    {
        str.erase(0, END_PROGRAM_TERMINAL.length());
        if (!ParseListstmnts(str))
        {
            return false;
        }
    }

    return true;
}

bool ParseAssigment(std::string& str)
{
    int null = 0;
    if (!ParseIdentifier(str, null))
    {
        return false;
    }

    null = 0;

    if (str.substr(0, ASSIGNMENT_TERMINAL.length()) != ASSIGNMENT_TERMINAL)
    {
        LogError(ASSIGNMENT_TERMINAL, 0);
        return false;
    }
    str.erase(0, ASSIGNMENT_TERMINAL.length());

    if (!RuleExpr(str))
    {
        return false;
    }

    return true;
}

bool ParseEmpty(std::string& str)
{
    if (str.substr(0, EMPTY_TERMINAL.length()) != EMPTY_TERMINAL)
    {
        LogError(EMPTY_TERMINAL, 0);
        return false;
    }
    str.erase(0, EMPTY_TERMINAL.length());

    return true;
}

bool ParseIf(std::string& str)
{
    if (str.substr(0, IF_TERMINAL.length()) != IF_TERMINAL)
    {
        LogError(IF_TERMINAL, 0);
        return false;
    }
    str.erase(0, IF_TERMINAL.length());

    if (!RuleExpr(str))
    {
        return false;
    }

    if (str.substr(0, THEN_TERMINAL.length()) != THEN_TERMINAL)
    {
        LogError(THEN_TERMINAL, 0);
        return false;
    }
    str.erase(0, THEN_TERMINAL.length());

    if (!ParseSt(str))
    {
        return false;
    }

    if (str.substr(0, ELSE_TERMINAL.length()) == ELSE_TERMINAL)
    {
        str.erase(0, ELSE_TERMINAL.length());
        if (!ParseSt(str))
        {
            return false;
        }
    }
    else
    {
        if (str.substr(0, END_IF_TERMINAL.length()) != END_IF_TERMINAL)
        {
            LogError(ELSE_TERMINAL, 0);
            return false;
        }
    }

    if (str.substr(0, END_IF_TERMINAL.length()) != END_IF_TERMINAL)
    {
        LogError(END_IF_TERMINAL, 0);
        return false;
    }
    str.erase(0, END_IF_TERMINAL.length());

    return true;
}

bool IsListstmnts(std::string str)
{
    if (str.substr(0, BEGIN_LISTSTMNTS_TERMINAL.length()) != BEGIN_LISTSTMNTS_TERMINAL)
    {
        return false;
    }
    str.erase(0, BEGIN_LISTSTMNTS_TERMINAL.length());

    if (!ParseListstmnts)
    {
        return false;
    }

    if (str.substr(0, END_LISTSTMNTS_TERMINAL.length()) != END_LISTSTMNTS_TERMINAL)
    {
        return false;
    }
    str.erase(0, END_LISTSTMNTS_TERMINAL.length());

    return true;
}

bool ParseSt(std::string& str)
{
    if (!ParseAssigment(str) || !ParseIf(str) || !ParseWhile(str) || !ParseFor(str) ||
        !ParseRead(str) || !ParseWrite(str) || !ParseEmpty(str) || !IsListstmnts(str))
    {
        LogError(ST_NAME, 0);
        return false;
    }

    return true;
}

