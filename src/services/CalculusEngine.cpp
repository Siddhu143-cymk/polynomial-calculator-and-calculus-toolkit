#include "CalculusEngine.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

Polynomial CalculusEngine::differentiate(const Polynomial& p) const {
    Polynomial result;
    if (p.isZero()) {
        return result;
    }

    for (const auto& term : p.getTerms()) {
        int exp = term.getExponent();
        double coeff = term.getCoeff();

        if (exp >= 1) {
            result.addTerm(coeff * exp, exp - 1);
        }
        // exp == 0 vanishes
    }
    return result;
}

Polynomial CalculusEngine::integrateIndefinite(const Polynomial& p, double C) const {
    Polynomial result;
    if (!p.isZero()) {
        for (const auto& term : p.getTerms()) {
            int exp = term.getExponent();
            double coeff = term.getCoeff();

            result.addTerm(coeff / (exp + 1.0), exp + 1);
        }
    }

    if (std::abs(C) > 1e-12) {
        result.addTerm(C, 0);
    }
    return result;
}

double CalculusEngine::integrateDefinite(const Polynomial& p, double a, double b) const {
    if (a >= b) {
        throw std::invalid_argument("Definite integral lower bound 'a' must be strictly less than upper bound 'b'");
    }

    Polynomial indefinite = integrateIndefinite(p, 0.0);
    double valB = indefinite.evaluate(b);
    double valA = indefinite.evaluate(a);
    return valB - valA;
}

std::vector<double> CalculusEngine::findRoots(const Polynomial& p, double initialGuess,
                                               int maxIterations, double tolerance) const {
    std::vector<double> roots;
    if (p.isZero()) {
        return roots; // All numbers are roots of zero poly
    }

    Polynomial dPoly = differentiate(p);

    double x = initialGuess;
    bool converged = false;

    for (int i = 0; i < maxIterations; ++i) {
        double fx = p.evaluate(x);
        if (std::abs(fx) < tolerance) {
            roots.push_back(x);
            converged = true;
            break;
        }

        double fprimex = dPoly.evaluate(x);

        if (std::abs(fprimex) < 1e-10) {
            // Fallback to Bisection search around x
            double left = x - 5.0;
            double right = x + 5.0;
            double fLeft = p.evaluate(left);
            double fRight = p.evaluate(right);

            if (fLeft * fRight <= 0.0) {
                for (int b = 0; b < 60; ++b) {
                    double mid = (left + right) / 2.0;
                    double fMid = p.evaluate(mid);
                    if (std::abs(fMid) < tolerance) {
                        x = mid;
                        converged = true;
                        break;
                    }
                    if (fLeft * fMid < 0) {
                        right = mid;
                        fRight = fMid;
                    } else {
                        left = mid;
                        fLeft = fMid;
                    }
                }
                if (converged) {
                    roots.push_back(x);
                    break;
                }
            }
            // If bisection range didn't bracket root, perturb x slightly
            x += 0.5;
            continue;
        }

        double nextX = x - (fx / fprimex);
        if (std::abs(nextX - x) < tolerance) {
            x = nextX;
            roots.push_back(x);
            converged = true;
            break;
        }

        x = nextX;
    }

    // Clean up roots (round close values to standard precision)
    for (auto& r : roots) {
        if (std::abs(r - std::round(r)) < 1e-6) {
            r = std::round(r);
        }
    }

    return roots;
}
