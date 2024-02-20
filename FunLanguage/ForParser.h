#pragma once
#include <iostream>

bool ParseFOR(std::string& line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	if (line.substr(0, 4) != "for(")
	{
		return false;
	}
	line.erase(0, 4);
	if (!ParseIdent(line))
	{
		return false;
	}
	if (line[0] != '=')
	{
		return false;
	}
	line.erase(line.begin());
	if (!ParseValue)
	{
		return false;
	}
	if (line[0] != ';')
	{
		return false;
	}
	line.erase(line.begin());
	if (!ParseIdent(line) || !ParseRelation(line) || !ParseValue(line))
	{
		return false;
	}
	if (line[0] != ';')
	{
		return false;
	}
	if (!ParseIdent(line))
	{
		return false;
	}
	if (line[0] != '=')
	{
		return false;
	}
	if (!ParseIdent(line) || !ParseMul(line) || !ParseValue(line))
	{
		return false;
	}
	if (line[0] != ')')
	{
		return false;
	}
	line.erase(line.begin());
	if (!ParseSt(line))
	{
		return false;
	}
	return true;
}

bool ParseValue(std::string& line)
{
	if (!ParseNumb(line) || !ParseIdent(line))
	{
		return false;
	}
	return true;
}