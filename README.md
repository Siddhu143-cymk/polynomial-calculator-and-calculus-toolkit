# Polynomial Calculator + Calculus Toolkit (C++ REST API)

A high-performance, layered-architecture backend service built in modern C++ (C++17) that parses, manipulates, and performs calculus operations on single-variable polynomials. Exposed via a stateless REST API with thread-safe operation history logging.

---

## 🚀 Key Features

1. **Polynomial Parsing & Formatting**: Converts human-readable mathematical strings (e.g., `"3x^4 - 2x^2 + 7x - 1"`, `"(x + 2)*(x - 3)"`) into internal sparse term maps and pretty-printed output strings.
2. **Polynomial Arithmetic**: Symbolic addition, subtraction, multiplication, and long division with exact quotient and remainder.
3. **$O(N)$ Horner's Method Evaluation**: Evaluates polynomials efficiently using dense coefficient vector representation.
4. **Exact Symbolic Differentiation**: Applies the power rule $c \cdot x^n \to (c \cdot n) x^{n-1}$ for exact derivatives.
5. **Symbolic & Definite Integration**: Computes exact indefinite integrals $c \cdot x^n \to \frac{c}{n+1} x^{n+1} + C$ and definite integrals over $[a, b]$ via $F(b) - F(a)$.
6. **Thread-Safe Operation History**: Maintains an in-memory chronological queue of all API operations protected by `std::mutex`.
7. **Numeric Root Finding**: Implements Newton-Raphson with Bisection fallback when $f'(x) \approx 0$.

---

## 🏛 Layered Architecture

```
/PolynomialCalculusToolkit
├── /src
│   ├── /datastructures  (SparsePolyMap, CoeffVector, ParserStack, HistoryQueue)
│   ├── /models          (Term, Polynomial, HistoryEntry)
│   ├── /parser          (PolynomialParser)
│   ├── /services        (ArithmeticService, CalculusEngine, HistoryLog)
│   ├── /api             (ApiController)
│   └── /utils           (Tokenizer, JsonHelper)
├── /third_party         (httplib.h, nlohmann/json.hpp)
├── /tests               (Unit tests: test_models, test_parser, test_arithmetic, test_calculus, test_history)
├── main.cpp             (REST API server entrypoint on port 8080)
├── test_client.py       (Automated test client verifying all 10 API endpoints)
├── demo_script.py       (End-to-end calculus workflow demonstration script)
├── build.bat            (Automated build script for MinGW GCC)
├── CMakeLists.txt       (CMake configuration)
├── README.md            (System documentation)
└── VIVA_PREP.md         (Oral exam preparation guide)
```

---

## 🛠 Compilation & Build Instructions

### Prerequisites
- C++17 compliant compiler (`g++` or `clang++` or MSVC `cl.exe`)
- `cmake` (version 3.14+)
- `python` 3.x (for running test scripts)

### Building on Windows (MinGW / GCC)
Run the automated build script:
```cmd
build.bat
```
Alternatively, configure and compile manually with CMake:
```cmd
cmake -B build -G "MinGW Makefiles"
cmake --build build --parallel
```

### Running Unit Tests
Execute the compiled C++ test executables:
```cmd
build\test_models.exe
build\test_parser.exe
build\test_arithmetic.exe
build\test_calculus.exe
build\test_history.exe
```

---

## 📡 REST API Endpoint Documentation

Base URL: `http://localhost:8080`

### 1. Parse Polynomial
- **Endpoint**: `POST /polynomial/parse`
- **Body**:
  ```json
  { "expression": "3x^4 - 2x^2 + 7x - 1" }
  ```
- **Example `curl`**:
  ```bash
  curl -X POST http://localhost:8080/polynomial/parse -H "Content-Type: application/json" -d "{\"expression\":\"3x^4 - 2x^2 + 7x - 1\"}"
  ```

### 2. Polynomial Addition
- **Endpoint**: `POST /polynomial/add`
- **Body**:
  ```json
  { "a": "3x^2 + 2x - 5", "b": "x - 1" }
  ```

### 3. Polynomial Subtraction
- **Endpoint**: `POST /polynomial/subtract`
- **Body**:
  ```json
  { "a": "3x^2 + 2x - 5", "b": "x - 1" }
  ```

### 4. Polynomial Multiplication
- **Endpoint**: `POST /polynomial/multiply`
- **Body**:
  ```json
  { "a": "3x^2 + 2x - 5", "b": "x - 1" }
  ```

### 5. Polynomial Long Division
- **Endpoint**: `POST /polynomial/divide`
- **Body**:
  ```json
  { "a": "3x^2 + 2x - 5", "b": "x - 1" }
  ```
- **Returns**: Quotient and Remainder polynomials.

### 6. Evaluate Polynomial
- **Endpoint**: `POST /polynomial/evaluate`
- **Body**:
  ```json
  { "expression": "3x^2 + 2x - 5", "x": 2.0 }
  ```

### 7. Symbolic Derivative
- **Endpoint**: `POST /calculus/derivative`
- **Body**:
  ```json
  { "expression": "3x^4 - 2x^2 + 7x - 1" }
  ```

### 8. Integration (Indefinite & Definite)
- **Endpoint**: `POST /calculus/integral`
- **Indefinite Body**:
  ```json
  { "expression": "3x^2 + 2x - 5", "C": 10.0 }
  ```
- **Definite Body**:
  ```json
  { "expression": "3x^2 + 2x - 5", "a": 0.0, "b": 2.0 }
  ```

### 9. Root Finding
- **Endpoint**: `POST /calculus/roots`
- **Body**:
  ```json
  { "expression": "x^2 - 4", "guess": 1.0 }
  ```

### 10. Operation History Log
- **Endpoint**: `GET /history`
- **Returns**: Chronological array of all executed operations.

---

## 🧪 Running the E2E Demo & REST Test Client

1. **Start the API Server**:
   ```cmd
   build\poly_calc_server.exe 8080
   ```
2. **Run Automated Test Suite**:
   ```cmd
   python test_client.py
   ```
3. **Run End-to-End Demo Script**:
   ```cmd
   python demo_script.py
   ```

---

## 📌 System Assumptions
- Single variable fixed as `x`.
- In-memory `HistoryLog` persisted across request threads during server runtime.
