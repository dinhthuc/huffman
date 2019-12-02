#ifndef  _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>

using namespace std;

struct Node
{
	char ch; // kí tự của node
	int  freq; // số lần xuất hiện
	Node *left, *right; // cây con trái, phải
};

struct comp
{
	bool operator()(Node*l, Node* r)
	{
		//đặt ưu tiên cao nhất cho kí tự có tần suất thấp nhất
		return l->freq > r->freq;
	}
};
//chỉ định 1 node cây mới
Node* getNode(char ch, int freq, Node* left, Node* right);

// mã hóa 
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode);


// giải mã
void decode(Node* root, int &index, string FileName);

//Xây dựng Huffman Tree và giải mã văn bản đầu vào đã cho
void buildHuffmanTree(string fileName);



#endif // ! _NODE_H_
