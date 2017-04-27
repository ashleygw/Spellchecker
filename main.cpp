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

//The source for this is all over the place, code was adapted from the Competitive Programmers handbook, sampled from wikipedia.
size_t distance(string string1, size_t lenstring1, string string2, size_t lenstring2)
{
	size_t i, j, temp;
	int wizard[100][100];
	//Builds two dimentional array with each letter representing a number based on how far along in the word it is
	// abc,bob = [[0,1,2],[1,0,0],[2,0,0]]
	for (i = 0; i <= lenstring1; i++)
		wizard[0][i] = i;
	for (j = 0; j <= lenstring2; j++)
		wizard[j][0] = j;

	//Walks through the array, always selecting the minimum path.
	//Recursive implementation was slow enough to warrent for loops.
	for (j = 1; j <= lenstring1; j++)
	{
		for (i = 1; i <= lenstring2; i++)
		{
			temp = MIN((wizard[i - 1][j] + 1), (wizard[i][j - 1] + 1));
			wizard[i][j] = MIN(temp, (wizard[i - 1][j - 1] + (string1[i - 1] == string2[j - 1] ? 0 : 1)));
		}
	}
	return wizard[lenstring2][lenstring1];
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
//Debugging purposes
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

vector<string> generate_n_candidates(string input, size_t len, unordered_map<string, string> &words, int go)
{
	vector<string> ret;
	vector<string> tempo;
	if (!go)
		return ret;
	//considering why I wouldn't always use this method. Iterating over the entire hash is really fast.
	// TODO, consider making this recursive as well, insert this list for bigger numbers, rebuild 
	// using the below method for when go <= 2.
	if (/*go >= 3*/1)
	{
		for (auto i = words.begin(); i != words.end(); ++i) {
			if (distance(input, len, i->first, i->first.length()) == go)
			{
				ret.push_back(i->first);
			}
		}
		tempo = generate_n_candidates(input, input.length(), words, go - 1);
		ret.reserve(ret.size() + tempo.size());
		ret.insert(ret.begin(), tempo.begin(), tempo.end());

		std::sort(ret.begin(), ret.end());
		ret.erase(std::unique(ret.begin(), ret.end()), ret.end());
		return ret;
	}

	//The above could literally be the whole function. It think it is even faster and takes up less memory.
	//What is below works just fine. It generates every iteration based on word distance though, and it takes up too 
	//much memory for when the distance is greater than or equal to 3. A hybrid of the two methods was tested,
	//it isn't worth implementing because it isn't any faster, even with this huge dictionary. 

	//al may not be needed, everything should be doable with ret and tempo. He exists for the same reason as museums.
	vector<string> al;
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
			if (go != 1) {
				al.push_back(input);
			}
			else if (words.find(input) != words.end()) {
				ret.push_back(input);
			}
		}
	}
	//Swap Keys
	for (i = 0; i < len - 1; i++)
	{
		input = original;
		temp = input[i + 1];
		input[i + 1] = input[i];
		input[i] = temp;
		if (go != 1) {
			al.push_back(input);
		}
		else if (words.find(input) != words.end()) {
			ret.push_back(input);
		}
	}
	//Insertion error
	for (i = 0; i < len; i++)
	{
		input = original;
		input.erase(i, 1);
		if (go != 1) {
			al.push_back(input);
		}
		else if (words.find(input) != words.end()) {
			ret.push_back(input);
		}
	}
	//Deletion error
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < 26; j++)
		{
			input = original;
			input.insert(i, 1, j + 'a');
			if (go != 1) {
				al.push_back(input);
			}
			else if (words.find(input) != words.end()) {
				ret.push_back(input);
			}
		}
	}
	int size_of_al = al.size();
	if (go != 1) {
		for (int b = 0; b < size_of_al; b++)
		{
			tempo = generate_n_candidates(al[b], al[b].length(), words, go - 1);
			ret.reserve(ret.size() + tempo.size());
			ret.insert(ret.begin(), tempo.begin(), tempo.end());
		}
		std::sort(ret.begin(), ret.end());
		ret.erase(std::unique(ret.begin(), ret.end()), ret.end());
		return ret;
	}
	else {
		return ret;
	}
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
	vector<string> double_candidates;
	string temp;
	size_t lenstring1, lenstring2;
	string string1,string2;
	string desired_distance;
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
		if (string1.length() == 0)
			exit(0);
		lenstring1 = string1.length();
		string1 = to_lowercase(string1, lenstring1);
		if (words.find(string1) != words.end())
			cout << string1 << " is a valid word." << endl;
		else
		{ 
			cout << "Enter desired distance: " << endl;
			getline(cin, desired_distance);
			cout << "Two edit suggestions: " << endl;
			double_candidates = generate_n_candidates((string)string1, lenstring1, words, stoi(desired_distance));
			for (int q = 0; q < double_candidates.size(); q++)
				cout << double_candidates[q] << endl;
			cout << string1 << " is not valid." << endl;
			candidates = generate_candidates(string1, lenstring1, words);
			if (candidates.empty()) {
				cout << "There were no suitable one-edit suggestions. " << endl;
			}
			else {
				cout << "Suggestions: " << endl;
				print_map(candidates);
			}
		}
		//std::cout << distance(string1, lenstring1, string2, lenstring2) << std::endl;
	}
}