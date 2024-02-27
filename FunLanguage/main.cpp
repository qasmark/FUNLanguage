#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <regex>
#include "ParseUnit.h"
#include <fstream>
std::vector<std::string> ParseString(std::string code);
bool syntaxAnalyzer(const std::vector<std::string>& tokens);

int main() 
{
    std::ifstream file("input_code.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    std::vector<std::string> tokens = ParseString(code);


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
