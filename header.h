#pragma once
#ifndef  _header_h_
#define _header_h_
#include<iostream>
#include<fstream>
#include<string>
#include <ctime>

using namespace std;
struct pathNode {//contain data of a single word
	string path;
	pathNode* pnext;
	int pos[50];
	int occurance;
	pathNode() { occurance = 0; }
};
struct wordNode {//one node in the wordtrie
	pathNode*phead = NULL;
	int n;
	wordNode*children[38] = {};
	wordNode() { n = 0; }


};
struct wordTrie {
private:
	wordNode * root;
	void printInternal(wordNode*root, string word);//test print
	string takeWord(ifstream &fin, int &n);
	void saveInternal(ofstream &fout, wordNode*root, string word);
	wordNode* Findword(string s, wordNode * root);

public:
	void print();//test print
	wordTrie() { root = NULL; }
	void loadwordFile(string path);//load trie from wordfile
	void add(string path);//add a file to wordttrie
	void savewordFile();//save trie to word file
	bool search(string s, wordNode *root);
	wordNode* Findword(string s);


};
bool checkValidation(char x);//check if a valid char or not


							 //Stopword
							 // Stopwords for feature 
struct Node
{
	string s;
	Node *next;
	Node()
	{
		next = NULL;
	}
};
class LinkedList
{
private:
	Node * head;
	void InsertWords(string s, Node *&cur);
	Node* FindWord(string s, Node*cur);
public:
	LinkedList()
	{
		head = NULL;
	}
	void RunInsertWords(string s);
	Node* RunFindWord(string s);
};
struct StopWordChaining
{
private:
	LinkedList arr[420];

public:
	StopWordChaining();
	bool isStopWord(string s);
	int HashWord(string s);
};
void ToLower(string & s);
bool StringCompare(string s1, string s2);
#endif
