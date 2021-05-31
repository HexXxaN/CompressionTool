#include "tree.h"


Tree::Tree() {}


Tree::Tree(Node* head)
{
	root = head;
}


void Tree::create_compressed_file(const char* directory)
{
	FILE* to_compress;
	BitBuffer Buffer;
	unsigned char legit;
	
	Buffer.file = fopen("compressed.huf", "w+b");
	to_compress = fopen(directory, "r");
	putc(1, Buffer.file);
	storeTree(root, Buffer);
	legit = Buffer.flush();

	while(!feof(to_compress))
	{
		char character = getc(to_compress);
		codeT(character, root, "", Buffer);
	}

	legit = Buffer.flush();
	rewind(Buffer.file);
	fwrite(&legit, 1, 1, Buffer.file);
	fclose(Buffer.file);
	fclose(to_compress);
}


void Tree::decompress_file(const char* directory)
{
	FILE* decompressedFile = nullptr;
	BitReader Reader;
	unsigned char bitsInLastByte;

	Reader.file = fopen(directory, "rb");
	bitsInLastByte = (unsigned char)getc(Reader.file);
	decompressedFile = fopen("decompressed.txt", "w");
	Reader.buffer1 = (unsigned char)getc(Reader.file);
	Reader.indicator = getc(Reader.file);
	root = ReadNode(Reader);
	Reader.count = 0;
	Reader.buffer1 = (unsigned char)Reader.indicator;
	Reader.indicator = getc(Reader.file);

	while (Reader.indicator >= 0 || Reader.count < bitsInLastByte)
		putc(Reader.decode(root), decompressedFile);

	fclose(Reader.file);
	fclose(decompressedFile);
}


unsigned char Tree::BitBuffer::flush()
{
	unsigned char tmp = count;

	count = 0;

	if (tmp == 0)
	{
		buffer = 0;
		return 8;
	}

	buffer <<= 8 - tmp;

	fputc(buffer, file);
	buffer = 0;
	return tmp;
}


void Tree::BitBuffer::outputBit(unsigned char bit)
{
	buffer <<= 1;
	if (bit)
		buffer |= 1;
	count++;
	if (count == 8) {
		fwrite(&buffer, sizeof(buffer), 1, file);
		buffer = 0;
		count = 0;
	}
}


bool Tree::codeT(char c, Node* p, std::string b, BitBuffer& Buffer)
{
	if (!p->left)
	{
		if (c != p->symbol)
			return false;

		for (unsigned int i = 0; i < b.size(); i++)
		{
			if (b[i] == '1')
				Buffer.outputBit(1);
			else if (b[i] == '0')
				Buffer.outputBit(0);
		}
		return true;
	}
	return codeT(c, p->left, b + "0", Buffer) || codeT(c, p->right, b + "1", Buffer);
}


void Tree::storeTree(Node* node, BitBuffer& buffer)
{
	if (node->left && node->right)
	{
		buffer.outputBit(0);

		storeTree(node->left, buffer);

		storeTree(node->right, buffer);

	}
	else if (node->right == nullptr && node->left == nullptr)
	{
		char sign = node->symbol;

		buffer.outputBit(1);

		for (int i = 7; i >= 0; i--)
		{
			unsigned char bit = ((sign >> i) & 1); //bierzemy bity w znaku ascii i przepisujemy je pojedynczo do bufora
			buffer.outputBit(bit);
		}
	}
}


bool Tree::BitReader::bit_reader()
{
	if (count < 7)
	{
		bool a = ((buffer1 >> 7-count) & 1);
		count++;
		return a;
	}

	bool a = buffer1 & 1;
	count = 0;

	buffer1 = (unsigned char)indicator;
	indicator = getc(file);

	return a;
}


char Tree::BitReader::byte_reader()
{
	char character = 0;

	for (int i = 7; i >= 0; i--)
	{
		character <<= 1;

		if (bit_reader())
			character |= 1;
	}
	return character;
}


Node* Tree::ReadNode(BitReader& reader)
{
	if (reader.bit_reader())
		return new Node(reader.byte_reader(), nullptr, nullptr);
	Node* leftChild = ReadNode(reader);
	Node* rightChild = ReadNode(reader);
	return new Node('\6', leftChild, rightChild);
}


char Tree::BitReader::decode(Node* root)
{
	Node* temporary = root;

	while (temporary->left && temporary->right)
	{
		if (!bit_reader())
			temporary = temporary->left;
		else
			temporary = temporary->right;
	}
	return temporary->symbol;
}


void Tree::delete_tree(Node*& root) {
	if (root != nullptr)
	{
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
		root = nullptr;
	}
}