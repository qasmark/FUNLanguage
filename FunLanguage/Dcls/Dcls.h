#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../include.h"

void DeleteSpaces(const std::string& text, int& i)
{
	while (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
	{
		i++;
	}
}

bool Expect(const std::string& expected, const std::string& text, int& i)
{
	if (text.substr(i, expected.length()) == expected)
	{
		i += int(expected.length());
		return true;
	}
	return false;
}

bool ParseIdentifier(const std::string& text, int& i)
{
	std::string identifier;
	while (isalpha(text[i]))
	{
		identifier += text[i++];
	}
	return true;
}

bool ParseValue(const std::string& text, int& i, const std::string& type);
bool ParseType(const std::string& text, int& i)
{
	std::string type;
	while (isalpha(text[i]))
	{
		type += text[i++];
	}
	DeleteSpaces(text, i);
	if (!Expect("=", text, i))
	{
		return false;
	}
	DeleteSpaces(text, i);
	return ParseValue(text, i, type);
}

bool ParseInt(const std::string& text, int& i)
{
	std::string value;
	while (isdigit(text[i]))
	{
		value += text[i++];
	}
	return true;
}

bool ParseDouble(const std::string& text, int& i)
{
	std::string value;
	while (isdigit(text[i]) || text[i] == '.')
	{
		if (text[i] == '.')
		{
			return ParseInt(text, ++i);
		}
		value += text[i++];
	}
	return true;
}

bool ParseFloat(const std::string& text, int& i)
{
	return ParseDouble(text, i);
}

bool ParseStr(const std::string& text, int& i)
{
	std::string value;
	bool isClose = false;
	while (isalpha(text[i]) || text[i] == '"')
	{
		if (text[i] == '"')
		{
			if (!isClose)
			{
				isClose = true;
			}
			else
			{
				value += text[i++];
				return true;
			}
		}
		value += text[i++];
	}
	return true;
}

bool ParseBool(const std::string& text, int& i)
{
	if (text[i] == 't' && text[i + 1] == 'r' && text[i + 2] == 'r' && text[i + 3] == 'u' && text[i + 4] == 'e')
	{
		i += 4;
		return true;
	}
	if (text[i] == 'f' && text[i + 1] == 'a' && text[i + 2] == 'l' && text[i + 3] == 's' && text[i + 4] == 'e')
	{
		i += 4;
		return true;
	}
	return false;
}

bool ParseChar(const std::string& text, int& i)
{
	if (text[i] != '\'')
	{
		return false;
	}

	i++;
	if (text[i] != '\'')
	{
		i++;
	}

	if (text[i] != '\'')
	{
		return false;
	}

	return true;
}

bool ParseValue(const std::string& text, int& i, const std::string& type)
{
	if (type == INT)
	{
		return ParseInt(text, i);
	}
	if (type == DOUBLE)
	{
		return ParseDouble(text, i);
	}
	if (type == FLOAT)
	{
		return ParseFloat(text, i);
	}
	if (type == STRING)
	{
		return ParseStr(text, i);
	}
	if (type == BOOL)
	{
		return ParseBool(text, i);
	}
	if (type == CHAR)
	{
		return ParseChar(text, i);
	}
	return false;
}

bool ParseNoc(const std::string& text, int& i)
{
	if (text[i] == 'N' && text[i + 1] == 'O' && text[i + 2] == 'C')
	{
		i += 3;
		return true;
	}
	return false;
}

void ParseConstants(const std::string& text, int& i)
{
	DeleteSpaces(text, i);
	Expect("CONST", text, i);
	while (true)
	{
		DeleteSpaces(text, i);
		if (ParseNoc(text, i))
		{
			break;
		}
		if (!ParseIdentifier(text, i))
		{
			return;
		}

		DeleteSpaces(text, i);
		if (!Expect(":", text, i))
		{
			return;
		}

		DeleteSpaces(text, i);
		if (!ParseType(text, i))
		{
			return;
		}

		DeleteSpaces(text, i);
		if (text[i] == ';')
		{
			i++;
			continue;
		}
		DeleteSpaces(text, i);
		if (ParseNoc(text, i))
		{
			break;
		}
	}
}

bool ParseIdentifierList(const std::string& text, int& i)
{
	std::string identifier;
	while (isalpha(text[i]) || text[i] == ',' || text[i] == ' ')
	{
		identifier += text[i++];
	}
	return true;
}

bool ParseRav(const std::string& text, int& i)
{
	if (text[i] == 'R' && text[i + 1] == 'A' && text[i + 2] == 'V')
	{
		i += 3;
		return true;
	}

	return false;
}

void ParseVar(const std::string& text, int& i)
{
	DeleteSpaces(text, i);
	if (!Expect("VAR", text, i))
	{
		return;
	}
	while (true)
	{
		DeleteSpaces(text, i);
		if (ParseRav(text, i))
		{
			break;
		}
		if (!ParseIdentifierList(text, i))
		{
			return;
		}
		DeleteSpaces(text, i);
		if (!Expect(":", text, i))
		{
			return;
		}
		DeleteSpaces(text, i);
		if (!ParseType(text, i))
		{
			return;
		}

		DeleteSpaces(text, i);
		if (text[i] == ';')
		{
			i++;
			continue;
		}

		DeleteSpaces(text, i);
		if (ParseRav(text, i))
		{
			break;
		}
	}
}

bool DCLS(std::ifstream& file)
{
	std::string text, line;
	while (std::getline(file, line))
	{
		text += line + '\n';
	}
	int i = 0;
	DeleteSpaces(text, i);
	if (text[i] == 'C')
	{
		ParseConstants(text, i);
	}
	ParseVar(text, i);
	return true;
}