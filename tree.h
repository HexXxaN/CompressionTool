#pragma once
#include "node.h"
#include <string>

class Tree {
public:
	Node* root;

	struct BitBuffer
	{
		FILE* file = nullptr;
		uint8_t buffer = 0;
		uint8_t count = 0;

		void outputBit(unsigned char);
		uint8_t flush();
	};

	struct BitReader
	{
		FILE* file = nullptr;
		int indicator = 0;
		uint8_t count = 0;
		uint8_t buffer1;
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

