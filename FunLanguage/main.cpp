#include <iostream>
#include <fstream>
#include "ReadAndWritAndListStatements.hpp"
int main()
{
	std::string str = "Read(dsddsdds, dsnsdnsdb, _dsdsdssd)";
	std::cout << ParseRead(str);
}
// Visual Studio Community 2022