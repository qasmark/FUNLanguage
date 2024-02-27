#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

const std::string EMPTY_TERMINAL = ";";
const std::string IF_TERMINAL = "if(";
const std::string THEN_TERMINAL = ")then";
const std::string ELSE_TERMINAL = "else";
const std::string END_IF_TERMINAL = "fi";
const std::string ASSIGMENT_TERMINAL = ":=";
const std::string BEGIN_LISTSTMNTS_TERMINAL = "{";
const std::string END_LISTSTMNTS_TERMINAL = "}";
const std::string END_PROGRAM_TERMINAL = "NUM";

const std::string ST_NAME = "statements";
const std::string LISTSTMNTS_NAME = "list statements";

void DeleteSpaces(std::string& line)
{
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
}

void LogError(std::string errorTerminal, int line)
{
    std::cout << "Syntax Error: Expected: " + errorTerminal + ", line pos: " + std::to_string(line) << std::endl;
}

bool ParseAssigment(std::string& str);
bool ParseListstmnts(std::string& str);
bool ParseSt(std::string& str);

bool ParseIdent(std::string& str)
{
    return true;
}

bool ParseExpr(std::string& str)
{
    return true;
}

bool ParseWhile(std::string& str)
{
    return true;
}

bool ParseFor(std::string& str)
{
    return true;
}

bool ParseRead(std::string& str)
{
    return true;
}

bool ParseWrite(std::string& str)
{
    return true;
}