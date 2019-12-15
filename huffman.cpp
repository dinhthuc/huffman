#include "huffman.h"
Node * getNode(unsigned char ch, unsigned int freq, Node * left, Node * right)
{
	{
		Node* node = new Node();

		node->ch = ch;
		node->freq = freq;
		node->left = left;
		node->right = right;

		return node;
	}
}

void encode(Node* root, string str,	unordered_map<unsigned char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, string str)
{
	ofstream OutputFile2("Decode.txt");
	string ans = "";
	 Node* curr = root;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// là nút lá
		if (curr->left == NULL and curr->right == NULL)
		{
			ans += curr->ch;
			curr = root;
		}
	}
	ans += '\0';
	OutputFile2 << ans;
}

void buildHuffmanTree(string fileName)
{
//----------------------------- mở file text ------------------------------
	ifstream fileInput;
	fileInput.open(fileName);

	string file_contents;

	if (fileInput.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}

	while (!fileInput.eof())
	{
		string s;
		getline(fileInput, s);
		file_contents += s + "\n";
	}

	file_contents.pop_back();
	fileInput.close();


//--------------------- đếm tần suất mỗi ký tự -----------------------
	unordered_map<unsigned char, unsigned int> freq;
	for (unsigned char ch : file_contents)
	{
		freq[ch]++;
	}


	// Tạo hàng đợi ưu tiên để lưu trực tiếp các node của cây Huffman
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Tạo node lá cho mỗi ký tự và thêm nó vào hàng đợi ưu tiên
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// làm cho đến khi có nhiều hơn một nút trong hàng đợi
	while (pq.size() != 1)
	{
		// Xóa 2 nút có độ ưu tiên cao nhất (tần suất thấp nhất) từ hàng đợi
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Tạo một nút nội bộ mới với hai nút này như 1 nút con
		// và có tần số bằng tổng tần số của hai nút.
		// Thêm nút mới vào hàng đợi ưu tiên.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root lưu trữ con trỏ đến root của Huffman Tree
	Node* root = pq.top();

	// duyệt cây Huffman và lưu trữ mã Huffman
	unordered_map<unsigned char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) // xuất bảng mã hóa 
	{
		cout << pair.first << " " << pair.second << '\n';
	}

	// mã hóa thành dãy nhị phân
	string str = "";
	for (unsigned char ch : file_contents)
	{
		str += huffmanCode[ch];
	}

	string str2 = str;
// ---------------------------- mở file nén và nén -------------------------------

	ofstream fileOutput;
	fileOutput.open("Encode.txt");


	if (fileOutput.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}


	//chuyển dãy nhị phân thành chuỗi và lưu vào file nén
	while ((unsigned int)str2.length() >= 8)
	{
		string byte = str2.substr(0, 8);
		bitset<8> set(byte);
		const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
		fileOutput.write(&toWrite, sizeof(unsigned char));
		str2 = str2.substr(8, str2.length() - 8);
	}
	int n;
	n = str2.size();
	//lưu dãy còn dư vào file (xử lý đuôi)
	for (int i = 0; i < n; i++)
	{
		fileOutput.write(&str2[i], sizeof(unsigned char));
	}
	
	fileOutput.close();




//----------------------------- mở file nén và giải nén ------------------------------

	ifstream fileInput2;
	fileInput2.open("Encode.txt");


	if (fileInput2.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}
	string bitStream = "";
	while (!fileInput2.eof())
	{
		string s;
		getline(fileInput2, s);
		bitStream += s + "\n";
	}


	bitStream.pop_back();
	fileInput2.close();

	string str3 = "";
	for (int i = 0; i < bitStream.size() - n; i++)
	{
		str3 += charToBin(bitStream[i]);
	}

	// lấy các phần bit thừa và gán vào chuỗi mói
	for (int i = bitStream.size() - n; i < bitStream.size(); i++)
	{
		str3 += bitStream[i];
	}


// ----------------------  giải nén  --------------------------
	cout << "\n---------------- Decoded string is: ----------------------\n";
	decode(root, str);
}

string charToBin(unsigned char c)
{
	string ch = "";
	for (int i = 7; i >= 0; --i)
	{
		unsigned char s = ((c & (1 << i)) ? '1' : '0');
		ch += s;
	}

	return ch;
}

