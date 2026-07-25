# Viva Preparation Guide — Polynomial Calculator + Calculus Toolkit

This document contains 39 essential questions and detailed answers based on Appendix B of the project specification for oral examination preparation.

---

### Q1: Primary objective of the project?
**Answer**: To build a backend REST API service in C++ that parses, manipulates, performs arithmetic, and evaluates symbolic/numeric calculus operations on single-variable polynomials with exact internal representations and thread-safe history logging.

### Q2: What internal representation stores a polynomial?
**Answer**: A custom sparse map (`SparsePolyMap`) mapping exponent `(int)` to coefficient `(double)`.

### Q3: Why use a map instead of a fixed array for storage?
**Answer**: A map handles sparse polynomials (e.g. $x^{100} + 1$) efficiently without allocating memory for 99 zero terms.

### Q4: What algorithm evaluates a polynomial in $O(N)$?
**Answer**: Horner's method, which rewrites $P(x) = a_0 + x(a_1 + x(a_2 + \dots + x \cdot a_n))$ to eliminate unnecessary calls to `pow()`.

### Q5: What data structure parses expressions with operator precedence?
**Answer**: A Stack (`ParserStack`), used during lexical tokenization and shunting-yard/recursive-descent parsing.

### Q6: What happens on `POST /polynomial/parse`?
**Answer**: The input string is tokenized, parsed into a `Polynomial` object, validated, and returned as a coefficient list and formatted string.

### Q7: How is polynomial addition performed?
**Answer**: Terms from both polynomials are iterated, and coefficients matching the same exponent are summed.

### Q8: How is polynomial multiplication performed?
**Answer**: Every term pair $(a \cdot x^i)$ and $(b \cdot x^j)$ produces $a \cdot b$ at exponent $i + j$, accumulated into the result map.

### Q9: How is polynomial division performed?
**Answer**: Polynomial Long Division, repeatedly dividing leading terms until the degree of the remainder is strictly less than the divisor's degree.

### Q10: What is the derivative rule applied per term?
**Answer**: The Power Rule: $c \cdot x^n \to (c \cdot n) x^{n-1}$ for $n \ge 1$.

### Q11: What happens to a constant term under differentiation?
**Answer**: Constant terms ($n = 0$) vanish (become 0).

### Q12: What is the integration rule applied per term?
**Answer**: The Power Rule for Integration: $c \cdot x^n \to \frac{c}{n+1} x^{n+1}$.

### Q13: What extra term appears after indefinite integration?
**Answer**: The constant of integration, $C$ (configurable, default 0).

### Q14: How is a definite integral computed?
**Answer**: By computing the indefinite integral $F(x)$, and calculating $F(b) - F(a)$.

### Q15: What algorithm finds roots numerically?
**Answer**: Newton-Raphson method ($x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}$), falling back to Bisection search when $f'(x_n) \approx 0$.

### Q16: Why fall back to Bisection?
**Answer**: Newton-Raphson divides by $f'(x_n)$, causing division by zero or divergence when the derivative is near zero at a stationary point.

### Q17: What data structure logs operations in order?
**Answer**: A Queue (`HistoryQueue`), preserving strict chronological FIFO order.

### Q18: Why must the history log be thread-safe?
**Answer**: Multiple concurrent HTTP API requests can attempt to write to the history log simultaneously. It is guarded by `std::mutex` and `std::lock_guard`.

### Q19: What class owns the private coefficient map?
**Answer**: The `Polynomial` class.

### Q20: Why keep the coefficient map private?
**Answer**: OOP Encapsulation — to ensure internal data integrity and force interaction through validated methods like `addTerm()` and `evaluate()`.

### Q21: Which class turns a string into a Polynomial?
**Answer**: `PolynomialParser`.

### Q22: Which class performs add/subtract/multiply/divide?
**Answer**: `ArithmeticService`.

### Q23: Which class performs derivative/integral?
**Answer**: `CalculusEngine`.

### Q24: Which class wires HTTP routes to services?
**Answer**: `ApiController`.

### Q25: What are the 6 mandatory features?
**Answer**: Polynomial Parsing, Polynomial Arithmetic, Evaluation, Differentiation, Integration, and History Logging.

### Q26: Is root finding mandatory?
**Answer**: No, root finding is an optional feature implemented after the 6 mandatory features.

### Q27: Is GCD of polynomials mandatory?
**Answer**: No, optional.

### Q28: Is Taylor series mandatory?
**Answer**: No, optional.

### Q29: What happens on division by the zero polynomial?
**Answer**: Returns a clear HTTP 400 Bad Request error ("Division by zero polynomial is undefined"), preventing server crashes.

### Q30: What happens on a malformed expression string?
**Answer**: Returns an HTTP 400 error detailing the position and nature of the parsing error.

### Q31: Can float approximation replace exact symbolic results here?
**Answer**: No, exact symbolic terms are preserved wherever possible (e.g. arithmetic, derivative, indefinite integral).

### Q32: What variable does this system support?
**Answer**: A single variable, `x`.

### Q33: Does this system support multi-variable polynomials?
**Answer**: No, multi-variable polynomials are explicitly out of scope.

### Q34: What HTTP library is used by default?
**Answer**: `cpp-httplib` (single-header C++ library).

### Q35: What JSON library is suggested for serialization?
**Answer**: `nlohmann/json` (single-header C++ library).

### Q36: What is returned by `GET /history`?
**Answer**: A JSON object containing an array of all past logged operation entries with timestamps, input parameters, and results.

### Q37: What fields does a HistoryEntry contain?
**Answer**: `id`, `timestamp` (ISO format), `operation` name, `inputs` JSON, and `result` JSON.

### Q38: Why use Horner's method instead of repeated `pow()` calls?
**Answer**: Repeated `pow()` calls require $O(N^2)$ scalar multiplications, whereas Horner's method requires only $O(N)$ additions and multiplications and avoids float rounding accumulation.

### Q39: What is the time complexity of map lookup for a term?
**Answer**: $O(\log N)$ for `std::map`.
