//NOTE: This file also successfully solves problem 67 almost instantly
#include "../utils/triangle.h"

#include <iostream>
using std::cout, std::endl, std::cerr;

#include <fstream>
using std::ifstream;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "2 arguments required, " << argc << " provided" << endl;
    	exit(1);
	}

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return 1;
    }

    triangle data_triangle = triangle(infile);
    infile.close();
	cout << data_triangle.get_max_path_sum() << endl;

}
