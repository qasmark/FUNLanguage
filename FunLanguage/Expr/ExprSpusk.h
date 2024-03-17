#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <regex>
#include "../include.h"


const std::string SYNTAX_ERROR_F = "Syntax error: expected factor, line: pos:";
const std::string SYNTAX_ERROR_MUL = "Syntax error: expected multiplicative operator, line: pos:";
const std::string SYNTAX_ERROR_PLUS = "Syntax error: expected additive operator, line: pos:";
const std::string SYNTAX_ERROR_RELATION = "Syntax error: expected relation operator, line: pos:";
const std::string SYNTAX_ERROR_CLOSE_BRACKET = "Syntax error: expected close bracket, line: pos:";


std::string errorMessage;

bool Error(const std::string& message) {
    errorMessage = message;
    return false;
}

std::vector<std::string> ParseString(std::string code) {
    std::string delimiters = " ,;:()";
    size_t pos = 0;
    std::string token;
    std::vector<std::string> tokens;

    // Замена символов новой строки и табуляции на пробелы
    std::replace(code.begin(), code.end(), '\n', ' ');
    std::replace(code.begin(), code.end(), '\t', ' ');

    // Удаление лишних пробелов
    code = std::regex_replace(code, std::regex(" +"), " ");

    while (!code.empty()) {
        if (code[0] == '\"') {
            pos = code.find_first_of('\"', 1);
            token = "\"" + code.substr(1, pos - 1) + "\"";
            code.erase(0, pos + 1);
        }
        else {
            pos = code.find_first_of(delimiters);
            token = code.substr(0, pos);
            if (pos != std::string::npos) {
                code.erase(0, pos);
            }
            else {
                code.clear(); // если разделитель не найден, очистить строку
            }
        }

        if (!token.empty()) {
            tokens.push_back(token);
        }

        // Добавление двоеточия, запятой, точки с запятой или скобок в токены
        if (!code.empty() && (code[0] == ':' || code[0] == ',' || code[0] == ';' || code[0] == '(' || code[0] == ')')) {
            tokens.push_back(std::string(1, code[0]));
            code.erase(0, 1);
        }

        // Пропускаем пробелы после разделителей
        if (!code.empty() && code[0] == ' ') {
            code.erase(0, 1);
        }
    }

    return tokens;
}

bool RuleF(std::vector<std::string>& input, std::size_t& pos);
bool RuleFPrime(std::vector<std::string>& input, std::size_t& pos);
bool RuleMul(std::vector<std::string>& input, std::size_t& pos);
bool RuleTermPrime(std::vector<std::string>& input, std::size_t& pos);
bool RuleTerm(std::vector<std::string>& input, std::size_t& pos);
bool RulePlus(std::vector<std::string>& input, std::size_t& pos);
bool RuleSimpleExprPrime(std::vector<std::string>& input, std::size_t& pos);
bool RuleSimpleExpr(std::vector<std::string>& input, std::size_t& pos);
bool RuleRelation(std::vector<std::string>& input, std::size_t& pos);
bool RuleExprPrime(std::vector<std::string>& input, std::size_t& pos);
bool RuleExpr(std::string& input);

// <expr>::= <simple expr> <expr'>
bool RuleExpr(std::string& input) {
    std::size_t pos = 0;

    std::vector<std::string> tokens = ParseString(input);

    if (RuleSimpleExpr(tokens, pos) && pos == tokens.size()) {
        return RuleExprPrime(tokens, pos);
    }
    if (!errorMessage.empty()) {
        std::cout << errorMessage << std::endl;
        errorMessage.clear();
    }
    return false;
}

// <expr'>::= <relation> <simple expr> <expr'> | ε
bool RuleExprPrime(std::vector<std::string>& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RuleRelation(input, pos) && RuleSimpleExpr(input, pos) && RuleExprPrime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <relation>::= = | <> | > | < | >= | <=
bool RuleRelation(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return false;
    if (RelationValues.count(input[pos])) {
        pos++;
        return true;
    }
    return Error(SYNTAX_ERROR_RELATION);
}

// <simple expr>::= <term> <simple expr'>
bool RuleSimpleExpr(std::vector<std::string>& input, std::size_t& pos) {
    if (RuleTerm(input, pos)) {
        return RuleSimpleExprPrime(input, pos);
    }
    return false;
}

// <simple expr'>::= <plus> <term> <simple expr'> | ε
bool RuleSimpleExprPrime(std::vector<std::string>& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RulePlus(input, pos) && RuleTerm(input, pos) && RuleSimpleExprPrime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <plus>::= + | or
bool RulePlus(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return false;
    if (PlusValues.count(input[pos])) {
        pos++;
        return true;
    }
    return Error(SYNTAX_ERROR_PLUS);
}

// <term>::= <f> <term'>
bool RuleTerm(std::vector<std::string>& input, std::size_t& pos) {
    if (RuleF(input, pos)) {
        return RuleTermPrime(input, pos);
    }
    return false;
}

// <term'>::= <mul> <f> <term'> | ε
bool RuleTermPrime(std::vector<std::string>& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RuleMul(input, pos) && RuleF(input, pos) && RuleTermPrime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <mul>::= * | / | and | div | mod
bool RuleMul(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return false;
    if (MulValues.count(input[pos])) {
        pos++;
        return true;
    }
    return Error(SYNTAX_ERROR_MUL);
}

// <f>::= -<f'> | not <f'> | <f'>
bool RuleF(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return Error(SYNTAX_ERROR_F);
    if (input[pos] == "-") {
        pos++;
        return RuleFPrime(input, pos);
    }
    else if (input[pos] == "not") {
        pos++;
        return RuleFPrime(input, pos);
    }
    return RuleFPrime(input, pos);
}

// <f'> ::= <ident> | <numb> | (<simple expr>)
bool RuleFPrime(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return Error(SYNTAX_ERROR_F);
    if (input[pos] == "id") {
        pos++;
        return true;
    }
    else if (isdigit(input[pos][0])) {
        pos++;
        return true;
    }
    else if (input[pos] == "(") {
        pos++;
        if (pos >= input.size())
            return Error(SYNTAX_ERROR_F);
        if (RuleSimpleExpr(input, pos)) {
            if (pos >= input.size()) {
                return Error(SYNTAX_ERROR_CLOSE_BRACKET);
            }
            if (input[pos] == ")") {
                pos++;
                return true;
            }
            return Error(SYNTAX_ERROR_CLOSE_BRACKET);
        }
        return Error(SYNTAX_ERROR_F);
    }
    return Error(SYNTAX_ERROR_F);
}
