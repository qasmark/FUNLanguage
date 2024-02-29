#pragma once
#include <iostream>
#include <vector>

const std::string FOR_TERMINAL = "FOR";
const std::string ASSIGNMENT_TERMINAL = ":=";
const std::string TO_TERMINAL = "TO";
const std::string DO_TERMINAL = "DO";
const std::string ENDFOR_TERMINAL = "ENDFOR";

void DeleteSpaces(std::string& line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
}

bool ParseFOR(std::vector<std::string>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		DeleteSpaces(vec[i]);
	}

	if (vec[0] != FOR_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + FOR_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	
	if (!ParseIdent(vec[1]))
	{
		std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (vec[2] != ASSIGNMENT_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + ASSIGNMENT_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (!ParseSimpleExpr(vec[3]))
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (vec[4] != TO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + TO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (!ParseSimpleExpr(vec[5]))
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (vec[6] != DO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + DO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (!ParseSt(vec[7]))
	{
		std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (vec[7] != ENDFOR_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + ENDFOR_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	return true;
}