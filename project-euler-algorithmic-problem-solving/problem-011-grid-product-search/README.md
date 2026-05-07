# Project Euler #11: Largest Product in a Grid

Solution for [Project Euler #11](https://projecteuler.net/problem=11). This program parses a numerical grid (default 20x20) and identifies the greatest product of four adjacent numbers in any direction: horizontal, vertical, or diagonal.

### 🛠 Technical Highlights

* **Directional Search Engine:** Developed a modular search function `get_product_in_direction` that utilizes coordinate offsets (`delta_vertical`, `delta_horizontal`). This allows a single algorithm to traverse eight distinct directions by simply adjusting vector parameters.
* **Defensive Programming:** Implemented rigorous boundary checks (e.g., `space_to_right`, `space_below`) to ensure the algorithm never attempts to access memory outside the grid's dimensions, preventing segmentation faults.
* **Dynamic Data Parsing:** Integrated `std::ifstream` and `std::istringstream` to read raw text data and dynamically populate a 2D `std::vector` matrix.
* **Optimized Complexity:** The solution operates with $O(N \times M)$ time complexity, scanning the grid in a single pass to evaluate all possible local products.

### 📊 Skills Demonstrated

* **Data Structures:** Matrix manipulation and 2D vector traversal.
* **Algorithm Design:** Pattern recognition and spatial logic.
* **C++ File I/O:** Stream-based parsing of external datasets.

### 🚀 Usage

Compile the program using `g++` and run it by passing the path to your grid data file:

```bash
g++ pe011-grid-product.cpp -o grid_solver
./grid_solver grid_data.txt