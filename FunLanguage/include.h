#pragma once
#include <set>
//read&write
const std::string READ_TERMINAL = "READ(";
const std::string WRITE_TERMINAL = "WRITE(";

//dcls
const std::string INT = "int";
const std::string STRING = "string";
const std::string DOUBLE = "double";
const std::string CHAR = "char";
const std::string BOOL = "bool";
const std::string FLOAT = "float";

const std::string CONST = "const";
const std::string VAR = "var";

//exprspusk
std::set<std::string> RelationValues = { "=", "<>", ">", "<", ">=", "<=" };
std::set<std::string> PlusValues = { "+", "or" };
std::set<std::string> MulValues = { "*", "/", "and", "div", "mod" };

//for
const std::string FOR_TERMINAL = "FOR";
const std::string ASSIGNMENT_TERMINAL = ":=";
const std::string TO_TERMINAL = "TO";
const std::string DO_TERMINAL = "DO";


//lstmparse
const std::string EMPTY_TERMINAL = ";";
const std::string IF_TERMINAL = "IF(";
const std::string THEN_TERMINAL = ")THEN";
const std::string ELSE_TERMINAL = "ELSE";
const std::string END_IF_TERMINAL = "FI";
//const std::string ASSIGMENT_TERMINAL = ":=";
const std::string BEGIN_LISTSTMNTS_TERMINAL = "{";
const std::string END_LISTSTMNTS_TERMINAL = "}";
const std::string END_PROGRAM_TERMINAL = "NUM";

const std::string ST_NAME = "statements";
const std::string LISTSTMNTS_NAME = "list statements";

// while
const std::string WHILE_START_TERMINAL = "WHILE";
//const std::string DO_TERMINAL = "DO";
const std::string WHILE_END_TERMINAL = "ENDWHILE";


void DeleteSpaces(std::string& line)
{
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
}