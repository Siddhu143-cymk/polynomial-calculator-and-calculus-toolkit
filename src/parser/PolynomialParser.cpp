#include "PolynomialParser.h"
#include "../services/ArithmeticService.h"
#include <stdexcept>
#include <cmath>

Polynomial PolynomialParser::parse(const std::string& expression) {
    if (expression.empty()) {
        throw std::invalid_argument("Cannot parse empty expression");
    }

    Tokenizer tokenizer(expression);
    std::vector<Token> tokens = tokenizer.tokenize();

    if (tokens.empty() || tokens.front().type == PolyTokenType::END) {
        throw std::invalid_argument("Empty token stream");
    }

    size_t index = 0;
    Polynomial result = parseExpression(tokens, index);

    if (index < tokens.size() && tokens[index].type != PolyTokenType::END) {
        throw std::invalid_argument("Unexpected token '" + tokens[index].text + "' at position " +
                                    std::to_string(tokens[index].position));
    }

    return result;
}

// Expression -> Term ( ('+' | '-') Term )*
Polynomial PolynomialParser::parseExpression(const std::vector<Token>& tokens, size_t& index) {
    ParserStack<Polynomial> polyStack;
    ParserStack<PolyTokenType> opStack;

    // Handle initial unary sign if present
    bool isNegative = false;
    if (tokens[index].type == PolyTokenType::PLUS) {
        index++;
    } else if (tokens[index].type == PolyTokenType::MINUS) {
        isNegative = true;
        index++;
    }

    Polynomial firstTerm = parseTerm(tokens, index);
    if (isNegative) {
        ArithmeticService service;
        Polynomial zero;
        firstTerm = service.subtract(zero, firstTerm);
    }
    polyStack.push(firstTerm);

    while (index < tokens.size()) {
        PolyTokenType type = tokens[index].type;
        if (type == PolyTokenType::PLUS || type == PolyTokenType::MINUS) {
            opStack.push(type);
            index++;

            Polynomial nextTerm = parseTerm(tokens, index);
            Polynomial left = polyStack.top();
            polyStack.pop();

            PolyTokenType op = opStack.top();
            opStack.pop();

            ArithmeticService service;
            Polynomial combined;
            if (op == PolyTokenType::PLUS) {
                combined = service.add(left, nextTerm);
            } else {
                combined = service.subtract(left, nextTerm);
            }
            polyStack.push(combined);
        } else {
            break;
        }
    }

    return polyStack.top();
}

// Term -> Factor ( ('*' | implicit) Factor )*
Polynomial PolynomialParser::parseTerm(const std::vector<Token>& tokens, size_t& index) {
    ParserStack<Polynomial> factorStack;
    factorStack.push(parseFactor(tokens, index));

    while (index < tokens.size()) {
        PolyTokenType type = tokens[index].type;
        bool isExplicitStar = (type == PolyTokenType::STAR);

        if (isExplicitStar) {
            index++; // consume '*'
        }

        // Check if next token starts a new factor (implicit multiplication or explicit '*')
        if (isExplicitStar || tokens[index].type == PolyTokenType::VARIABLE ||
            tokens[index].type == PolyTokenType::NUMBER || tokens[index].type == PolyTokenType::LPAREN) {
            Polynomial nextFactor = parseFactor(tokens, index);
            Polynomial left = factorStack.top();
            factorStack.pop();

            ArithmeticService service;
            Polynomial product = service.multiply(left, nextFactor);
            factorStack.push(product);
        } else {
            break;
        }
    }

    return factorStack.top();
}

// Factor -> Base ( '^' Exponent )?
Polynomial PolynomialParser::parseFactor(const std::vector<Token>& tokens, size_t& index) {
    if (index >= tokens.size()) {
        throw std::invalid_argument("Unexpected end of expression");
    }

    const Token& current = tokens[index];
    Polynomial basePoly;

    if (current.type == PolyTokenType::NUMBER) {
        basePoly.addTerm(current.numericValue, 0);
        index++;
    } else if (current.type == PolyTokenType::VARIABLE) {
        basePoly.addTerm(1.0, 1);
        index++;
    } else if (current.type == PolyTokenType::LPAREN) {
        index++; // consume '('
        basePoly = parseExpression(tokens, index);
        if (index >= tokens.size() || tokens[index].type != PolyTokenType::RPAREN) {
            throw std::invalid_argument("Unmatched opening parenthesis '('");
        }
        index++; // consume ')'
    } else {
        throw std::invalid_argument("Unexpected token '" + current.text + "' at position " +
                                    std::to_string(current.position));
    }

    // Check for exponent '^'
    if (index < tokens.size() && tokens[index].type == PolyTokenType::POWER) {
        index++; // consume '^'
        if (index >= tokens.size()) {
            throw std::invalid_argument("Expected exponent after '^'");
        }

        // Exponent can be a number or (number)
        int expVal = 0;
        if (tokens[index].type == PolyTokenType::NUMBER) {
            expVal = static_cast<int>(tokens[index].numericValue);
            if (expVal < 0) {
                throw std::invalid_argument("Polynomial exponents must be non-negative integers");
            }
            index++;
        } else if (tokens[index].type == PolyTokenType::LPAREN) {
            index++;
            if (tokens[index].type != PolyTokenType::NUMBER) {
                throw std::invalid_argument("Invalid exponent in parenthesis");
            }
            expVal = static_cast<int>(tokens[index].numericValue);
            index++;
            if (index >= tokens.size() || tokens[index].type != PolyTokenType::RPAREN) {
                throw std::invalid_argument("Unmatched parenthesis in exponent");
            }
            index++;
        } else {
            throw std::invalid_argument("Exponent must be a non-negative integer");
        }

        // Compute basePoly ^ expVal
        ArithmeticService service;
        Polynomial result;
        result.addTerm(1.0, 0); // 1
        for (int i = 0; i < expVal; ++i) {
            result = service.multiply(result, basePoly);
        }
        basePoly = result;
    }

    return basePoly;
}
