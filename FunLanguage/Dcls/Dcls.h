#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string INT = "int";
const std::string STRING = "string";
const std::string DOUBLE = "double";
const std::string CHAR = "char";
const std::string BOOL = "bool";
const std::string FLOAT = "float";

const std::string CONST = "const";
const std::string VAR = "var";

void DeleteSpaces(const std::string& text, int& i)
{
	while (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
	{
		i++;
	}
}

void Expect(const std::string& expected, const std::string& text, int& i)
{
	if (text.substr(i, expected.length()) == expected)
	{
		i += expected.length();
	}
	else
	{
		std::cout << "Syntax error: expected '" + expected + "'" << " but " << text.substr(i, expected.length()) << std::endl;
		throw std::runtime_error("Syntax error: expected '" + expected + "'");
	}
}

std::string ParseIdentifier(const std::string& text, int& i)
{
	std::string identifier;
	while (isalpha(text[i]))
	{
		identifier += text[i++];
	}
	std::cout << identifier << std::endl;
	return identifier;
}

std::string ParseType(const std::string& text, int& i)
{
	std::string type;
	while (isalpha(text[i]))
	{
		type += text[i++];
	}
	if (type == INT || type == CHAR || type == STRING || type == DOUBLE || type == FLOAT || type == BOOL)
	{
		return type;
	}
	std::cout << "Syntax error: expected type" << std::endl;
	throw std::runtime_error("Syntax error: expected type");
}

std::string ParseInt(const std::string& text, int& i)
{
	std::string value;
	while (isdigit(text[i]))
	{
		value += text[i++];
	}
	return value;
}

std::string ParseDouble(const std::string& text, int& i)
{
	std::string value;
	while (isdigit(text[i]) || text[i] == '.')
	{
		if (text[i] == '.')
		{
			return value + "." + ParseInt(text, ++i);
		}
		value += text[i++];
	}
	return value;
}

std::string ParseFloat(const std::string& text, int& i)
{
	return ParseDouble(text, i);
}

std::string ParseString(const std::string& text, int& i)
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
				return value;
			}
		}
		value += text[i++];
	}
	return value;
}

std::string ParseBool(const std::string& text, int& i)
{
	if (text[i] == 't' && text[i + 1] == 'r' && text[i + 2] == 'r' && text[i + 3] == 'u' && text[i + 4] == 'e')
	{
		i += 4;
		return "true";
	}
	if (text[i] == 'f' && text[i + 1] == 'a' && text[i + 2] == 'l' && text[i + 3] == 's' && text[i + 4] == 'e')
	{
		i += 4;
		return "false";
	}
	throw std::runtime_error("Syntax error: expected bool type");
}

std::string ParseChar(const std::string& text, int& i)
{
	if (text[i] != '\'')
	{
		throw std::runtime_error("Syntax error: expected char type");
	}

	i++;
	if (text[i] != '\'')
	{
		i++;
	}
	if (text[i] != '\'')
	{
		throw std::runtime_error("Syntax error: expected char type");
	}
}

std::string ParseValue(const std::string& text, int& i, const std::string& type)
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
		return ParseString(text, i);
	}
	if (type == BOOL)
	{
		return ParseBool(text, i);
	}
	if (type == CHAR)
	{
		return ParseChar(text, i);
	}
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
		ParseIdentifier(text, i);

		DeleteSpaces(text, i);
		Expect(":", text, i);

		DeleteSpaces(text, i);
		const std::string type = ParseType(text, i);

		DeleteSpaces(text, i);
		Expect("=", text, i);

		DeleteSpaces(text, i);
		ParseValue(text, i, type);

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

std::string ParseIdentifierList(const std::string& text, int& i)
{
	std::string identifier;
	while (isalpha(text[i]) || text[i] == ',' || text[i] == ' ')
	{
		identifier += text[i++];
	}
	//std::cout << identifier << std::endl;
	return identifier;
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
	Expect("VAR", text, i);
	while (true)
	{
		DeleteSpaces(text, i);
		if (ParseRav(text, i))
		{
			break;
		}
		ParseIdentifierList(text, i);

		DeleteSpaces(text, i);
		Expect(":", text, i);

		DeleteSpaces(text, i);
		const std::string type = ParseType(text, i);

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