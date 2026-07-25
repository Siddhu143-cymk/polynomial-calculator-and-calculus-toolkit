#include "ArithmeticService.h"
#include <stdexcept>
#include <cmath>

Polynomial ArithmeticService::add(const Polynomial& a, const Polynomial& b) const {
    Polynomial result = a;
    for (const auto& term : b.getTerms()) {
        result.addTerm(term.getCoeff(), term.getExponent());
    }
    return result;
}

Polynomial ArithmeticService::subtract(const Polynomial& a, const Polynomial& b) const {
    Polynomial result = a;
    for (const auto& term : b.getTerms()) {
        result.addTerm(-term.getCoeff(), term.getExponent());
    }
    return result;
}

Polynomial ArithmeticService::multiply(const Polynomial& a, const Polynomial& b) const {
    Polynomial result;
    if (a.isZero() || b.isZero()) {
        return result;
    }

    for (const auto& termA : a.getTerms()) {
        for (const auto& termB : b.getTerms()) {
            double c = termA.getCoeff() * termB.getCoeff();
            int exp = termA.getExponent() + termB.getExponent();
            result.addTerm(c, exp);
        }
    }
    return result;
}

DivisionResult ArithmeticService::divide(const Polynomial& dividend, const Polynomial& divisor) const {
    if (divisor.isZero()) {
        throw std::invalid_argument("Division by zero polynomial is undefined");
    }

    DivisionResult result;
    if (dividend.isZero()) {
        return result;
    }

    int degDivisor = divisor.getDegree();
    double leadCoeffDivisor = divisor.getCoeff(degDivisor);

    if (dividend.getDegree() < degDivisor) {
        result.remainder = dividend;
        return result;
    }

    Polynomial rem = dividend;
    Polynomial quot;

    while (!rem.isZero() && rem.getDegree() >= degDivisor) {
        int degRem = rem.getDegree();
        double leadCoeffRem = rem.getCoeff(degRem);

        int scaleExp = degRem - degDivisor;
        double scaleCoeff = leadCoeffRem / leadCoeffDivisor;

        quot.addTerm(scaleCoeff, scaleExp);

        // Term to subtract: scaleCoeff * x^scaleExp * divisor
        Polynomial subTermPoly;
        subTermPoly.addTerm(scaleCoeff, scaleExp);
        Polynomial productToSub = multiply(subTermPoly, divisor);

        rem = subtract(rem, productToSub);
    }

    result.quotient = quot;
    result.remainder = rem;
    return result;
}
