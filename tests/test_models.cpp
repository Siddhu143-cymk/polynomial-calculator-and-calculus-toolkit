#include "../src/models/Polynomial.h"
#include "../src/models/Term.h"
#include "../src/datastructures/CoeffVector.h"
#include <iostream>
#include <cassert>
#include <cmath>

void testTerm() {
    Term t1(3.0, 4);
    assert(t1.getCoeff() == 3.0);
    assert(t1.getExponent() == 4);
    assert(std::abs(t1.evaluate(2.0) - 48.0) < 1e-9);
    assert(t1.toString(true) == "3x^4");

    Term t2(-1.0, 1);
    assert(t2.toString(true) == "-x");
    assert(t2.toString(false) == " - x");

    std::cout << "[PASS] testTerm\n";
}

void testPolynomial() {
    Polynomial p;
    p.addTerm(3.0, 4);
    p.addTerm(-2.0, 2);
    p.addTerm(7.0, 1);
    p.addTerm(-1.0, 0);

    assert(p.getDegree() == 4);
    assert(p.getTermCount() == 4);
    assert(p.toString() == "3x^4 - 2x^2 + 7x - 1");

    // Horner evaluation test at x = 2
    // 3(16) - 2(4) + 7(2) - 1 = 48 - 8 + 14 - 1 = 53
    double evalVal = p.evaluate(2.0);
    assert(std::abs(evalVal - 53.0) < 1e-9);

    std::cout << "[PASS] testPolynomial\n";
}

int main() {
    testTerm();
    testPolynomial();
    std::cout << "All Model unit tests passed successfully!\n";
    return 0;
}
