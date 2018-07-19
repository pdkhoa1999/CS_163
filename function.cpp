#include "Header.h"
StopWordChaining sw;
void wordTrie::add(string path)
{

	ifstream fin;
	fin.open(path);
	if (fin)
	{
		int count=0;
		while (!fin.eof())
		{
			wordNode* cur = NULL;
			int n = 0;
			string word = takeWord(fin, n);

			if (!sw.isStopWord(word)) {
				if (word[0] > 0) {
					if (root == NULL) root = new wordNode;
					cur = root;
					for (int i = 0; i < n; i++)
					{

						char x = tolower(word[i]);
						if ((x - 'a' >= 26 || x - 'a' < 0) && (x < 48 || x>57) && x != '#'&&x != '$')//if not alphabet ->break
							break;
						if (x == '#')
						{
							if (cur->children[36] == NULL)
							{
								cur->children[36] = new wordNode;
							}
							cur = cur->children[36];
						}
						else if (x == '$')
						{
							if (cur->children[37] == NULL)
							{
								cur->children[37] = new wordNode;
							}
							cur = cur->children[37];
						}
						else if (x >= 48 && x <= 57)
						{
							if (cur->children[x - 22] == NULL)
							{
								cur->children[x - 22] = new wordNode;
							}
							cur = cur->children[x - 22];
						}
						else if (x > 57)
						{
							if (cur->children[x - 'a'] == NULL)
							{
								cur->children[x - 'a'] = new wordNode;
							}
							cur = cur->children[x - 'a'];
						}
					}
					if (cur->phead == NULL)//create first data node for the word
					{
						cur->phead = new pathNode;
						cur->phead->pos[0] = count;
						cur->phead->occurance++;
						cur->phead->path = path;
						cur->phead->pnext = NULL;
						cur->n++;
					}
					else
					{
						pathNode*curpath = cur->phead;
						while (curpath->pnext != NULL && curpath->path != path)//create nodes after the first node
						{
							curpath = curpath->pnext;
						}
						if (curpath->path == path)//the file already in the data
						{
							curpath->pos[curpath->occurance] = count;
							curpath->occurance++;
						}
						else
						{
							curpath->pnext = new pathNode;//new file
							curpath = curpath->pnext;
							curpath->path = path;
							curpath->pos[0] = count;
							curpath->occurance++;
							curpath->pnext = NULL;
							cur->n++;
						}

					}
					count++;
				}
			}
		}
	}
	fin.close();
}
bool checkValidation(char x)
{
	if ((x>64 && x<91) || (x>96 && x<123) || (x >= 48 && x <= 57) || x == '$' || x == '#')
		return true;
	return false;
}
string wordTrie::takeWord(ifstream &fin, int &n)
{
	string word, w;
	char x;
	fin >> x;
	while (!checkValidation(x) && fin)fin >> x;
	fin >> word;
	w += x;
	word.insert(0, w);
	n = word.length();
	for (int i = 0; i < n; i++)
	{
		if (!checkValidation(word[i]))
		{
			word.erase(i, n);
			n = i;
		}
	}
	return word;
}



void wordTrie::printInternal(wordNode*root, string word)
{
	if (root->phead != NULL)
	{
		cout << word << "-" << root->n << "-";
		pathNode *cur = root->phead;
		while (cur != NULL)
		{
			cout << cur->path << "," << cur->occurance ;
			for (int i = 0; i < cur->occurance; i++)
			{
				cout << "," << cur->pos[i];
			}
			cout << ";";
			cur = cur->pnext;
		}
		cout << endl;
	}
	for (int i = 0; i < 38; i++)
	{
		if (root->children[i] != NULL)
		{
			if (i == 37) word += '$';
			else if (i == 36) word += '#';
			else if (i >= 26 && i <= 35)word += i + 22;
			else word += 'a' + i;
			printInternal(root->children[i], word);
			word.pop_back();
		}
	}
}
void wordTrie::print()
{
	string word;
	printInternal(root, word);
}
void wordTrie::loadwordFile(string path)
{
	ifstream fin;
	fin.open(path);
	if (fin)
	{
		while (!fin.eof())
		{
			string word;
			getline(fin, word, '-');
			wordNode* cur = NULL;
			int n = word.length();
			if (root == NULL) root = new wordNode;
			cur = root;
			for (int i = 0; i < n; i++)
			{

				char x = tolower(word[i]);
				if ((x - 'a' >= 26 || x - 'a' < 0) && (x < 48 || x>57) && x != '#'&&x != '$')//if not alphabet ->break
					break;
				if (x == '#')
				{
					if (cur->children[36] == NULL)
					{
						cur->children[36] = new wordNode;
					}
					cur = cur->children[36];
				}
				else if (x == '$')
				{
					if (cur->children[37] == NULL)
					{
						cur->children[37] = new wordNode;
					}
					cur = cur->children[37];
				}
				else if (x >= 48 && x <= 57)
				{
					if (cur->children[x - 22] == NULL)
					{
						cur->children[x - 22] = new wordNode;
					}
					cur = cur->children[x - 22];
				}
				else if (x > 57) {
					if (cur->children[x - 'a'] == NULL)
					{
						cur->children[x - 'a'] = new wordNode;
					}
					cur = cur->children[x - 'a'];
				}
			}
			fin >> cur->n;
			pathNode*curpath = NULL;
			for (int i = 0; i < cur->n; i++)
			{
				int x;
				fin.ignore();
				getline(fin, path, ',');
				fin >> x;
				if (cur->phead == NULL)//create first data node for the word
				{
					cur->phead = new pathNode;
					curpath = cur->phead;
					cur->phead->occurance += x;
					for (int i = 0; i < x; i++)
					{
						fin.ignore(1);
						fin >> curpath->pos[i];

					}
					cur->phead->path = path;
					cur->phead->pnext = NULL;
				}
				else
				{
					curpath->pnext = new pathNode;
					curpath = curpath->pnext;
					curpath->occurance += x;
					for (int i = 0; i < x; i++)
					{
						fin.ignore(1);
						fin >> curpath->pos[i];

					}
					curpath->path = path;
					curpath->pnext = NULL;


				}
			}
			fin.ignore(2);
		}
	}
	fin.close();
}
void wordTrie::saveInternal(ofstream &fout, wordNode*root, string word) {

	if (fout)
	{
		if (root->phead != NULL)
		{
			fout << word << "-" << root->n << "-";
			pathNode*cur = root->phead;
			while (cur != NULL)
			{
				fout << cur->path << "," << cur->occurance;
				for (int i = 0; i < cur->occurance; i++)
				{
					fout << "," << cur->pos[i];
				}
				fout << ";";
				cur = cur->pnext;
			}
			fout << endl;
		}
		for (int i = 0; i < 38; i++)
		{
			if (root->children[i] != NULL)
			{
				if (i == 37) word += '$';
				else if (i == 36) word += '#';
				else if (i >= 26 && i <= 35)word += i + 22;
				else word += 'a' + i;
				saveInternal(fout, root->children[i], word);
				word.pop_back();
			}
		}
	}
}
void wordTrie::savewordFile()
{
	ofstream fout;
	fout.open("word.txt");
	string m;
	saveInternal(fout, root, m);
	fout.close();
}
bool wordTrie::search(string s, wordNode *root)
{
	int i = 0;
	wordNode * cur = root;
	char x;
	//function filter 
	while (checkValidation(s[i]) && i<s.length())
	{
		if (cur == NULL)return false;
		x = tolower(s[i]);
		cur = cur->children[s[i] - 'a'];
		i++;
		if (cur != NULL && i == s.length() && cur->phead != NULL)return true;
	}
	return false;
}
wordNode* wordTrie::Findword(string s)
{
	return Findword(s, root);
}
wordNode* wordTrie::Findword(string s, wordNode * root)
{
	int i = 0;
	wordNode * cur = root;
	char x;
	//function filter 
	while (checkValidation(s[i]) && i<s.length())
	{
		if (cur == NULL)return NULL;
		x = tolower(s[i]);
		cur = cur->children[s[i] - 'a'];
		i++;
		if (cur != NULL && i == s.length() && cur->phead != NULL)return cur;
	}
	return NULL;
}

void LinkedList::InsertWords(string s, Node *&cur)
{
	if (cur == NULL)
	{
		cur = new Node;
		cur->s = s;
		return;
	}
	else return InsertWords(s, cur->next);
}
void LinkedList::RunInsertWords(string s)
{
	InsertWords(s, head);
}
StopWordChaining::StopWordChaining()
{
	ifstream fin;

	fin.open("Stopwords.txt");
	if (!fin.good())
	{
		cout << " Stopword.txt ERROR!!";
		exit(1);
	}
	while (!fin.eof())
	{
		string s;
		getline(fin, s, '\n');
		arr[HashWord(s)].RunInsertWords(s);
	}


	fin.close();
	return;
}
int StopWordChaining::HashWord(string s)
{
	int t = s.length(), index = 0;
	for (int i = 0; i<t; i++)
	{
		index += s[i];
	}
	index = index % 419;

	return index;
}
bool StopWordChaining::isStopWord(string s)
{
	if (arr[HashWord(s)].RunFindWord(s) != NULL) return true;


	return false;
}
Node* LinkedList::FindWord(string s, Node*cur)
{
	if (cur == NULL) return NULL;
	if (StringCompare(s, cur->s))
	{
		return cur;
	}
	else return FindWord(s, cur->next);
}

Node* LinkedList::RunFindWord(string s)
{
	ToLower(s);
	return FindWord(s, head);

}

bool StringCompare(string s1, string s2)
{

	for (int i = 0; i < s1.size(); i++)
		s1[i] = toupper(s1[i]);

	for (int i = 0; i < s2.size(); i++)
		s2[i] = toupper(s2[i]);

	if (s1.compare(s2) == 0)
	{
		return true;
	}

	return false;
}
void ToLower(string & s)
{
	for (int i = 0; i < s.length(); i++) tolower(s[i]);
	return;
}

