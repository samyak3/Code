#include<string>
#include<vector>
using namespace std;
void init(const int N, const string words[]);
int query(const string& validChars);

int TW = 0;
struct node
{
	node* child[26];
	bool endOfWord;
	int characterCount;
	char ch;
	int wordCount;
	node()
	{
		endOfWord = false;
		wordCount = 0;
		for (int i = 0; i < 26; i++)
			child[i] = nullptr;
	}
};
node root;
void insert(const string& s)
{
	node* currentNode = &root;
	int charCount[26] = {0};
	for (int i = 1; i <= s.size(); i++)
	{
		int childIndex = s[i - 1] - 'a';
		charCount[childIndex] += 1;
		if (!currentNode->child[childIndex])
		{
			currentNode->child[childIndex] = new node;
			currentNode->child[childIndex]->ch = s[i - 1];
			currentNode->child[childIndex]->characterCount = charCount[childIndex];
		}
		currentNode = currentNode->child[childIndex];		
	}
	currentNode->endOfWord = true;
	currentNode->wordCount += 1;
	TW++;
}
void init(const int N, const string words[])
{
	for (int i = 1; i <= N; i++)
	{
		insert(words[i]);
	}
}
int validCharCount[26];
int validWords = 0;
int validWordsBruteForce = 0;
void traverseTrie(node* root,int level)
{
	for(int i = 0; i < 26; i++)
	{
		if (root->child[i])
		{
			node* next = root->child[i];
			int ch = next->ch;
			int chIndex = ch - 'a';
			if (next->characterCount <= validCharCount[chIndex])
			{
				if (next->endOfWord)
					validWords += next->wordCount;
				traverseTrie(next, level + 1);
			}
		}
	}
}
vector<string>vw;
void initBruteForce(const int N, const string words[])
{
	for (int i = 1; i <= N; i++)
		vw.push_back(words[i - 1]);
}
int queryBruteForce(const string& validChars)
{
	validWordsBruteForce = 0;
	
	for (int i = 0; i < 26; i++)
		validCharCount[i] = 0;
	for (int i = 0; i < validChars.size(); i++)
		validCharCount[validChars[i] - 'a'] += 1;
	for (int i = 0; i < vw.size(); i++)
	{
		int currentCount[26] = { 0 };
		bool isValid = true;
		for (int j = 0; j < vw[i].size(); j++)
		{
			currentCount[vw[i][j] - 'a'] += 1;
			if (currentCount[vw[i][j] -'a'] > validCharCount[vw[i][j] - 'a'])
			{
				isValid = false;
				break;
			}
		}
		if (isValid)
			validWordsBruteForce++;
	}
	return validWordsBruteForce;
}
int query(const string& validChars)
{
	validWords = 0;
	for (int i = 0; i < 26; i++)
		validCharCount[i] = 0;
	for (int i = 0; i < validChars.size(); i++)
	{
		int index = validChars[i] - 'a';
		validCharCount[index] += 1;
	}
	traverseTrie(&root, 0);
	return validWords;
}
