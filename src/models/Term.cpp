#include "Term.h"
#include <cmath>
#include <sstream>
#include <iomanip>

Term::Term() : coeff(0.0), exp(0) {}

Term::Term(double coefficient, int exponent) : coeff(coefficient), exp(exponent) {}

double Term::getCoeff() const {
    return coeff;
}

int Term::getExponent() const {
    return exp;
}

void Term::setCoeff(double c) {
    coeff = c;
}

void Term::setExponent(int e) {
    exp = e;
}

double Term::evaluate(double x) const {
    if (coeff == 0.0) return 0.0;
    if (exp == 0) return coeff;
    return coeff * std::pow(x, exp);
}

std::string Term::toString(bool isLeading) const {
    if (std::abs(coeff) < 1e-12) return "";

    std::ostringstream oss;
    double absCoeff = std::abs(coeff);

    // Sign handling
    if (!isLeading) {
        if (coeff > 0) {
            oss << " + ";
        } else {
            oss << " - ";
        }
    } else {
        if (coeff < 0) {
            oss << "-";
        }
    }

    // Coefficient formatting
    if (exp == 0) {
        oss << absCoeff;
    } else {
        if (absCoeff != 1.0) {
            oss << absCoeff;
        }
        oss << "x";
        if (exp != 1) {
            oss << "^" << exp;
        }
    }

    return oss.str();
}

nlohmann::json Term::toJson() const {
    return nlohmann::json{
        {"coefficient", coeff},
        {"exponent", exp}
    };
}
