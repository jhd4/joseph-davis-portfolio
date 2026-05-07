# Project Euler #50: Consecutive Prime Sum

Solution for [Project Euler #50](https://projecteuler.net/problem=50). This program identifies the prime below one million that can be written as the sum of the most consecutive primes.

### 🛠 Technical Highlights
* **Reusable Class Library:** Built upon a custom `prime_finder` class, demonstrating the ability to maintain and extend a codebase across multiple projects. 
* **Sliding Window Algorithm:** Implemented a variable-width sliding window to iterate through the prime cache. This allowed for an efficient search for the longest possible sum that still results in a prime number below the threshold.
* **Pre-population Strategy:** Optimized execution time by pre-populating the prime cache up to the million-mark threshold before beginning the summation search, avoiding the overhead of repetitive "Just-In-Time" generation during the search loop.
* **Algorithmic Pruning:** Integrated logic to "break" out of summation loops early once the cumulative sum exceeded the upper threshold, significantly reducing the total operations required.

### 📊 Complexity & Optimization
Finding the sum of the longest sequence of primes requires balancing two variables: the starting point of the sequence and the length of the sequence. By iterating through the largest possible window sizes first, the algorithm identifies the "champion" sequence early and prunes the remaining search space.



### 🚀 Usage
This project requires the `prime_finder.h` and `binary_search.h` headers.

```bash
g++ pe050-prime-sum-series.cpp -o prime_sum_solver
./prime_sum_solver 1000000