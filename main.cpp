#include "NODE.h"

// Huffman coding algorithm
int main()
{

	buildHuffmanTree("text.txt");
	//fstream fileOutput2;
	//fileOutput2.open("huffman.txt");

	//if (fileOutput2.fail())
	//{
	//	cout << "Failed to open this file!" << endl;
	//}

	//string ch = "";
	//while (!fileOutput2.eof())
	//{
	//	char c;
	//	fileOutput2.get(c); //đọc từng kí tự
	//	ch += c;
	//}

	//cout << ch << endl;

	//string str = "";

	//for (char& _char : ch)
	//{
	//	str += bitset<8>(_char).to_string();
	//}

	//cout << str << endl;

	//fileOutput2.close();
	system("pause");
	return 0;
}


