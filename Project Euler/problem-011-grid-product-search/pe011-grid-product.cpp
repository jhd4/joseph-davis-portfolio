//
// Created by 4jose on 4/13/2026.
//

#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;
#include <iostream>
using std::cout, std::cerr, std::endl, std::getline;
#include <vector>
using std::vector;
#include <string>
using std::string;

int max(const int a, const int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int get_product_in_direction(const int delta_vertical, const int delta_horizontal, const int i, const int j, const int NUMBER_OF_TERMS, const vector<vector<int>> &num_grid) {
    //assumes grid size and indices are valid to reference
    int product = 1;
    for (int k = 0; k < NUMBER_OF_TERMS; k++) {
        product *= num_grid.at(i + (k * delta_vertical)).at(j + (k * delta_horizontal));
    }
    return product;
}

int main(int argc, char *argv[]) {
    //asserting valid input
    if (argc < 2) {
        std::cerr << "2 arguments required" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "unable to open file " << argv[1] << endl;
        return 2;
    }

    //reading data
    vector<vector<int>> num_grid;
    string file_line;
    while (getline(infile, file_line)) {
        istringstream line_stream(file_line);
        vector<int> grid_row;
        int elem;
        while (line_stream >> elem) {
            grid_row.push_back(elem);
        }
        if (num_grid.size() > 0 && grid_row.size() != num_grid[num_grid.size() - 1].size()) {
            cerr << "improper grid, row lengths do not match.";
            cerr << "num_grid[last].size(): " << num_grid[num_grid.size() - 1].size() << "; ";
            cerr << "grid_row.size(): " << grid_row.size() << endl;
            return 3;
        }
        num_grid.push_back(grid_row);
    }
    infile.close();

    //multiplications
    int champion_product = 0;
    const int NUMBER_OF_TERMS = 4;
    for (int i = 0; i < num_grid.size(); i++) {
        //cout << "i = " << i << endl;
        bool space_below = (i + NUMBER_OF_TERMS <= num_grid.size());
        bool space_above = (i - NUMBER_OF_TERMS + 1 >= 0);
        for (int j = 0; j < num_grid[i].size(); j++) {
            //cout << "    " << "    " << "j = " << j << endl;

            bool space_to_right = (j + NUMBER_OF_TERMS <= num_grid[i].size());
            if (space_to_right) {
                //cout << "    " << "    " << "space to right" << endl;
                int right_product = get_product_in_direction(0, 1, i, j, NUMBER_OF_TERMS, num_grid);
                champion_product = max(champion_product, right_product);
                if (space_above) {
                    //cout << "    " << "    " << "space above" << endl;
                    int diagonal_up_product = get_product_in_direction(-1, 1, i, j, NUMBER_OF_TERMS, num_grid);
                    champion_product = max(champion_product, diagonal_up_product);
                }
                if (space_below) {
                    //cout << "    " << "    " << "space below" << endl;
                    int diagonal_down_product = get_product_in_direction(1, 1, i, j, NUMBER_OF_TERMS, num_grid);
                    champion_product = max(champion_product, diagonal_down_product);
                }
            }

            if (space_below) {
                int down_product = get_product_in_direction(1, 0, i, j, NUMBER_OF_TERMS, num_grid);
                champion_product = max(champion_product, down_product);
            }
        }
    }

    cout << champion_product << endl;

}