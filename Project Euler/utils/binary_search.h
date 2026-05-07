#pragma once
#include <vector>
using std::vector;

bool binary_search(vector<size_t> &L, size_t n, int min, int max) {
    int middle = (max + min) / 2;
    if (L[middle] == n) {
        return true;
    }

    if (min >= max) {
        return false;
    }

    if (n > L[middle]) {
        return binary_search(L, n, middle + 1, max);
    } else {
        return binary_search(L, n, min, middle);
    }
}

bool binary_search(vector<size_t> &L, size_t n) {
    return binary_search(L, n, 0, L.size() - 1);
}