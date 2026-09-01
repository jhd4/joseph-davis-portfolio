# Euclidean & Extended Euclidean Algorithms in C++

C++ implementations of the classical Euclidean Algorithm and Extended Euclidean Algorithm for computing greatest common divisors (GCD) and Bézout coefficients.

---

## Overview

This repository contains lightweight, standalone C++ implementations of fundamental number-theoretic algorithms:

* **Euclidean Algorithm (`euclidean_algorithm.cpp`)**: Calculates the Greatest Common Divisor ($\gcd(a, b)$) of two positive integers using recursive division steps.
* **Extended Euclidean Algorithm (`extended_euclidean_algorithm.cpp`)**: Computes $\gcd(a, b)$ alongside Bézout coefficients $x, y \in \mathbb{Z}$ satisfying Bézout's Identity:
  $$a x + b y = \gcd(a, b)$$

---

## Technical Features

### Fixed-Size Array Reference Parameters
Rather than returning heap-allocated arrays or permitting array-to-pointer decay, the extended algorithm leverages reference-to-array signatures in C++:
```cpp
void extended_euclidean_algorithm(int a, int b, int (&output)[3])
```
This enforces exact buffer sizes at compile time and avoids dynamic memory allocation overhead.

### Iterative State Cycling
The helper function `cycle_coeff_history` updates running coefficient buffers iteratively across division steps:
```cpp
int new_coeff = coeff_history[1] - (q * coeff_history[0]);
coeff_history[1] = coeff_history[0];
coeff_history[0] = new_coeff;
```
This tracks linear combinations efficiently without recursive stack overhead.

### Command-Line Interface & Validation
Both utilities include input validation and error handling:
* Validates parameter counts (`argc >= 3`).
* Converts arguments to integers via `std::stoi`.
* Enforces domain constraints ($a, b \ge 1$).
* Directs diagnostic error messages to `std::cerr` with distinct non-zero exit codes.

---

## Building and Execution

### Compilation

```bash
g++ euclidean_algorithm.cpp -o euclidean
g++ extended_euclidean_algorithm.cpp -o extended_euclidean
```

### Usage

**Euclidean Algorithm:**
```bash
./euclidean 252 105
# Output: GCD(252, 105) = 21
```

**Extended Euclidean Algorithm:**
```bash
./extended_euclidean 252 105
# Output: 21 = (-2 * 252) + (5 * 105)
```