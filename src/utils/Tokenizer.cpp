#include "Tokenizer.h"
#include <cctype>
#include <stdexcept>
#include <cstdlib>

Tokenizer::Tokenizer(const std::string& expr) : input(expr), cursor(0) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    size_t length = input.length();

    while (cursor < length) {
        char current = input[cursor];

        // Skip whitespace
        if (std::isspace(static_cast<unsigned char>(current))) {
            cursor++;
            continue;
        }

        size_t startPos = cursor;

        if (current == '+') {
            tokens.emplace_back(PolyTokenType::PLUS, "+", 0.0, startPos);
            cursor++;
        } else if (current == '-') {
            tokens.emplace_back(PolyTokenType::MINUS, "-", 0.0, startPos);
            cursor++;
        } else if (current == '*') {
            tokens.emplace_back(PolyTokenType::STAR, "*", 0.0, startPos);
            cursor++;
        } else if (current == '^') {
            tokens.emplace_back(PolyTokenType::POWER, "^", 0.0, startPos);
            cursor++;
        } else if (current == '(') {
            tokens.emplace_back(PolyTokenType::LPAREN, "(", 0.0, startPos);
            cursor++;
        } else if (current == ')') {
            tokens.emplace_back(PolyTokenType::RPAREN, ")", 0.0, startPos);
            cursor++;
        } else if (current == 'x' || current == 'X') {
            tokens.emplace_back(PolyTokenType::VARIABLE, std::string(1, current), 0.0, startPos);
            cursor++;
        } else if (std::isdigit(static_cast<unsigned char>(current)) || current == '.') {
            // Read number
            size_t numStart = cursor;
            bool decimalSeen = false;
            while (cursor < length &&
                  (std::isdigit(static_cast<unsigned char>(input[cursor])) || (!decimalSeen && input[cursor] == '.'))) {
                if (input[cursor] == '.') decimalSeen = true;
                cursor++;
            }
            std::string numStr = input.substr(numStart, cursor - numStart);
            double val = std::stod(numStr);
            tokens.emplace_back(PolyTokenType::NUMBER, numStr, val, numStart);
        } else {
            std::string errStr = "Unexpected character '";
            errStr += current;
            errStr += "' at position " + std::to_string(startPos);
            throw std::invalid_argument(errStr);
        }
    }

    tokens.emplace_back(PolyTokenType::END, "", 0.0, cursor);
    return tokens;
}
