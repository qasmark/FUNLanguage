#pragma once
#include "../include.h"

#include "Dcls/Dcls.h"
#include "Expr/ExprSpusk.h"
#include "LIstSmnts/ListmntsParser.h"

bool ParseFor(std::string& str)
{
	size_t index = 0;
	int zero = 0;
	std::string tempStr;
	DeleteSpaces(str);

	if (str.substr(0, 3) != FOR_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + FOR_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	index += 3;

	size_t positionAssigment = str.find(":=");
	if (positionAssigment == std::string::npos)
	{
		//дописать вывод ошибки
		return false;
	}
	tempStr = str.substr(index, positionAssigment - index);
	if (!ParseIdentifier(tempStr, zero))
	{
		std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
		return false;
	}

	index += positionAssigment;
	zero = 0;

	if (str.substr(index, 2) != ASSIGNMENT_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + ASSIGNMENT_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}

	index += 5;

	positionAssigment = str.find("TO");
	if (positionAssigment == std::string::npos)
	{
		//дописать вывод ошибки
		return false;
	}
	tempStr = str.substr(index, positionAssigment - index);
	if (!RuleExpr(tempStr)) // потом должны передлать чтобы принимало строку
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}

	index += positionAssigment;
	zero = 0;

	if (str.substr(index, 2) != TO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + TO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	index += 2;

	positionAssigment = str.find("DO");
	if (positionAssigment == std::string::npos)
	{
		//дописать вывод ошибки
		return false;
	}

	tempStr = str.substr(index, positionAssigment - index);
	if (!RuleExpr(tempStr))
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}

	index += positionAssigment;
	zero = 0;

	if (str.substr(0, 2) != DO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + DO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	str.erase(0, 2);
	index += 2;

	tempStr = str.substr(index);
	if (!ParseSt(tempStr))
	{
		std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
		return false;
	}
	return true;
}