# Project Euler #18 & #67: Maximum Path Sum Optimization

Solution for [Project Euler #18](https://projecteuler.net/problem=18) and [Project Euler #67](https://projecteuler.net/problem=67). 

While Problem 18 can be solved via brute force due to its small size, Problem 67 contains a triangle with 100 rows, making an exponential $O(2^n)$ approach computationally impossible. This implementation was engineered from the start to handle both by utilizing **Dynamic Programming (DP)** and **Memoization**.

### ⚡ The Optimization: From Billions of Years to Milliseconds
The "brute force" approach attempts to check every single path from top to bottom. For a 100-row triangle, there are $2^{99}$ paths—a number so large it would take billions of years to compute. 

My solution uses a **bottom-up Dynamic Programming** approach:
* **Memoization:** Each node in the `triangle` class stores a `visited_for_summation` state.
* **Recursive Reduction:** The algorithm breaks the large triangle into smaller sub-triangles, solving for the maximum path of the base rows first and bubbling the results upward.
* **Complexity:** This reduces the time complexity from **Exponential $O(2^n)$** to **Linear $O(n)$** relative to the number of nodes.



### 🛠 Technical Implementation
* **Custom Data Structure:** Defined a `Node` struct within a specialized `triangle` class to manage pointers to `left` and `right` children in the grid.
* **Memory Management:** Implemented a custom **Destructor** using an `std::unordered_set` to track and safely `delete` nodes in a non-linear graph structure, ensuring zero memory leaks.
* **Stack-Based File Parsing:** Used `std::stack` to read the input file in reverse order, allowing the tree to be built efficiently from the bottom up.

### 🚀 Usage
The solver is designed to handle any triangle data file, regardless of size.

```bash
g++ pe018-path-sum-i.cpp -o path_solver
./path_solver 0018_triangle.txt