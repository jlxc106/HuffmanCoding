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
	};

	~HuffmanTree(){};



	//global variables
	int buffer[8]={ 0 };
	node *root=NULL;
	priority_queue<node *,vector<node *> ,OrderByFreq > mypq;
	vector<node *> myvec;
	unsigned int buffer_position;
	int arrayCount=0;

//	string *codeTable =NULL;
//	char *charTable = NULL;



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
	void printConv(ofstream &write_file){
		printConv(root, "", write_file);
		write_file << "\n";
	}

/*
 * Method: printConv
 * Parameters: node *n, string code
 * Description: Access method - print the conversion code
 * Returns: void
 */
	void printConv(node *n, string code, ofstream &write_file){
		if(n->key!= '\0'){
			write_file << n-> key << " " << code << endl;
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
 * Method: getit - access method
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
	}


	void filewrite(string s, ofstream &write_file){
		for(unsigned int i =0; i< s.length(); i++){ // length of string
			writeBuffer(s.at(i), write_file);
		}
	}

	void writeBuffer(char c, ofstream &write_file){ // void? params?
		//look up conversion here
		string temp;
		for(unsigned int i=0; i<myvec.size(); i++){
			if(myvec[i]->key == c)
				temp = myvec[i]->Huffcode;
		}
		for(unsigned int i=0; i<temp.size(); i++){
			if(buffer_position>7){
				//convert buffer to byte and write onto the file
				//reset the buffer
				//reset i
				debuffer(write_file);
				buffer_position=0;
			}
			buffer[buffer_position]= (int)temp[i];
			buffer_position++;
		}
	}

	void debuffer(ofstream &write_file){
		int temp=0;
		for(int i=0; i< 8; i++){
			temp += buffer[i]*pow(2, 7-i);
			buffer[i]=0;
		}
		write_file << char(temp);
	}
};

int main(int argc, char *argv[]){

	HuffmanTree hf;
	string input, output;
	string line;
	ofstream writefile;
	ifstream readfile; // ifstream - stream class to read from files


	if(argc < 3){
		cout << "Enter a file to read from: ";
		cin >> input;
		cout << "Enter a file to write to: ";
		cin >> output;
	}
	else{
		input = argv[1];
		output = argv[2];
	}


	writefile.open(output.c_str());
	readfile.open(input.c_str());	// string1.c_str() converts strings into const char*

	while(getline(readfile, line)){
		hf.readString(line);
	}

	//transfer to priority queue here
	hf.transferDB();

	hf.build();	//build the huffman tree

	hf.printConv(writefile);

	readfile.clear();
	readfile.seekg(0, ios::beg);

	//writes the compressed file
	while(getline(readfile, line)){
		hf.filewrite(line, writefile);
	}

	readfile.close();
	writefile.close();
}
