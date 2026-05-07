#include <iostream>
using std::cout, std::endl, std::atoi;
#include <cmath>

int main(const int argc, const char *argv[]) {
    size_t n;//our number of natural numbers to use in our sum
    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        n = 100;
    }

    size_t sum_of_squares(0);
    size_t sum_of_nums(0);

    for (int i = 1; i <= n; i++) {
        sum_of_squares += pow(i, 2);
        sum_of_nums += i;
    }

    size_t square_of_sum = pow(sum_of_nums, 2);

    cout << abs(sum_of_squares - square_of_sum) << endl;
}

