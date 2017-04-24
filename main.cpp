#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
#include <algorithm>

#define MIN(x,y) ((x) < (y) ? (x) : (y))
using namespace std;

//The source for this is all over the place. 
size_t distance(string string1, size_t lenstring1, string string2, size_t lenstring2)
{
	size_t i, j, temp;
	int d[100][100];
	//Builds two dimentional array with each letter representing a number based on how far along in the word it is
	// abc,bob = [[0,1,2],[1,0,0],[2,0,0]]
	for (i = 0; i <= lenstring1; i++)
		d[0][i] = i;
	for (j = 0; j <= lenstring2; j++)
		d[j][0] = j;

	//Walks through the array
	for (j = 1; j <= lenstring1; j++)
	{
		for (i = 1; i <= lenstring2; i++)
		{
			temp = MIN((d[i - 1][j] + 1), (d[i][j - 1] + 1));
			d[i][j] = MIN(temp, (d[i - 1][j - 1] + (string1[i - 1] == string2[j - 1] ? 0 : 1)));
		}
	}
	//printf("The Levinstein distance is %d\n", d[lenstring2][lenstring1]);
	return d[lenstring2][lenstring1];
}

string to_lowercase(string input, size_t len) {
	for (int i = 0; i < len; i++)
	{
		if (input[i] <= 'Z' && input[i] >= 'A')
			input[i] -= ('Z' - 'z');
	}
	return input;
}

//http://www.cplusplus.com/reference/unordered_map/unordered_map/begin/
//http://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
void print_map(unordered_map<string, unsigned> &map)
{
	std::vector<std::pair<string, unsigned>> candidates(map.begin(), map.end());
	std::sort(candidates.begin(), candidates.end(), [](auto &left, auto &right) {
		return left.second > right.second;
	});
	for (auto i = candidates.begin(); i != candidates.end(); ++i)
		std::cout << i->first << ": " << i->second << "\n";
	cout << "\n";
}

unordered_map<string, unsigned> generate_candidates(string input, size_t &len, unordered_map<string, string> &words)
{
	unordered_map<string, unsigned> ret;
	string original = input;
	char temp;
	unsigned i = 0;
	unsigned j = 0;
	//Misshit keys
	for (i = 0; i < len; i++)
	{
		input = original;
		for (unsigned j = 0; j < 26; j++)
		{
			input[i] = j + 'a';
			//Save new word to return hash if it is in the dictionary and modify the probability value
			if (words.find(input) != words.end()) {
				ret[input] += 10;
			}
			/*else
			{
				ret[input] += 10; 
			}*/
		}
	}
	//Swap Keys
	for (i = 0; i < len - 1; i++)
	{
		input = original;
		temp = input[i+1];
		input[i + 1] = input[i];
		input[i] = temp;
		if (words.find(input) != words.end()) {
			ret[input] += 40;
		}
	}
	//Insertion error
	for (i = 0; i < len; i++)
	{
		input = original;
		input.erase(i,1);
		if (words.find(input) != words.end()) {
			ret[input] += 20;
		}
	}
	//Deletion error
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < 26; j++)
		{
			input = original;
			input.insert(i, 1, j + 'a');
			if (words.find(input) != words.end()) {
				ret[input] += 5;
			}
		}
	}
	return ret;
}

int main()
{
	unordered_map<string, string> words;
	unordered_map<string, unsigned> candidates;
	string temp;
	size_t lenstring1, lenstring2;
	string string1,string2;
	unsigned max = 100;
	ifstream ifs;
	ifs.open("allwords.txt", ifstream::in);
	if (!ifs)
	{
		cout << "Dictionary File not Loaded. " << endl;
		return 1;
	}
	while (ifs) {
		getline(ifs, temp);
		words[temp] = temp;
	}
	//ifs.close();
	while (1) {
		cout << "Enter a word: ";
		getline(cin, string1);
		if (string1 == "\n")
			exit(0);
		lenstring1 = string1.length();
		string1 = to_lowercase(string1, lenstring1);
		if (words.find(string1) != words.end())
			cout << string1 << " is a valid word." << endl;
		else
		{
			cout << string1 << " is not valid." << endl;
			candidates = generate_candidates(string1, lenstring1, words);
			if (candidates.empty()) {
				cout << "There were no suitable suggestions. \nWould you like to do an extensive search for the closest words? (y/n)" << endl;
				getline(cin, temp);
				if (temp == "y")
				{
					max = 100;
					for (auto i = words.begin(); i != words.end(); ++i){
						if (distance(string1, lenstring1, i->first, i->first.length()) < max)
						{
							temp = i->first;
							max = distance(string1, lenstring1, i->first, i->first.length());
						}
					}
					cout << temp << " is the closest related word with distance " << max << "." << endl;
				}
			}
			else {
				cout << "Suggestions: " << endl;
				print_map(candidates);
			}
		}
		//std::cout << distance(string1, lenstring1, string2, lenstring2) << std::endl;
	}
}
