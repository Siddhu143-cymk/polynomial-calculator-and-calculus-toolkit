#ifndef ARITHMETIC_SERVICE_H
#define ARITHMETIC_SERVICE_H

#include "../models/Polynomial.h"
#include <utility>

struct DivisionResult {
    Polynomial quotient;
    Polynomial remainder;
};

/**
 * @brief Stateless service performing arithmetic operations on Polynomial objects.
 */
class ArithmeticService {
public:
    ArithmeticService() = default;

    Polynomial add(const Polynomial& a, const Polynomial& b) const;
    Polynomial subtract(const Polynomial& a, const Polynomial& b) const;
    Polynomial multiply(const Polynomial& a, const Polynomial& b) const;

    /**
     * @brief Performs Polynomial Long Division: dividend / divisor.
     * Returns quotient and remainder such that dividend = quotient * divisor + remainder.
     * @throws std::invalid_argument if divisor is the zero polynomial.
     */
    DivisionResult divide(const Polynomial& dividend, const Polynomial& divisor) const;
};

#endif // ARITHMETIC_SERVICE_H
