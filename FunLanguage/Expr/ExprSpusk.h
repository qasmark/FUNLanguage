#pragma once
#include <iostream>
#include <vector>

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
bool RuleExpr(std::vector<std::string>& input, std::size_t& pos);

// <expr>::= <simple expr> <expr'>
bool RuleExpr(std::vector<std::string>& input, std::size_t& pos) {
    if (RuleSimpleExpr(input, pos)) {
        return RuleExprPrime(input, pos);
    }
    return false;
}

// <expr'>::= <relation> <simple expr> <expr'> | ε
bool RuleExprPrime(std::vector<std::string>& input, std::size_t& pos) {
    if (RuleRelation(input, pos) && RuleSimpleExpr(input, pos) && RuleExprPrime(input, pos)) {
        return true;
    }
    return true;
}

// <relation>::= = | <> | > | < | >= | <=
bool RuleRelation(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return false;
    if (input[pos] == "=" || input[pos] == "<>" || input[pos] == ">" || input[pos] == "<" || input[pos] == ">=" || input[pos] == "<=") {
        pos++;
        return true;
    }
    return false;
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
    if (RulePlus(input, pos) && RuleTerm(input, pos) && RuleSimpleExprPrime(input, pos)) {
        return true;
    }
    return true;
}

// <plus>::= + | or
bool RulePlus(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return false;
    if (input[pos] == "+" ||/* input[pos] == "-" ||*/ input[pos] == "or") {
        pos++;
        return true;
    }
    return false;
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
    if (RuleMul(input, pos) && RuleF(input, pos) && RuleTermPrime(input, pos)) {
        return true;
    }
    return true;
}

// <mul>::= * | / | and | div | mod
bool RuleMul(std::vector<std::string>& input, std::size_t& pos) {
    if (pos >= input.size())
        return false;
    if (input[pos] == "*" || input[pos] == "/" || input[pos] == "and" || input[pos] == "div" || input[pos] == "mod") {
        pos++;
        return true;
    }
    return false;
}

// <f>::= -<f'> | not <f'> | <f'>
bool RuleF(std::vector<std::string>& input, std::size_t& pos) {
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
        if (RuleSimpleExpr(input, pos) && input[pos] == ")") {
            pos++;
            return true;
        }
        return false;
    }
    return false;
}