#ifndef TERM_H
#define TERM_H

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Class representing a single term in a polynomial: coeff * x^exp.
 */
class Term {
private:
    double coeff;
    int exp;

public:
    Term();
    Term(double coefficient, int exponent);

    double getCoeff() const;
    int getExponent() const;

    void setCoeff(double c);
    void setExponent(int e);

    /**
     * @brief Evaluates term c * x^e at x.
     */
    double evaluate(double x) const;

    /**
     * @brief Formats term to human-readable string (e.g., "-3x^2", "x", "5").
     */
    std::string toString(bool isLeading = false) const;

    nlohmann::json toJson() const;
};

#endif // TERM_H
