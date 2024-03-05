#include <iostream>
#include <fstream>
#include "ReadAndWritAndListStatements.hpp"
int main()
{
	std::string input1 = "Write(variable)";
	std::string input2 = "Write(var1, var2, var3)";
	std::string input3 = "Write(\"Hello, World!\", variable)";
	std::string input4 = "Write( \"Hello, World!\" , variable )";
	std::string input5 = "Write(\"Hello\", \"World\", variable)";
	std::string input6 = "Write(var1, var2, var3,)";
	std::string input7 = "Write(var1, var2, var3";
	std::string input8 = "Write()";
	std::string input9 = "Write(\"\")";
	std::string input10 = "Write(\"Hello, World, variable)";
	std::string input11 = "Write(var1, var2, 1ar3)";
	std::cout << ParseWrite(input11);
}