#ifndef HASH_H
#define HASH_H
#include <string>
using namespace std;

class Hash {

public:

	// Constructor
	Hash(int);

	// Destructor
	~Hash();

	// inserts word into hash
	void insert(string);

	// hash function
	int placement(string);

	// searches for word in hash
	bool search(string);

	// pointer
	string *arr;

	// size of array
	int array_size;

	// number of words in hash
	int current_size;

	// number of collisions
	int collisions;

};


#endif
