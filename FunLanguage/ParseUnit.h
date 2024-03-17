#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <regex>
#include "include.h"

#include "ForParser/ForParser.h"
#include "ListAndWriteStmnts/ListAndWriteStmts.h"


std::vector<std::string> ParseString(std::string fileName)
{
    std::ifstream fileInput(fileName);

    std::vector<std::string> tokens;
    std::string str;
    while (getline(fileInput, str))
    {
        std::replace(str.begin(), str.end(), '\t', ' ');
        std::replace(str.begin(), str.end(), '\n', ' ');
        tokens.push_back(str);
    }
    return tokens;
}

//std::vector<std::string> ParseString(std::string code) {
//    std::map<std::string, int> varMap;
//    int varCount = 1;
//    std::string delimiters = " \n\t,;:";
//    size_t pos = 0;
//    std::string token;
//    std::vector<std::string> tokens;
//    bool isConstOrVarBlock = false;
//
//    // Удаление лишних пробелов, \n и \t
//    code = std::regex_replace(code, std::regex(" +"), " ");
//    std::replace(code.begin(), code.end(), '\n', ' ');
//    std::replace(code.begin(), code.end(), '\t', ' ');
//
//    while ((pos = code.find_first_of(delimiters)) != std::string::npos) {
//        token = code.substr(0, pos);
//        if (!token.empty()) {
//            if (token == "CONST" || token == "VAR") {
//                isConstOrVarBlock = true;
//            }
//            else if (token == "NOC" || token == "RAV") {
//                isConstOrVarBlock = false;
//            }
//            else if (isConstOrVarBlock) {
//                size_t nextPos = pos;
//                while (code[nextPos] == ' ' && nextPos < code.size()) {
//                    ++nextPos;
//                }
//                if (code[nextPos] == ':' || code[nextPos] == ',') {
//                    varMap[token] = varCount++;
//                }
//            }
//
//            if (varMap.find(token) != varMap.end()) {
//                tokens.push_back("[" + std::to_string(varMap[token]) + "]");
//            }
//            else {
//                tokens.push_back(token);
//            }
//        }
//        if (code[pos] == ':' || code[pos] == ',' || code[pos] == ';') {
//            tokens.push_back(std::string(1, code[pos]));
//        }
//        code.erase(0, pos + 1);
//    }
//
//    if (!code.empty()) {
//        if (varMap.find(code) != varMap.end()) {
//            tokens.push_back("[" + std::to_string(varMap[code]) + "]");
//        }
//        else {
//            tokens.push_back(code);
//        }
//    }
//
//    //std::cout << "Variable Map:\n";
//    //for (const auto& pair : varMap) {
//    //    std::cout << pair.first << ": " << pair.second << "\n";
//    //}
//    //std::cout << std::endl;
//
//    return tokens;
//}

bool syntaxAnalyzer(const std::vector<std::string>& tokens) {
    std::vector<std::string> controlKeywords = { "FUN", "MAIN", "CONST", "NOC", "VAR", "RAV", "BEGIN", "END", "IF", "THEN", "ELSE", "ENDIF", "FOR", "TO", "DO", "ENDFOR", "WRITE", "READ", "WHILE"};
    std::vector<std::string> controlOperators = { "=", "+", "-", "*", "/", ":=" };

    int ifCount = 0;
    int forCount = 0;
    std::vector<std::string> stack;

    for (size_t i = 0; i < tokens.size(); ++i) {
        auto token = tokens[i];

       
        bool findControleKeyWord = false;
        for (auto& word : controlKeywords)
        {
            if (token.find(word) != std::string::npos )
            {
                if (word == "FOR")
                {
                    std::string forStr = "";
                    bool findEndFor = false;
                    for (size_t l = i; l < tokens.size(); l++)
                    {
                        if (tokens[l].find("ENDFOR") != std::string::npos) 
                        {
                            findEndFor = true;
                            for (size_t k = i; k < l; k++)
                            {
                                forStr += tokens[k];
                            }
                            break;
                        }
                    }
                    if (!findEndFor)
                    {
                        std::cout << "Not found ENDFOR" << std::endl;
                        return false;
                    }
                    if (!ParseFor(forStr))
                    {
                        return false;
                    }
                }

                if (word == "READ")
                {
                    if (!ParseRead(token))
                    {
                        return false;
                    }
                }

                if (word == "WRITE")
                {
                    if (!ParseWrite(token))
                    {
                        return false;
                    }
                }

                if (word == "IF")
                {
                    if (!ParseIf(token))
                    {
                        return false;
                    }
                }

                findControleKeyWord = true;
                break;
            }


        }

       /* if (std::find(controlKeywords.begin(), controlKeywords.end(), token) != controlKeywords.end()) {
            if (token.find("IF") != std::string::npos) {
                ifCount++;
                stack.push_back("IF");
            }
            else if (token.find("ELSE") != std::string::npos) {
                if (!stack.empty() && stack.back() == "IF") {
                    stack.pop_back();
                    stack.push_back("ELSE");
                }
                else {
                    std::cerr << "Error: ELSE without IF\n";
                    return false;
                }
            }
            else if (token.find("THEN") != std::string::npos && stack.back() != "IF")
            {
                std::cerr << "Error: THEN without IF\n";
            }
            else if (token.find("FOR") != std::string::npos) {
                if (!ParseFor(token))
                {
                    return false;
                }
                forCount++;
                stack.push_back("FOR");
            }
            else if (token.find("ENDIF") != std::string::npos) {
                if (!stack.empty() && (stack.back() == "IF" || stack.back() == "ELSE")) {
                    stack.pop_back();
                }
                else {
                    std::cerr << "Error: Misplaced ENDIF\n";
                    return false;
                }
            }
            else if (token.find("ENDFOR") != std::string::npos) {
                if (!stack.empty() && stack.back() == "FOR") {
                    stack.pop_back();
                }
                else {
                    std::cerr << "Error: Misplaced ENDFOR\n";
                    return false;
                }
            }
        }
        else if (std::find(controlOperators.begin(), controlOperators.end(), token) != controlOperators.end()) {
        }
        else if (token.find("READ") != std::string::npos) {
            if (!ParseRead(token))
            {
                return false;
            }
        }
        else if (token.find("WRITE") != std::string::npos) {
            if (!ParseWrite(token))
            {
                return false;
            }
        }*/
    }

    if (!stack.empty()) {
        std::cerr << "Error: Missing END for IF or FOR\n";
        return false;
    }

    return true;
}

bool semanticAnalyzer(const std::vector<std::string>& tokens) {
    std::map<std::string, std::string> variables;
    std::string currentDataType;

    bool inConstBlock = false;
    bool inVarBlock = false;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        if (token == "FUN") {
        }
        else if (token == "MAIN") {
        }
        else if (token == "CONST") {
            inConstBlock = true;
            inVarBlock = false;
        }
        else if (token == "VAR") {
            inConstBlock = false;
            inVarBlock = true;
        }
        else if (inConstBlock || inVarBlock) {
            if (token == ":") {
                if (i + 2 < tokens.size()) {
                    variables[tokens[i - 1]] = tokens[i + 1];
                    currentDataType = tokens[i + 1];
                    i += 2;
                }
                else {
                    std::cerr << "Error at index " << i << ": Invalid variable declaration\n";
                    return false;
                }
            }
            else if (token == "=" && inConstBlock) {
                std::cerr << "Error at index " << i << ": Constant cannot be assigned a value\n";
                return false;
            }
        }
        else if (token == "END") {
            if (i + 1 < tokens.size()) {
                if (tokens[i + 1] == "FUN" || tokens[i + 1] == "MAIN") {
                }
                else if (tokens[i + 1] == "IF" || tokens[i + 1] == "ELSE" || tokens[i + 1] == "FOR") {
                }
                else {
                    std::cerr << "Error at index " << i << ": Unexpected END\n";
                    return false;
                }
            }
            else {
                std::cerr << "Error at index " << i << ": Unexpected END\n";
                return false;
            }
        }
        else if (token == "READ") {
            if (i + 2 < tokens.size() && tokens[i + 1] == "(" && tokens[i + 3] == ")") {
                i += 3;
            }
            else {
                std::cerr << "Error at index " << i << ": Invalid READ syntax\n";
                return false;
            }
        }
        else if (token == "WRITE") {
            if (i + 2 < tokens.size() && tokens[i + 1] == "(" && tokens[i + 3] == ")") {
                i += 3;
            }
            else {
                std::cerr << "Error at index " << i << ": Invalid WRITE syntax\n";
                return false;
            }
        }
    }

    return true;
}


struct ASTNode {
    std::string type;
    std::vector<ASTNode*> children;

    ASTNode(const std::string& t) : type(t) {}
    ~ASTNode() {
        for (auto& child : children) {
            delete child;
        }
    }
};

// TODO: complete all tokens to builing in AST
ASTNode* buildAST(const std::vector<std::string>& tokens) {
    ASTNode* root = new ASTNode("Program");
    ASTNode* currentFunctionNode = nullptr;
    ASTNode* currentDeclarationNode = nullptr;

    std::vector<std::string> controlKeywords = { "FUN", "MAIN", "CONST", "NOC", "VAR", "RAV", "BEGIN", "END", "IF", "THEN", "ELSE", "ENDIF", "FOR", "TO", "DO", "ENDFOR" };
    std::vector<std::string> controlOperators = { "=", "+", "-", "*", "/", ":=" };

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        if (std::find(controlKeywords.begin(), controlKeywords.end(), token) != controlKeywords.end()) {
            if (token == "FUN") {
                currentFunctionNode = new ASTNode("Function: MAIN");
                root->children.push_back(currentFunctionNode);
            }
            else if (token == "CONST") {
                currentDeclarationNode = new ASTNode("Declaration: CONST");
                currentFunctionNode->children.push_back(currentDeclarationNode);
            }
            else if (token == "VAR") {
                currentDeclarationNode = new ASTNode("Declaration: VAR");
                currentFunctionNode->children.push_back(currentDeclarationNode);
            }
        }
        else if (std::find(controlOperators.begin(), controlOperators.end(), token) != controlOperators.end()) {
            continue;
        }
        else {
            ASTNode* newNode = new ASTNode("Ident: " + token);
            if (currentDeclarationNode) {
                currentDeclarationNode->children.push_back(newNode);
            }
            else if (currentFunctionNode) {
                currentFunctionNode->children.push_back(newNode);
            }
            else {
                root->children.push_back(newNode);
            }
        }
    }

    return root;
}



void printAST(ASTNode* node, std::stringstream& ss, int depth = 0) {
    for (int i = 0; i < depth; ++i) {
        ss << "|   ";
    }
    ss << "|-- " << node->type << "\n";

    for (auto child : node->children) {
        printAST(child, ss, depth + 1);
    }
}


void deleteAST(ASTNode* node) {
    if (!node) {
        return;
    }

    while (!node->children.empty()) {
        deleteAST(node->children.back());
        node->children.pop_back();
    }

    delete node;
}

void generateIntermediateCode(ASTNode* node, std::stringstream& output) {
    if (!node) {
        return;
    }
    // TODO: complete all tokens in intermediateCode
    if (node->type == "Program") {
        output << "Program Start\n";
    }
    else if (node->type.find("Function:") != std::string::npos) {
        output << "Function: " << node->type.substr(10) << "\n";
    }
    else if (node->type.find("Declaration:") != std::string::npos) {
        output << "Declaration: " << node->type.substr(13) << "\n";
    }
    else if (node->type.find("Unknown:") != std::string::npos) {
        output << "Unknown Token: " << node->type.substr(8) << "\n";
    }

    for (auto child : node->children) {
        generateIntermediateCode(child, output);
    }
}




    