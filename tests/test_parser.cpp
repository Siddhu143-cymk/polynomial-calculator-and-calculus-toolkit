#include "../src/parser/PolynomialParser.h"
#include <iostream>
#include <cassert>

void testPolynomialParser() {
    PolynomialParser parser;

    Polynomial p1 = parser.parse("3x^4 - 2x^2 + 7x - 1");
    assert(p1.getDegree() == 4);
    assert(p1.getCoeff(4) == 3.0);
    assert(p1.getCoeff(2) == -2.0);
    assert(p1.getCoeff(1) == 7.0);
    assert(p1.getCoeff(0) == -1.0);

    Polynomial p2 = parser.parse("-x^3 + 5");
    assert(p2.getDegree() == 3);
    assert(p2.getCoeff(3) == -1.0);
    assert(p2.getCoeff(0) == 5.0);

    Polynomial p3 = parser.parse("(x + 2)*(x - 3)");
    // x^2 - x - 6
    assert(p3.getDegree() == 2);
    assert(p3.getCoeff(2) == 1.0);
    assert(p3.getCoeff(1) == -1.0);
    assert(p3.getCoeff(0) == -6.0);

    std::cout << "[PASS] testPolynomialParser\n";
}

int main() {
    testPolynomialParser();
    std::cout << "All Parser unit tests passed successfully!\n";
    return 0;
}
