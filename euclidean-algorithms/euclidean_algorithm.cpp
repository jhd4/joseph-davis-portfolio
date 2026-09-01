//
// Created by 4jose on 5/6/2026.
//
#include <iostream>
using std::cout, std::cerr, std::endl, std::stoi;
#include <algorithm>
using std::max, std::min;

int GCD(const int a, const int b) {
    int A = max(a, b);
    int B = min(a, b);
    int q = A / B;
    int r = A % B;
    if (r == 0) {
        //cout << "Calculation yields GCD(" << a << "," << b << ") = " << B << endl;
        return B;
    } else {
        //cout << "Calculation yields GCD(" << a << "," << b << ") = GCD(" << B << "," << r << ")" << endl;
        return GCD(B, r);
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
    int gcd = GCD(arg1, arg2);
    cout << "GCD(" << arg1 << ", " << arg2 << ") = " << gcd << endl;
}