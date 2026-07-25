#include "../src/services/CalculusEngine.h"
#include "../src/parser/PolynomialParser.h"
#include <iostream>
#include <cassert>
#include <cmath>

void testCalculus() {
    PolynomialParser parser;
    CalculusEngine engine;

    Polynomial p = parser.parse("3x^4 - 2x^2 + 7x - 1");

    // Derivative: d/dx (3x^4 - 2x^2 + 7x - 1) = 12x^3 - 4x + 7
    Polynomial dPoly = engine.differentiate(p);
    assert(dPoly.toString() == "12x^3 - 4x + 7");

    // Indefinite Integral: integral (3x^2 + 2x - 5) dx = x^3 + x^2 - 5x + C
    Polynomial p2 = parser.parse("3x^2 + 2x - 5");
    Polynomial indPoly = engine.integrateIndefinite(p2, 10.0);
    assert(indPoly.toString() == "x^3 + x^2 - 5x + 10");

    // Definite Integral: integral_0^2 (3x^2 + 2x - 5) dx = [x^3 + x^2 - 5x]_0^2 = (8 + 4 - 10) - 0 = 2
    double defVal = engine.integrateDefinite(p2, 0.0, 2.0);
    assert(std::abs(defVal - 2.0) < 1e-9);

    // Root Finding: x^2 - 4 = 0 -> roots: 2, -2
    Polynomial pRoots = parser.parse("x^2 - 4");
    std::vector<double> roots = engine.findRoots(pRoots, 1.0);
    assert(!roots.empty());
    assert(std::abs(std::abs(roots[0]) - 2.0) < 1e-3);

    std::cout << "[PASS] testCalculus\n";
}

int main() {
    testCalculus();
    std::cout << "All Calculus unit tests passed successfully!\n";
    return 0;
}
