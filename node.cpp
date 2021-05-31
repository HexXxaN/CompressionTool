#include "node.h"

Node::Node() {}


Node::Node(char character)
{  //konstruktor Node
	next = nullptr;
	left = nullptr;
	right = nullptr;
	weight = 0;
	symbol = character;
}


Node::Node(char character, Node* leftChild, Node* rightChild)
{
	symbol = character;
	left = leftChild;
	right = rightChild;
}


Node* Node::first_read_of_the_file(const char* directory)
{
	FILE* to_compress;
	Node* head = nullptr;
	Node* tmp = nullptr;

	to_compress = fopen(directory, "r");

	while (!feof(to_compress))
	{
		char character = getc(to_compress);

		if (feof(to_compress))
			break;

		if (head == nullptr)
		{
			head = new Node(character);
			head->weight++;
		}

		else
		{ //jezeli nie jest to przechodzimy ja do momentu znalezienia odpowiedniego znaku lub jej konca
			tmp = head;

			while (tmp->symbol != character)
			{
				if (tmp->next == nullptr)  //jezeli lista sie skonczyla (czyli nie ma na liscie naszego znaku) to tworzymy nowy element listy
					tmp->next = new Node(character);

				tmp = tmp->next;
			}
			tmp->weight++;  //zwiekszamy wage znaku
		}
	}

	fclose(to_compress);
	return head;
}


void Node::sort_list(Node* head) {  //sortowanie listy
	for (Node* tmp = head; tmp != nullptr; tmp = tmp->next) {
		for (Node* help = tmp; help != nullptr; help = help->next) {
			if (help->weight < tmp->weight) {
				char clipboard1 = tmp->symbol;
				int clipboard2 = tmp->weight;
				tmp->symbol = help->symbol;
				tmp->weight = help->weight;
				help->symbol = clipboard1;
				help->weight = clipboard2;
			}
		}
	}
}


void Node::make_tree(Node*& head)
{
	Node* tmp1 = nullptr;
	Node* tmp2 = nullptr;
	Node* tmp3 = nullptr;
	Node* internalNode = nullptr;

	while (true)
	{
		tmp1 = head;
		tmp2 = head->next;

		if (!tmp2)
			break;

		head = tmp2->next;

		internalNode = new Node('\6');
		internalNode->left = tmp1;
		internalNode->right = tmp2;
		internalNode->weight = tmp1->weight + tmp2->weight;

		if (!head || internalNode->weight <= head->weight)
		{
			internalNode->next = head;
			head = internalNode;
			continue;
		}

		tmp3 = head;

		while (tmp3->next && (internalNode->weight > tmp3->next->weight))
			tmp3 = tmp3->next;

		internalNode->next = tmp3->next;
		tmp3->next = internalNode;
	}
}