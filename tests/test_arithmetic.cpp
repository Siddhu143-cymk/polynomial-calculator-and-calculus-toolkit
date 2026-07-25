#include "../src/services/ArithmeticService.h"
#include "../src/parser/PolynomialParser.h"
#include <iostream>
#include <cassert>

void testArithmetic() {
    PolynomialParser parser;
    ArithmeticService service;

    Polynomial a = parser.parse("3x^2 + 2x - 5");
    Polynomial b = parser.parse("x - 1");

    // Addition
    Polynomial sum = service.add(a, b);
    assert(sum.toString() == "3x^2 + 3x - 6");

    // Subtraction
    Polynomial diff = service.subtract(a, b);
    assert(diff.toString() == "3x^2 + x - 4");

    // Multiplication
    // (3x^2 + 2x - 5)*(x - 1) = 3x^3 - 3x^2 + 2x^2 - 2x - 5x + 5 = 3x^3 - x^2 - 7x + 5
    Polynomial prod = service.multiply(a, b);
    assert(prod.toString() == "3x^3 - x^2 - 7x + 5");

    // Long Division
    // (3x^2 + 2x - 5) / (x - 1)
    // 3x^2 + 2x - 5 = (3x + 5)(x - 1) + 0
    DivisionResult divRes = service.divide(a, b);
    assert(divRes.quotient.toString() == "3x + 5");
    assert(divRes.remainder.isZero());

    std::cout << "[PASS] testArithmetic\n";
}

int main() {
    testArithmetic();
    std::cout << "All Arithmetic unit tests passed successfully!\n";
    return 0;
}
