#pragma once
#include "node.h"
#include <string>

class Tree {
public:
	Node* root;

	struct BitBuffer
	{
		FILE* file = nullptr;
		unsigned char buffer = 0;
		unsigned char count = 0;

		void outputBit(unsigned char);
		unsigned char flush();
	};

	struct BitReader
	{
		FILE* file = nullptr;
		int indicator = 0;
		unsigned char count = 0;
		unsigned char buffer1;
		bool bit_reader();
		char byte_reader();
		char decode(Node*);
	};

	Tree();
	Tree(Node*);
	bool codeT(char, Node*, std::string, BitBuffer&);
	void create_compressed_file(const char*);
	void storeTree(Node*, BitBuffer&);
	void delete_tree(Node*&);
	void decompress_file(const char*);
	Node* ReadNode(BitReader&);
};

