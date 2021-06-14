#pragma once
#include <cstdio>
#include <string>


class Node {
	friend class Tree;
	Node* next;
	Node* left;
	Node* right;
	uint32_t weight;
	char symbol;

public:
	Node();
	Node(char);
	Node(char, Node*, Node*);
	Node* first_read_of_the_file(const char*);
	void make_tree(Node*& head);
	void sort_list(Node* head);
};

