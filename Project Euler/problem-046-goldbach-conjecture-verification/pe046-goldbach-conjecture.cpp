//
// Created by 4jose on 4/11/2026.
//
#include "prime_finder.h"
#include <iostream>
using std::cout, std::endl;

bool composite_satisfies_conjecture(size_t n, prime_finder &finder) {
    //assumes it is given an odd composite number
    for (size_t i = 0; 2 * i * i < n; i++) {
        if (finder.is_prime(n - (2 * i * i))) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    prime_finder finder;
    size_t candidate = 3;

    while (finder.is_prime(candidate) || composite_satisfies_conjecture(candidate, finder)) {
        candidate += 2;
    }

    cout << candidate << endl;

}