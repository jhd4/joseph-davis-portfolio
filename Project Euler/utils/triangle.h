#pragma once

#include <iostream>
using std::cout, std::endl, std::cerr;

#include <istream>
using std::istream;

#include <string>
using std::string;

#include <sstream>
using std::istringstream;

#include <stack>
using std::stack;

#include <vector>
using std::vector;

#include <unordered_set>
using std::unordered_set;

#include <algorithm>
using std::max;

class triangle {//a specialized binary tree for the problem. It will walk down recursively to get the highest sum path in the tree
    struct Node {
        Node *left;
        Node *right;
        int value;
        bool visited_for_summation;
		bool visited_for_deletion;

        Node(int v) : left(nullptr), right(nullptr), value(v), visited_for_summation(false), visited_for_deletion(false) {}
    };
    Node *root;

public:
    triangle() : root(nullptr) {}

    triangle(istream &infile) {
        //look at HW 1b for file reading
        //this constructor should take a filestream pointing to a valid input file
        //it reads out one line at a time. It adds each line to a stack
		stack<string> line_stack;
		string line_to_stack;
		while (getline(infile, line_to_stack)) {
			line_stack.push(line_to_stack);
    	}
		string line_from_stack = line_stack.top();
		line_stack.pop();
		vector<Node*> row_below = read_row_from_line(line_from_stack);
		vector<Node*> current_row;

		while (!line_stack.empty()) {
			line_from_stack = line_stack.top();
			line_stack.pop();
			current_row = read_row_from_line(line_from_stack);
			if(row_below.size() - current_row.size() != 1) {
				cerr << "improper triangle, row size difference of " << current_row.size() - row_below.size() << endl;
				exit(2);
			}
			for(int i = 0; i < current_row.size(); i++) {
				current_row[i]->left = row_below[i];
				current_row[i]->right = row_below[i + 1];
			}
			row_below = current_row;
		}
		root = row_below[0];
    }

    ~triangle() {
		unordered_set<Node*> to_delete;
        add_to_deletion_set(root, to_delete);
		for(auto node : to_delete) {
			delete node;
		}
		root = nullptr;
    }

	int get_max_path_sum() {
		return get_max_path_sum(root);
	}

private:
    void add_to_deletion_set(Node *node, unordered_set<Node*>& to_delete) {
        if (node != nullptr && !node->visited_for_deletion) {
			to_delete.insert(node);
			node->visited_for_deletion = true;
            add_to_deletion_set(node->left, to_delete);
            add_to_deletion_set(node->right, to_delete);
        }
    }

	vector<Node*> read_row_from_line(string line) {
		istringstream current_line_stream(line);
		vector<Node*> output_row;
		int num_catcher;
		while (current_line_stream >> num_catcher) {
			output_row.push_back(new Node(num_catcher));
		}
		return output_row;
	}

	int get_max_path_sum(Node *node) {
		if(node == nullptr) {
			return 0;
		} else if (node->visited_for_summation) {
			return node->value;
		} else {
			node->value += max(get_max_path_sum(node->left), get_max_path_sum(node->right));
			node->visited_for_summation = true;
			return node->value;
		}
	}
};