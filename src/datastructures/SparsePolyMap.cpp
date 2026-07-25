#include "SparsePolyMap.h"
#include <cmath>

void SparsePolyMap::setCoeff(int exp, double coeff, double eps) {
    if (std::abs(coeff) < eps) {
        terms.erase(exp);
    } else {
        terms[exp] = coeff;
    }
}

double SparsePolyMap::getCoeff(int exp) const {
    auto it = terms.find(exp);
    if (it != terms.end()) {
        return it->second;
    }
    return 0.0;
}

bool SparsePolyMap::hasTerm(int exp) const {
    return terms.find(exp) != terms.end();
}

void SparsePolyMap::removeTerm(int exp) {
    terms.erase(exp);
}

void SparsePolyMap::clear() {
    terms.clear();
}

const std::map<int, double, std::greater<int>>& SparsePolyMap::getMap() const {
    return terms;
}

size_t SparsePolyMap::size() const {
    return terms.size();
}

bool SparsePolyMap::empty() const {
    return terms.empty();
}

int SparsePolyMap::getMaxExponent() const {
    if (terms.empty()) {
        return 0;
    }
    return terms.begin()->first;
}
