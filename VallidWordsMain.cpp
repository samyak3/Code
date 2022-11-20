#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
static const int maxWordsCount = 100000;
static const int ValidCharsCount = 10;
static const int maxWordLength = 10;
static const int minWordLength = 6;
static const int queryCount = 100;
extern void init(const int N, const string words[maxWordsCount]);
extern int query(const string& validChars);
extern void initBruteForce(const int N, const string words[]);
extern int queryBruteForce(const string& validChars);
string words[maxWordsCount];
string validChars;
void generateWords()
{
	for (int wc = 1; wc <= maxWordsCount; wc++)
	{
		int len = minWordLength + rand()%(maxWordLength - minWordLength);
		string str;
		for (int l = 1; l <= len; l++)
			str.push_back('a' + rand() % 26);
		words[wc - 1] = str;
	}	
}

void generateValidChars(int len)
{
	validChars.clear();
	for (int cc = 1; cc <= len; cc++)
		validChars.push_back('a' + rand() % 26);

}
int main()
{
	generateWords();
	init(maxWordsCount, words);
	initBruteForce(maxWordsCount, words);
	for (int q = 1; q <= queryCount; q++)
	{
		int len = max(10, rand() % 27);
		generateValidChars(len);
		int validWords = query(validChars);
		cout << len <<" :: "<<validWords << " " << queryBruteForce(validChars) << endl;
	}
}