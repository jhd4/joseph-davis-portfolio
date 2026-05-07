#include "../utils/prime_finder.h"
#include <iostream>
using std::cout, std::cerr, std::endl, std::stoi;

size_t get_prime_sum_of_primes_with_most_terms(prime_finder finder, size_t upper_bound) {
    finder.populate_primes_up_through(upper_bound);
    size_t champion_term_count_with_prime_sum = 0;
    size_t champion_prime_found = 0;
    for (size_t i = 0; i < finder.size(); i++) {
        size_t current_sum = 0;
        size_t current_term_count = 0;
        size_t last_term_count_with_prime_sum = 0;
        size_t last_prime_found = 0;
        for (size_t j = i; j < finder.size(); j++) {
            current_sum += finder[j];
            current_term_count++;
            if (current_sum >= upper_bound) {
                break;
            }
            if (finder.is_prime(current_sum)) {
                last_term_count_with_prime_sum = current_term_count;
                last_prime_found = current_sum;
            }
        }
        if (last_term_count_with_prime_sum > champion_term_count_with_prime_sum) {
            champion_term_count_with_prime_sum = last_term_count_with_prime_sum;
            champion_prime_found = last_prime_found;
        }
    }
    return champion_prime_found;
}

int main(int argc, char *argv[]) {
    int upper_threshold = 1000000;
    if (argc > 1) {
        upper_threshold = stoi(argv[1]);
    }
    prime_finder finder;
    cout << get_prime_sum_of_primes_with_most_terms(finder, upper_threshold) << endl;
}