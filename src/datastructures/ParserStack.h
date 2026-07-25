#ifndef PARSER_STACK_H
#define PARSER_STACK_H

#include <vector>
#include <stdexcept>
#include <cstddef>

/**
 * @brief Custom thin wrapper around a dynamic array/vector for stack operations.
 * Used during polynomial expression parsing.
 */
template <typename T>
class ParserStack {
private:
    std::vector<T> elements;

public:
    ParserStack() = default;

    void push(const T& item) {
        elements.push_back(item);
    }

    void pop() {
        if (elements.empty()) {
            throw std::underflow_error("ParserStack underflow: pop from empty stack");
        }
        elements.pop_back();
    }

    T& top() {
        if (elements.empty()) {
            throw std::underflow_error("ParserStack underflow: top of empty stack");
        }
        return elements.back();
    }

    const T& top() const {
        if (elements.empty()) {
            throw std::underflow_error("ParserStack underflow: top of empty stack");
        }
        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }

    void clear() {
        elements.clear();
    }
};

#endif // PARSER_STACK_H
