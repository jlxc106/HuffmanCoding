/*
 * Huffman.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: jlxc106
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

//node class
struct node{
	int freq;
	string Huffcode;
	char key;
	node *leftchild, *rightchild;

	node(int num){
		freq = num;
		key = '\0';
		rightchild = NULL;
		leftchild = NULL;
		Huffcode = "";
	}

	node(char data, int num, string code){
		freq = num;
		key = data;
		Huffcode = code;
		rightchild=NULL;
		leftchild=NULL;

	}

	node(char data, int num){
		key = data;
		freq = num;
		rightchild = NULL;
		leftchild = NULL;
		Huffcode = "";
	}
};

//comparison class for priority queue
//1) frequency of nodes is first priority
//2) leaves are prioritized over non-leaves(based on key)
struct OrderByFreq
{
	bool operator()(node *L, node *R){
		if(L->freq == R->freq){
			return L->key < R-> key;	//if the case that freq are the same,
										//sort by key(leaves should be prioritized
										//over parents of leaves)
		}
		return (L -> freq > R -> freq);
	}
};

class HuffmanTree{

public:
	HuffmanTree(){
		buffer_position=0;
		root = NULL;
	};

	~HuffmanTree(){};



	//global variables
	int buffer[8]={ 0 };
	node *root;
	priority_queue<node *,vector<node *> ,OrderByFreq > mypq;
	vector<node *> myvec;
	unsigned int buffer_position;
	int arrayCount=0;

	/*
	 * Method: readString
	 * Parameter(s): string s - line from input file
	 * Description: method used to record the number of char in file
	 * Returns: void
	 */
	void readString(string s){
		for(unsigned int i =0; i< s.length(); i++){ // length of string
			readChar(s.at(i));
		}
		readChar(char(3));
	}

	/*
	 * Method: readChar
	 * Parameter(s): char c - individual char that will be recorded
	 * Description: helper method(called in readIt())
	 * 				1)increases the frequency of node containing char or
	 * 				2)adds a new node to vector
	 * Returns: void
	 */
	void readChar(char c){
		node *temp;
		if(myvec.size()==0){	//corner case: 1st node of vector
			temp = new node(c, 1);
			myvec.push_back(temp);
		}
		else{
			for(unsigned int i=0; i < myvec.size(); i++){
				if(myvec[i]->key == c){		//case 1)
					myvec[i]->freq++;
					break;
				}
				else if(myvec[i]->key != c && i == myvec.size()-1){	//case 2
					node *temp = new node(c, 1);
					myvec.push_back(temp);
					break;
				}
			}
		}
	}

	/*
	 * Method: test() - just for testing
	 */
	void test(){
		cout << "myvec.size(): " << myvec.size() << endl;
		for(unsigned int i=0; i< myvec.size(); i++){
			cout<<"i: "<<i<<" frequency: "<<myvec[i]->freq<<" key: "<<myvec[i]->key<<endl;
		}
	}

	/*
	 * Method: transferDB()
	 * Parameter(s): void
	 * Description: transfers nodes from vector to priority queue
	 * 				once all the characters in the file have been counted
	 * Returns: void
	 */
	void transferDB(){
		//size = myvec.size();
		for(unsigned int i=0; i< myvec.size(); i++)
			mypq.push(myvec[i]);
	}
/*
 * Method: poptest() -- just for testing
 */
	void poptest(){
		while(!mypq.empty()){
		cout << mypq.top() -> key << "\t";
		cout << mypq.top() -> freq << endl;
		mypq.pop();
		}
	}

/*
 * Method: build()
 * Parameter(s): void
 * Description: A method to build the Huffman Tree & set to root.
 * Returns: void
 */
	void build(){
		while(mypq.size() > 1){
			node *a = mypq.top();	//left child - 0
			mypq.pop();
			node *b = mypq.top();	//right child - 1
			mypq.pop();
			node *temp = new node(a->freq + b->freq);
			temp -> leftchild = a;
			temp -> rightchild = b;
			mypq.push(temp);
		}
		root = mypq.top();
	}
/*
 * Method: printConv() -- dummy function to call printConv(node, string)
 */
	void printConv(fstream &write_file){
		write_file << myvec.size() <<"\n";
		printConv(root, "", write_file);
		//write_file << "\n";
	}

/*
 * Method: printConv
 * Parameters: node *n, string code
 * Description: Access method - print the conversion code
 * Returns: void
 */
	void printConv(node *n, string code, fstream &write_file){
		if(n->key!= '\0'){
			write_file << n-> key << " " << n->freq << endl;
			n->Huffcode = code;
		}
		if(n->leftchild !=NULL){
			printConv(n->leftchild, code + "0", write_file);
		}
		if(n->rightchild !=NULL){
			printConv(n->rightchild, code + "1", write_file);
		}
	}

/*
 * Method: getit - access method - only for testing
 */
	void getit(){
		cout << "root" << endl;
		cout << root->freq << endl;
		cout << root->key << endl;
		cout << "left child" << endl;
		cout << root -> leftchild -> freq << endl;
		cout << root -> leftchild -> key << endl;
		cout << "right child" << endl;
		cout << root -> rightchild -> freq << endl;
		cout << root -> rightchild -> key << endl;
		cout << "11" <<endl;
		cout << root ->rightchild->rightchild->freq << endl;
		cout << root -> rightchild->rightchild->key<<endl;
	}

/*
 * Method: filewrite
 * Parameter(s): string s, ofstream &write_file - string read from input file
 * 				and reference to our output file.
 * Description: Method used to call writeBuffer multiple times.
 * Returns: void
 */
	void filewrite(string s, fstream &write_file){
		for(unsigned int i =0; i< s.length(); i++){ // length of string
			writeBuffer(s.at(i), write_file);
		}
		writeBuffer((char)3, write_file);
	}

	/*
	 * Method: writeBuffer
	 * Parameter(s): char c, ofstream &write_file - char read from input file
	 * 				and reference to our output file
	 * Description: Method called in filewrite - manages the buffer
	 * Returns: void
	 */
	void writeBuffer(char c, fstream &write_file){ // void? params?
		//look up conversion here
		string temp;
		for(unsigned int i=0; i<myvec.size(); i++){
			if(myvec[i]->key == c)
				temp = myvec[i]->Huffcode;
		}
		for(unsigned int i=0; i<temp.size(); i++){
			if(buffer_position>7){
				debuffer(write_file);
				buffer_position=0;
			}
			buffer[buffer_position]= temp[i]-'0';
			buffer_position++;
		}
		if(c==char(3)){
			debuffer(write_file);
		}
	}
/*
 * Method: debuffer
 * Parameter(s): ofstream& write_file - reference to our output file
 * Description: helper function(called in writeBuffer) - used to clear
 * 				the buffer when the end is reached & writes the output file.
 * Returns: void
 */
	void debuffer(fstream &write_file){
		int temp=0;
		static int aay=0;
//		cout << "run: "<<aay<<endl;
		for(int i=0; i< 8; i++){
//			cout << "buffer[i]: "<< buffer[i]<<endl;
			temp += (buffer[i]*pow(2, (7-i)));
			buffer[i]=0;
		}
//		cout << "temp: " << temp << endl;
		write_file << char(temp);
		aay++;
	}




};

class HuffmanDecode{
public:
	HuffmanDecode(){
		//conv_table = new vector;
		root = NULL;
	};

	~HuffmanDecode(){};
	priority_queue<node*, vector<node*>, OrderByFreq> mypq;
	node *root;
	vector <node*> conv_table;
	int buffer[8]={0};
	int buffer_position=0;

	void build(){
		cout << "mypq.size(): "<<mypq.size() << endl;
		while(mypq.size() > 1){
			node *a = mypq.top();	//left child - 0
			mypq.pop();
			node *b = mypq.top();	//right child - 1
			mypq.pop();
			node *temp = new node(a->freq + b->freq);
			temp -> leftchild = a;
			temp -> rightchild = b;
			mypq.push(temp);
		}
		root = mypq.top();
	}

	/*
	 *
	 *
	 */
	void readtable(string s){
		//node *temp;
		//char c = s[0];
		int freq = 0;
		string conv_code="";
		for(unsigned int i=2; i< s.size(); i++){
			//int a = s[i]-'0';
			freq =freq*10 + (s[i]-'0');
			//conv_code += s[i];
		}
		node *temp = new node(s[0], freq);
		conv_table.push_back(temp);
		mypq.push(temp);
		cout << "c: "<< s[0]<< " freq: " << freq <<endl;
	}

	void decode(string s, fstream &write_file){
		string code;
		node *temp = root;
		for(unsigned int i=0; i<s.size();i++){
			//convert s[i] to int
			unsigned int wut = (unsigned int)(unsigned char)s[i];
//			cout << wut<<endl;
			for(unsigned int j=0; j<8; j++){
				buffer[j]=wut/(pow(2,7-j));
//				cout << "Buffer[j]: "<< buffer[j]<<endl;
				wut = wut % (int)pow(2,7-j);
			}
			for(unsigned int k=0; k<8; k++){
				if(buffer[k]==0){
					//go left
					if(temp->leftchild->key != '\0'){
						if(temp->leftchild->key !=(char)3)
							write_file << temp->leftchild->key;
//						cout << temp->leftchild->key;
						temp = root;
					}
					else
						temp=temp->leftchild;
				}
				else{
					//go right
					if(temp->rightchild->key != '\0'){
						if(temp->rightchild->key!= (char)3)
							write_file << temp->rightchild->key;
//						cout << temp->rightchild->key;
						temp = root;
					}
					else
						temp = temp->rightchild;
				}
			}
			//decode_char(s[i], write_file);
		}
	}

	void getit(){
		cout << "root" << endl;
		cout << root->freq << endl;
		cout << root->key << endl;
		cout << "left child" << endl;
		cout << root -> leftchild -> freq << endl;
		cout << root -> leftchild -> key << endl;
		cout << "right child" << endl;
		cout << root -> rightchild -> freq << endl;
		cout << root -> rightchild -> key << endl;
		cout << "right->right" <<endl;
		cout << root ->rightchild->rightchild->freq << endl;
		cout << root -> rightchild->rightchild->key<<endl;
		cout << "" << endl;
		cout << root ->rightchild->leftchild->freq<<endl;
		cout << root ->rightchild->leftchild->key<<endl;
	}

	void poptest(){
		while(!mypq.empty()){
		cout << mypq.top() -> key << "\t";
		cout << mypq.top() -> freq << endl;
		mypq.pop();
		}
	}
};


int main(int argc, char *argv[]){

	HuffmanTree hf;
	string input="hello.txt", output="hellocompress.txt", new_input="hello_new.txt";
//	string input="big.txt", output="bigcompress.txt", new_input= "big_new.txt";
	string line;
	fstream writefile;
	fstream uncompressfile;	//duplicate file of readfile
	ifstream readfile; // ifstream - stream class to read from files

/*
	if(argc < 4){
		cout << "Enter a file to read from: ";
		cin >> input;
		cout << "Name a compressed file to write to: ";
		cin >> output;
		cout << "Name an uncompressed file to write to: ";
		cin >> new_input;
	}
	else{
		input = argv[1];
		output = argv[2];
		new_input = argv[3];
	}
*/

	writefile.open(output.c_str());
	readfile.open(input.c_str());	// string1.c_str() converts strings into const char*
	uncompressfile.open(new_input.c_str());

	readfile.seekg(0, ios::end);
	int readfile_length = readfile.tellg();
	readfile.seekg(0, ios::beg);

	char *buffer = new char[readfile_length];

	readfile.read(buffer, readfile_length);

	hf.readString((string)buffer);

	//transfer to priority queue here
	hf.transferDB();

	hf.build();	//build the huffman tree


	hf.printConv(writefile);

	//hf.getit();

	readfile.clear();
	readfile.seekg(0, ios::beg);

	hf.filewrite((string)buffer, writefile);

	//writes the compressed file
//	while(getline(readfile, line)){
//		hf.filewrite(line, writefile);
//		writefile << "\n";
//	}

	writefile.clear();
	writefile.seekg(0, ios::beg);

	HuffmanDecode hd;
	//read from the compressed file to make original file from scratch.
	//getline(writefile, line);
	getline(writefile,line);
	int number_lines = atoi(line.c_str());

	for(unsigned int i=0; i<number_lines; i++){
		getline(writefile,line);
		hd.readtable(line);
	}

	//hd.poptest();

	hd.build();

	getline(writefile, line);
	hd.decode(line, uncompressfile);
//	while(getline(writefile,line)){
		//cout << "line: "<<line << endl;
//		hd.decode(line, uncompressfile);
		//uncompressfile <<"\n";
//	}

	//hd.getit();

	uncompressfile.close();
	readfile.close();
	writefile.close();
}
