#include <iostream>
#include <string>

bool ParseRead(std::string& str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	if (str.substr(0, 5) != "Read(")
	{
		return false;
	}

	str.erase(0, 5);
	size_t findSymbol = str.find(",");

	if (findSymbol == std::string::npos)
	{
		return false;
	}

	std::string tempStr = str.substr(0, findSymbol);

	if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
	{
		return false;
	}

	str.erase(0, findSymbol + 1);
	findSymbol = str.find(")");

	if (findSymbol == std::string::npos)
	{
		return false;
	}

	tempStr = str.substr(0, findSymbol);

	if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
	{
		return false;
	}

	return true;
}

bool Write(std::string& str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	if (str.substr(0, 5) != "Write(")
	{
		return false;
	}

	str.erase(0, 6);
	size_t findSymbol = str.find(",");

	if (findSymbol == std::string::npos)
	{
		return false;
	}

	std::string tempStr = str.substr(0, findSymbol);

	if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
	{
		return false;
	}

	str.erase(0, findSymbol + 1);
	findSymbol = str.find(")");

	if (findSymbol == std::string::npos)
	{
		return false;
	}

	tempStr = str.substr(0, findSymbol);

	if (!((tempStr[0] >= 'A' && tempStr[0] <= 'Z') || (tempStr[0] >= 'a' && tempStr[0] <= 'z')))
	{
		return false;
	}

	return true;
}

void ListStatements()
{
	// return State || ListStatements()
}