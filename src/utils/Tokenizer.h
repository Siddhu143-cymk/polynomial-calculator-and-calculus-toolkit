#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

enum class PolyTokenType {
    NUMBER,
    VARIABLE, // 'x'
    PLUS,
    MINUS,
    STAR,
    POWER, // '^'
    LPAREN,
    RPAREN,
    END,
    INVALID
};

struct Token {
    PolyTokenType type;
    std::string text;
    double numericValue;
    size_t position;

    Token(PolyTokenType t, const std::string& txt, double val = 0.0, size_t pos = 0)
        : type(t), text(txt), numericValue(val), position(pos) {}
};

class Tokenizer {
private:
    std::string input;
    size_t cursor;

public:
    explicit Tokenizer(const std::string& expr);

    std::vector<Token> tokenize();
};

#endif // TOKENIZER_H
