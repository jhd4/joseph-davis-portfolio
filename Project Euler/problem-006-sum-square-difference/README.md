# Project Euler #6: Sum Square Difference

Solution for [Project Euler #6](https://projecteuler.net/problem=6). 

### Technical Implementation
This C++ program calculates the positive difference between the sum of squares and the square of the sum for a series of natural numbers. 

* **Runtime Efficiency:** Optimized $O(n)$ iteration.
* **Scalability:** Uses `size_t` to handle large 64-bit integers.
* **Dynamic CLI:** Accepts `argc/argv` for custom inputs.

### Usage
```bash
g++ pe006-sum-square-diff.cpp -o solution
./solution 100