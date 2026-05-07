# Project Euler: Algorithmic Problem Solving in C++

A collection of high-performance C++ solutions for [Project Euler](https://projecteuler.net/) challenges. This repository emphasizes mathematical optimization, efficient data structures, and the development of reusable computational libraries.

### 🛠 Core Engineering Principles
* **Modular Library Design:** Developed a shared `utils/` directory to house optimized mathematical components (e.g., Sieve-based Prime Finders, Binary Search) used across multiple challenges.
* **Computational Efficiency:** Optimized brute-force mathematical problems through algorithmic refinement, such as implementing $O(\sqrt{N})$ primality testing and dynamic programming for path-sum optimizations.
* **Resource Management:** Utilized STL containers like `std::vector` and custom classes to manage large datasets and Just-In-Time (JIT) sequence generation.

---

### 📂 Repository Structure
* **`/utils`**: Reusable header-only libraries including `prime_finder.h` and `binary_search.h`.
* **`/problem-006-sum-square-difference`**: Optimized calculation of sum-square differences using arithmetic series logic.
* **`/problem-011-grid-product-search`**: A linear scan algorithm that identifies the greatest product of four adjacent numbers in a 20x20 grid (horizontal, vertical, and diagonal).
* **`/problem-018-067-path-sum-optimization`**: Solving triangle path constraints using a bottom-up dynamic programming approach to find the maximum sum from top to bottom.
* **`/problem-042-coded-triangle-words`**: Converts words to numerical values and checks them against a generated sequence of triangle numbers (tₙ = ½n(n+1)).
* **`/problem-046-goldbach-conjecture-verification`**: A computational search for the smallest odd composite number that contradicts Goldbach's other conjecture by checking $n = p + 2k^2$.
* **`/problem-050-consecutive-prime-sum`**: Identifying the prime below one million that can be written as the sum of the most consecutive primes using $O(N \log \log N)$ pre-computation.

---

### 🚀 Usage & Compilation
Each problem folder is self-contained. To compile a solution while linking the shared utilities in the `utils/` directory, use the `-I` include flag:

```bash
# Example for Problem 50
# Navigate to the problem folder first, then run:
g++ pe050-prime-sum-series.cpp -I../utils -o prime_sum_solver

# Run the executable
./prime_sum_solver 1000000