#ifndef CALCULUS_ENGINE_H
#define CALCULUS_ENGINE_H

#include "../models/Polynomial.h"
#include <vector>

/**
 * @brief Stateless calculus engine performing symbolic differentiation, symbolic indefinite integration,
 * numeric definite integration, and root finding.
 */
class CalculusEngine {
public:
    CalculusEngine() = default;

    /**
     * @brief Computes exact symbolic derivative of polynomial: c*x^n -> (c*n)*x^(n-1).
     */
    Polynomial differentiate(const Polynomial& p) const;

    /**
     * @brief Computes exact symbolic indefinite integral: c*x^n -> (c/(n+1))*x^(n+1) + C.
     */
    Polynomial integrateIndefinite(const Polynomial& p, double C = 0.0) const;

    /**
     * @brief Computes exact definite integral over interval [a, b] using F(b) - F(a).
     */
    double integrateDefinite(const Polynomial& p, double a, double b) const;

    /**
     * @brief Finds real roots using Newton-Raphson with Bisection fallback when derivative is zero.
     */
    std::vector<double> findRoots(const Polynomial& p, double initialGuess = 1.0,
                                  int maxIterations = 100, double tolerance = 1e-7) const;
};

#endif // CALCULUS_ENGINE_H
