//
// Created by 4jose on 5/6/2026.
//
#include <iostream>
using std::cout, std::cerr, std::endl, std::stoi;
#include <algorithm>
using std::max, std::min;

void cycle_coeff_history(int (&coeff_history)[2], int q) {
	int new_coeff = coeff_history[1] - (q * coeff_history[0]);
	coeff_history[1] = coeff_history[0];
	coeff_history[0] = new_coeff;
}

void extended_euclidean_algorithm(int a, int b, int (&output)[3]) {
	//edits the output array to the form [gcd, a_coeff, b_coeff]
	if (a < b) {
		extended_euclidean_algorithm(b, a, output);
		int temp = output[1];
		output[1] = output[2];
		output[2] = temp;
	} else {
		//in history, more recent history comes closer to the start of the list
		int A_coeff_history[] = {0, 1};
		int B_coeff_history[] = {1, 0};
		int r_history[] = {b, a};

		while (r_history[0] != 0) {
			//calculate new q and r
			int q = r_history[1] / r_history[0];
			int r = r_history[1] % r_history[0];
			//update coefficients
			cycle_coeff_history(A_coeff_history, q);
			cycle_coeff_history(B_coeff_history, q);
			//update r_history
			r_history[1] = r_history[0];
			r_history[0] = r;
		}

		int gcd = r_history[1];
		int A_coeff = A_coeff_history[1];
		int B_coeff = B_coeff_history[1];

		output[0] = gcd;
		output[1] = A_coeff;
		output[2] = B_coeff;
	}
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << argc << " arguments provided, 3 required" << endl;
        return 1;
    }

    int arg1 = stoi(argv[1]);
    int arg2 = stoi(argv[2]);
    if (arg1 < 1 || arg2 < 1) {
        cerr << "Invalid inputs, " << arg1 << " and " << arg2 << " are not both positive integers" << endl;
        return 2;
    }

	int euclidean_output[3];
	extended_euclidean_algorithm(arg1, arg2, euclidean_output);
    cout << euclidean_output[0] << " = (" << euclidean_output[1] << " * " << arg1 << ") + (" << euclidean_output[2] << " * " << arg2 << ")" << endl;
}