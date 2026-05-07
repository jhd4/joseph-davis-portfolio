#pragma once
#include "binary_search.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cout, std::endl;


class prime_finder {
    vector<size_t> primes_found;
public:
    prime_finder() {
        primes_found = {2};
    }

    bool is_prime(size_t n) {
        while (n > primes_found.at(primes_found.size() - 1)) {
            get_next_prime();
        }
        return binary_search(primes_found, n);
    }

private:

    void get_next_prime() {
        size_t candidate = primes_found.at(primes_found.size() - 1) + 1;
        bool factor_found = true;
        while (factor_found) {
            factor_found = false;
            for (size_t i : primes_found) {
                if (candidate % i == 0) {
                    factor_found = true;
                    candidate++;
                    break;
                }
            }
        }
        primes_found.push_back(candidate);
    }


};