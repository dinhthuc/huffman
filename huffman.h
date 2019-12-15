#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <io.h>
#include <fcntl.h>
#include <codecvt>
#include <locale>

using namespace std;


struct Node
{
	char ch;	// kí tự của node
	int freq;	// số lần xuất hiện
	Node *left, *right;	// cây con trái, phải
};

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};


//chỉ định 1 node cây mới
Node* getNode(unsigned char ch, unsigned int freq, Node* left, Node* right);

// mã hóa 
void encode(Node* root, string str, unordered_map<unsigned char, string> &huffmanCode);


// giải mã
void decode(Node* root, string str);

//Xây dựng Huffman Tree và giải mã
void buildHuffmanTree(string text);

//chuyển char về nhị phân
string charToBin(unsigned char c);
