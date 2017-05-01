#include "Hash.h"
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

// Constructor
Hash::Hash(int _array_size) {
	current_size = 0;
	collisions = 0;
	array_size = _array_size;
	arr = new string[array_size];
	for (int i = 0; i<array_size; i++) {
		arr[i] = "0";
	}
}

// Destructor
Hash::~Hash() {
	delete[] arr;
}

// inserts word into hash
void Hash::insert(string word) {
	current_size++;
	int place = placement(word);
	int count = 0;
	while (arr[place] != "0") {
		place++;
		count++;
		if (place == array_size) {
			place = 0;
		}
	}
	if (count) {
		collisions++;
		//        cout << count << " ";
	}
	arr[place] = word;

}

// hash function
int Hash::placement(string word) {
	int num = 0;

	for (int i = 0; i<word.length(); i++) {
		num += pow(2, word[i] % 18) * word[i] * (i + 1);
	}

	return num % array_size;
}

// search
bool Hash::search(string w) {
	int index = placement(w);
	while (arr[index] != "0") {
		if (arr[index] == w) return true;
		index++;
		if (index == array_size) index = 0;
	}
	return false;
}




