#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <regex>
#include "ParseUnit.h"
#include <fstream>


int main() 
{
    std::string fileName = "input_code.txt";
    std::vector<std::string> tokens = ParseString(fileName);


    std::cout << "Tokens: ";
    for (const auto& token : tokens) {
        std::cout << token << " ";
    }

    std::cout << "\nSyntax analysis result: ";
    if (syntaxAnalyzer(tokens)) {
        std::cout << "Syntax is correct.\n";
    } else {
        std::cout << "Syntax is incorrect.\n";
    }

    std::cout << "Semantic analysis result: ";
    if (semanticAnalyzer(tokens)) {
        std::cout << "Semantics is correct.\n";
    }
    else {
        std::cout << "Semantics is incorrect.\n";
        return 1;
    }


    ASTNode* root = buildAST(tokens);
    std::stringstream ss;

    printAST(root, ss);

    std::ofstream outfile("out_AST.txt", std::ios::binary);
    outfile.write(ss.str().c_str(), ss.str().size());
    outfile.close();

    std::stringstream intermediateCode;

    generateIntermediateCode(root, intermediateCode);

    std::ofstream outf("out_intermediate_code.txt");
    outf << intermediateCode.str();
    outf.close();

    deleteAST(root);

    return 0;
}
