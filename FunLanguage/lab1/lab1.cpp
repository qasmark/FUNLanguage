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

void deleteSpaces(const std::string& text , int& i)
{
	while (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
	{
		i++;
	}
}

bool expect(const std::string& expected , const std::string& text , int& i)
{
	if (text.substr(i , expected.length()) == expected)
	{
		i += expected.length();
		return true;
	}
	return false;
}

bool parseIdentifier(const std::string& text , int& i)
{
	std::string identifier;
	while (isalpha(text[i]))
	{
		identifier += text[i++];
	}
	return true;
}

bool parseValue(const std::string& text , int& i , const std::string& type);
bool parseType(const std::string& text , int& i)
{
	std::string type;
	while (isalpha(text[i]))
	{
		type += text[i++];
	}
	deleteSpaces(text , i);
	if (!expect("=" , text , i))
	{
		return false;
	}
	deleteSpaces(text , i);
	return parseValue(text , i , type);
}

bool parseInt(const std::string& text , int& i)
{
	std::string value;
	while (isdigit(text[i]))
	{
		value += text[i++];
	}
	return true;
}

bool parseDouble(const std::string& text , int& i)
{
	std::string value;
	while (isdigit(text[i]) || text[i] == '.')
	{
		if (text[i] == '.')
		{
			return parseInt(text , ++i);
		}
		value += text[i++];
	}
	return true;
}

bool parseFloat(const std::string& text , int& i)
{
	return parseDouble(text , i);
}

bool parseString(const std::string& text , int& i)
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

bool parseBool(const std::string& text , int& i)
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

bool parseChar(const std::string& text , int& i)
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

bool parseValue(const std::string& text , int& i , const std::string& type)
{
	if (type == INT)
	{
		return parseInt(text , i);
	}
	if (type == DOUBLE)
	{
		return parseDouble(text , i);
	}
	if (type == FLOAT)
	{
		return parseFloat(text , i);
	}
	if (type == STRING)
	{
		return parseString(text , i);
	}
	if (type == BOOL)
	{
		return parseBool(text , i);
	}
	if (type == CHAR)
	{
		return parseChar(text , i);
	}
	return false;
}

bool parseNoc(const std::string& text , int& i)
{
	if (text[i] == 'N' && text[i + 1] == 'O' && text[i + 2] == 'C')
	{
		i += 3;
		return true;
	}
	return false;
}

void parseConstants(const std::string& text , int& i)
{
	deleteSpaces(text , i);
	expect("CONST" , text , i);
	while (true)
	{
		deleteSpaces(text , i);
		if (parseNoc(text , i))
		{
			break;
		}
		if (!parseIdentifier(text , i))
		{
			return;
		}

		deleteSpaces(text , i);
		if (!expect(":" , text , i))
		{
			return;
		}

		deleteSpaces(text , i);
		if (!parseType(text , i))
		{
			return;
		}

		deleteSpaces(text , i);
		if (text[i] == ';')
		{
			i++;
			continue;
		}
		deleteSpaces(text , i);
		if (parseNoc(text , i))
		{
			break;
		}
	}
}

bool parseIdentifierList(const std::string& text , int& i)
{
	std::string identifier;
	while (isalpha(text[i]) || text[i] == ',' || text[i] == ' ')
	{
		identifier += text[i++];
	}
	return true;
}

bool parseRav(const std::string& text , int& i)
{
	if (text[i] == 'R' && text[i + 1] == 'A' && text[i + 2] == 'V')
	{
		i += 3;
		return true;
	}

	return false;
}

void parseVar(const std::string& text , int& i)
{
	deleteSpaces(text , i);
	if (!expect("VAR" , text , i))
	{
		return;
	}
	while (true)
	{
		deleteSpaces(text , i);
		if (parseRav(text , i))
		{
			break;
		}
		if (!parseIdentifierList(text , i))
		{
			return;
		}
		deleteSpaces(text , i);
		if (!expect(":" , text , i))
		{
			return;
		}
		deleteSpaces(text , i);
		if (!parseType(text , i))
		{
			return;
		}

		deleteSpaces(text , i);
		if (text[i] == ';')
		{
			i++;
			continue;
		}

		deleteSpaces(text , i);
		if (parseRav(text , i))
		{
			break;
		}
	}
}

bool DCLS(std::ifstream& file)
{
	std::string text , line;
	while (std::getline(file , line))
	{
		text += line + '\n';
	}
	int i = 0;
	deleteSpaces(text , i);
	if (text[i] == 'C')
	{
		parseConstants(text , i);
	}
	parseVar(text , i);
	return true;
}

int main()
{
	std::string fileName;
	std::cin >> fileName;

	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return 1;
	}

	DCLS(file);

}
