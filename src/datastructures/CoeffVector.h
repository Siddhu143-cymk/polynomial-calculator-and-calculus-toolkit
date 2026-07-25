#ifndef COEFF_VECTOR_H
#define COEFF_VECTOR_H

#include <vector>
#include <cstddef>

/**
 * @brief Custom thin wrapper around std::vector for dense polynomial evaluation.
 * Stores coefficients indexed by exponent: coeffs[i] is the coefficient of x^i.
 */
class CoeffVector {
private:
    std::vector<double> coeffs;

public:
    CoeffVector() = default;
    explicit CoeffVector(size_t degree);

    void setCoeff(size_t exp, double coeff);
    double getCoeff(size_t exp) const;
    size_t size() const;
    int degree() const;

    /**
     * @brief Evaluates polynomial using Horner's Method: O(N) complexity.
     * P(x) = a0 + x*(a1 + x*(a2 + ... + x*an))
     */
    double evaluateHorner(double x) const;
};

#endif // COEFF_VECTOR_H
