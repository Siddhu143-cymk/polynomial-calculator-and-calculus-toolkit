#include "CoeffVector.h"
#include <algorithm>

CoeffVector::CoeffVector(size_t degree) {
    coeffs.resize(degree + 1, 0.0);
}

void CoeffVector::setCoeff(size_t exp, double coeff) {
    if (exp >= coeffs.size()) {
        coeffs.resize(exp + 1, 0.0);
    }
    coeffs[exp] = coeff;
}

double CoeffVector::getCoeff(size_t exp) const {
    if (exp >= coeffs.size()) {
        return 0.0;
    }
    return coeffs[exp];
}

size_t CoeffVector::size() const {
    return coeffs.size();
}

int CoeffVector::degree() const {
    if (coeffs.empty()) return 0;
    return static_cast<int>(coeffs.size()) - 1;
}

double CoeffVector::evaluateHorner(double x) const {
    if (coeffs.empty()) {
        return 0.0;
    }
    double result = coeffs.back();
    for (int i = static_cast<int>(coeffs.size()) - 2; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}
