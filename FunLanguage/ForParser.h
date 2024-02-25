#pragma once
#include <iostream>
#include <sstream>

const std::string FOR_TERMINAL = "FOR";
const std::string ASSIGNMENT_TERMINAL = ":=";
const std::string TO_TERMINAL = "TO";
const std::string DO_TERMINAL = "DO";

void DeleteSpaces(std::string& line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
}

bool ParseFOR(std::stringstream& strm)
{
	std::string line;
	strm >> line;

	DeleteSpaces(line);

	if (line.substr(0, 3) != FOR_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + FOR_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	line.erase(0, 3);
	if (!ParseIdent(line))
	{
		std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (line.substr(0, 2) != ASSIGNMENT_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + ASSIGNMENT_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	line.erase(0, 2);
	if (!ParseSimpleExpr)
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (line.substr(0, 2) != TO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + TO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	line.erase(0, 2);
	if (!ParseSimpleExpr)
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (line.substr(0, 2) != DO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + DO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	line.erase(0, 2);
	if (!ParseSt(line))
	{
		std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
		return false;
	}
	return true;
}