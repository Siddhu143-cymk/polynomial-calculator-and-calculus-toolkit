#include "Polynomial.h"
#include <sstream>
#include <cmath>

void Polynomial::addTerm(double coeff, int exp) {
    if (exp < 0) {
        throw std::invalid_argument("Polynomial exponents must be non-negative integers");
    }
    double current = termsMap.getCoeff(exp);
    termsMap.setCoeff(exp, current + coeff);
}

void Polynomial::addTerm(const Term& term) {
    addTerm(term.getCoeff(), term.getExponent());
}

void Polynomial::setCoeff(int exp, double coeff) {
    if (exp < 0) {
        throw std::invalid_argument("Polynomial exponents must be non-negative integers");
    }
    termsMap.setCoeff(exp, coeff);
}

double Polynomial::getCoeff(int exp) const {
    return termsMap.getCoeff(exp);
}

int Polynomial::getDegree() const {
    if (termsMap.empty()) return 0;
    return termsMap.getMaxExponent();
}

bool Polynomial::isZero() const {
    return termsMap.empty();
}

size_t Polynomial::getTermCount() const {
    return termsMap.size();
}

std::vector<Term> Polynomial::getTerms() const {
    std::vector<Term> list;
    for (const auto& pair : termsMap.getMap()) {
        list.emplace_back(pair.second, pair.first);
    }
    return list;
}

CoeffVector Polynomial::toCoeffVector() const {
    int deg = getDegree();
    CoeffVector cv(deg);
    for (const auto& pair : termsMap.getMap()) {
        if (pair.first >= 0) {
            cv.setCoeff(static_cast<size_t>(pair.first), pair.second);
        }
    }
    return cv;
}

double Polynomial::evaluate(double x) const {
    if (isZero()) return 0.0;
    CoeffVector cv = toCoeffVector();
    return cv.evaluateHorner(x);
}

std::string Polynomial::toString() const {
    if (isZero()) return "0";

    std::ostringstream oss;
    bool isLeading = true;

    for (const auto& pair : termsMap.getMap()) {
        Term t(pair.second, pair.first);
        oss << t.toString(isLeading);
        isLeading = false;
    }

    std::string str = oss.str();
    return str.empty() ? "0" : str;
}

nlohmann::json Polynomial::toJson() const {
    nlohmann::json termsJson = nlohmann::json::array();
    for (const auto& pair : termsMap.getMap()) {
        termsJson.push_back({
            {"exponent", pair.first},
            {"coefficient", pair.second}
        });
    }
    return nlohmann::json{
        {"pretty", toString()},
        {"degree", getDegree()},
        {"terms", termsJson}
    };
}
