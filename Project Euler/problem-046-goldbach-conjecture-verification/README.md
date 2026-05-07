# Project Euler #46: Goldbach's Other Conjecture

Solution for [Project Euler #46](https://projecteuler.net/problem=46). This program identifies the smallest odd composite number that cannot be written as the sum of a prime and twice a square ($n = p + 2k^2$).

### 🛠 Technical Architecture
* **Modular Library Design:** Instead of writing a monolithic script, I developed a reusable `prime_finder` class. This class encapsulates prime number generation and verification logic, which can be imported into multiple projects.
* **Lazy Evaluation (JIT Generation):** The `prime_finder` class implements a "Just-In-Time" generation strategy. It only calculates new primes when the candidate number exceeds the current cache, significantly reducing unnecessary computations.
* **Efficient Search Heuristics:** The `composite_satisfies_conjecture` function utilizes a mathematical shortcut: it only iterates through possible squares where $2k^2 < n$, drastically narrowing the search space.
* **Recursive Binary Search:** Integrated a custom-built recursive binary search algorithm to verify prime status within the cached dataset in $O(\log n)$ time.

### 📐 Mathematical Logic
The program iterates through odd composite candidates ($3, 5, 7, ...$) and attempts to disprove the conjecture for each by checking:
$$n - 2k^2 = p$$
If no prime $p$ is found for any integer $k$, the conjecture is disproven for that $n$.



### 🚀 Usage
This project depends on the `prime_finder.h` and `binary_search.h` headers included in this repository.

```bash
g++ pe046-goldbach-conjecture.cpp -o conjecture_solver
./conjecture_solver