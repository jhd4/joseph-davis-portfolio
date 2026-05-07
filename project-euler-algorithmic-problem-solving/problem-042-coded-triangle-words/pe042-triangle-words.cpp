#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout, std::cerr, std::endl, std::getline;

/*
//This function proved unnecessary
int get_numeric_score(string s) {
	int offset = 'A' - 1;
	int score = 0;
	for(int i : s) {
		score += i - offset;
	}
	return score;
}
*/
int get_triangle(int n) {
	return (n * (n + 1)) / 2;
}

bool is_triangle(int score) {
	int n = 1;
	int triangle = get_triangle(n);

	while (triangle < score) {
		n++;
		triangle = get_triangle(n);
	}

	return (triangle == score);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "2 arguments required" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "unable to open file: " << argv[1] << endl;
        return 2;
    }
	string input_line;
	getline(infile, input_line);
	infile.close();

	int triangular_words_count = 0;
	int offset = 'A' - 1;
	int current_score = 0;

	for(int i : input_line) {
		int adjusted_value = i - offset;
		if (1 <= adjusted_value && adjusted_value <= 26) {
			current_score += adjusted_value;
		} else {
			triangular_words_count += is_triangle(current_score);
			current_score = 0;
		}
	}

    cout << triangular_words_count << endl;
}