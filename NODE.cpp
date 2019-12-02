#include "NODE.h"

Node * getNode(char ch, int freq, Node * left, Node * right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

void encode(Node * root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// là node lá
	if (!root->left && !root->right) 
	{
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode); // qua trái thì thêm 0
	encode(root->right, str + "1", huffmanCode); // qua phải thêm 1
}

void decode(Node * root, int & index, string str)
{
	ofstream out("huffman(Giainen).txt");

	{
		if (root == nullptr) {
			return;
		}

		// là node lá
		if (!root->left && !root->right)
		{
			cout << root->ch;
			out.write(&root->ch, sizeof(char));

			return;
		}

		index++;

		if (str[index] == '0') // nếu 0 thì qua trái
			decode(root->left, index, str);
		else // nếu 1 thì qua phải
			decode(root->right, index, str);
	}
}

void WriteToFile(string FileName, unordered_map<char, string> huffmanCode, string s)
{
	ofstream fileOutput;
	fileOutput.open(FileName);

	if (fileOutput.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}

	// Ghi mã vào file
	string str = "";
	for (char ch : s)
	{
		str += huffmanCode[ch];
	}

	while ((int)str.length() > 8)
	{
		string byte = str.substr(0, 8);
		bitset<8> set(byte);
		const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
		fileOutput.write(&toWrite, sizeof(char));
		str = str.substr(8, str.length() - 8);
	}

	fileOutput.close();

}

void buildHuffmanTree(string fileName)
{

	ifstream fileInput;
	fileInput.open(fileName);
	string s;

	if (fileInput.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}
	while (!fileInput.eof()) {

		char c;
		fileInput.get(c); //đọc từng kí tự
		s += c;
	}


	fileInput.close();

	// đếm tần suất mỗi ký tự
	unordered_map<char, int> freq;
	for (char ch : s)
	{
		freq[ch]++;
	}

	// Tạo hàng đợi ưu tiên để lưu trực tiếp các node của cây Huffman
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Tạo node lá cho mỗi ký tự và thêm nó vào hàng đợi ưu tiên 
	for (auto pair : freq) 
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// làm cho đến khi có nhiều hơn một nút trong hàng đợi
	while (pq.size() != 1)
	{
		// Xóa 2 nút có độ ưu tiên cao nhất (tần suất thấp nhất) từ hàng đợi
		Node *left = pq.top();
		pq.pop();

		Node *right = pq.top();	
		pq.pop();

		// Tạo một nút nội bộ mới với hai nút này như 1 nút con
		//  và có tần số bằng tổng tần số của hai nút.
		//Thêm nút mới vào hàng đợi ưu tiên.

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root lưu trữ con trỏ đến root của Huffman Tree
	Node* root = pq.top();

	// duyệt cây Huffman và lưu trữ mã Huffman
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';

	for (auto pair : huffmanCode) 
	{
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << s << '\n';


	WriteToFile("huffman.txt", huffmanCode, s); // ghi vào file
	

	fstream fileOutput2;
	fileOutput2.open("huffman.txt");

	if (fileOutput2.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}

	string cc = "";
	while (!fileOutput2.eof()) {

		char c;
		fileOutput2.get(c); //đọc từng kí tự
		cc += c;
	}


	fileOutput2.close();

	string str2 = "";
	for (char& _char : cc) {
		str2 += bitset<8>(_char).to_string();
	}

	// Duyệt cây và giải mã
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str2.size() - 2)
 {
		decode(root, index, str2);
	}
}
