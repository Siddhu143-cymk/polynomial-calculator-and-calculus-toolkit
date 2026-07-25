#ifndef POLYNOMIAL_PARSER_H
#define POLYNOMIAL_PARSER_H

#include "../models/Polynomial.h"
#include "../utils/Tokenizer.h"
#include "../datastructures/ParserStack.h"
#include <string>

/**
 * @brief Expression parser that converts human-readable strings into Polynomial objects.
 * Demonstrates operator precedence stack operations via ParserStack.
 */
class PolynomialParser {
private:
    std::string inputExpr;

    // Helper parsing methods
    Polynomial parseExpression(const std::vector<Token>& tokens, size_t& index);
    Polynomial parseTerm(const std::vector<Token>& tokens, size_t& index);
    Polynomial parseFactor(const std::vector<Token>& tokens, size_t& index);

public:
    PolynomialParser() = default;

    /**
     * @brief Parse input string expression into Polynomial object.
     * @throws std::invalid_argument on syntax or formatting error.
     */
    Polynomial parse(const std::string& expression);
};

#endif // POLYNOMIAL_PARSER_H
