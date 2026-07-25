#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "../datastructures/SparsePolyMap.h"
#include "../datastructures/CoeffVector.h"
#include "Term.h"
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Represents a single-variable polynomial P(x).
 * Encapsulation: Internal terms map (SparsePolyMap) is strictly private.
 */
class Polynomial {
private:
    SparsePolyMap termsMap;

public:
    Polynomial() = default;

    /**
     * @brief Add a term (coefficient * x^exponent) to the polynomial.
     * Merges coefficients if exponent already exists.
     */
    void addTerm(double coeff, int exp);
    void addTerm(const Term& term);

    /**
     * @brief Set explicit coefficient for exponent (overwrites).
     */
    void setCoeff(int exp, double coeff);

    /**
     * @brief Get coefficient for exponent.
     */
    double getCoeff(int exp) const;

    /**
     * @brief Get highest degree of the polynomial. Returns 0 for zero polynomial.
     */
    int getDegree() const;

    /**
     * @brief Check if zero polynomial (all coefficients ~0).
     */
    bool isZero() const;

    /**
     * @brief Get total non-zero term count.
     */
    size_t getTermCount() const;

    /**
     * @brief Get list of terms ordered from highest degree to lowest degree.
     */
    std::vector<Term> getTerms() const;

    /**
     * @brief Evaluates P(x) at given x using dense CoeffVector & Horner's Method.
     */
    double evaluate(double x) const;

    /**
     * @brief Converts sparse polynomial representation to dense CoeffVector.
     */
    CoeffVector toCoeffVector() const;

    /**
     * @brief Formats polynomial as human-readable string (e.g. "3x^4 - 2x^2 + 7x - 1").
     */
    std::string toString() const;

    /**
     * @brief Serializes polynomial to JSON structure.
     */
    nlohmann::json toJson() const;
};

#endif // POLYNOMIAL_H
