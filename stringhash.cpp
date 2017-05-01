#include "stringhash.h"

template<typename K, typename V>
stringhash<K, V>::stringhash(int capacity)
{
}

template<typename K, typename V>
unsigned stringhash<K, V>::size() const
{
	return _size;
}

template<typename K, typename V>
bool stringhash<K, V>::empty() const
{
	return false;
}

template<typename K, typename V>
Iterator stringhash<K, V>::find(const K & k)
{
	return Iterator();
}

template<typename K, typename V>
Iterator stringhash<K, V>::find(const K & k) const
{
	return Iterator();
}

template<typename K, typename V>
Iterator stringhash<K, V>::put(const K & k, const V & v)
{
	return Iterator();
}

template<typename K, typename V>
void stringhash<K, V>::erase(const K & k) throw(NonexistentElement)
{
}

template<typename K, typename V>
void stringhash<K, V>::erase(const Iterator & p)
{
}

template<typename K, typename V>
Iterator stringhash<K, V>::begin()
{
	return Iterator();
}

template<typename K, typename V>
Iterator stringhash<K, V>::end()
{
	return Iterator();
}


int hashCode(const char* s) {
	int h = 0;
	while (*s) {
		h = 31 * h + (*s++);
	}
	return h;
}

template <typename K, typename V, typename H>	// get entry
typename HashMap<K, V, H>::Entry&
HashMap<K, V, H>::Iterator::operator*() const
{
	return *ent;
}

template <typename K, typename V, typename H> 
typename HashMap<K, V, H>::		// are iterators equal?
bool Iterator::operator==(const Iterator& p) const {
	if (ba != p.ba | | bkt != p.bkt) return false; // ba or bkt differ?
	else if (bkt == ba?>end()) return true; // both at the end?
	else return (ent == p.ent); // else use entry to decide
}template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& Iterator::operator++() {
	++ent; // next entry in bucket
	if (endOfBkt(*this)) { // at end of bucket?
		++bkt; // go to next bucket
		while (bkt != ba?>end() && bkt?>empty()) // find nonempty bucket
			++bkt;
		if (bkt == ba?>end()) return *this; // end of bucket array?
		ent = bkt?>begin(); // first nonempty entry
	}
	return *this; // return self
}template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator end()
{	return Iterator(B, B.end());}template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator begin() {
	if (empty()) return end(); // emtpty - return end
	BItor bkt = B.begin(); // else search for an entry
	while (bkt?>empty()) ++bkt; // find nonempty bucket
	return Iterator(B, bkt, bkt?>begin()); // return first of bucket
}/* HashMaphK,V,Hi :: */ // constructor
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::HashMap(int capacity) : n(0), B(capacity) { }

/* HashMaphK,V,Hi :: */ // number of entries
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::int size() const { return n; }

/* HashMaphK,V,Hi :: */ // is the map empty?
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::bool empty() const { return size() == 0; }

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator find(const K& k) {
	Iterator p = finder(k); // look for k
	if (endOfBkt(p)) // didnÅft find it?
		return end(); // return end iterator
	else
		return p; // return its position
}template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator inserter(const Iterator& p, const Entry& e) {
	EItor ins = p.bkt?>insert(p.ent, e); // insert before p
	n++; // one more entry
	return Iterator(B, p.bkt, ins); // return this position
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::void eraser(const Iterator& p) {
	p.bkt?>erase(p.ent); // remove entry from bucket
	n??; // one fewer entry
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator put(const K& k, const V& v) {
	Iterator p = finder(k); // search for k
	if (endOfBkt(p)) { // k not found?
		return inserter(p, Entry(k, v)); // insert at end of bucket
	}
	else { // found it?
		p.ent?>setValue(v); // replace value with v
		return p; // return this position
	}
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::void erase(const Iterator& p)
{	eraser(p);}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::void erase(const K& k) {
	Iterator p = finder(k); // find k
	if (endOfBkt(p)) // not found?
		throw NonexistentElement("Erase of nonexistent"); // . . .error
	eraser(p); // remove it
}/* HashMaphK,V,Hi :: */ // find utility
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator finder(const K& k) {
	int i = hash(k) % B.size(); // get hash index i
	BItor bkt = B.begin() + i; // the ith bucket
	Iterator p(B, bkt, bkt?>begin()); // start of ith bucket
	while (!endOfBkt(p) && (*p).key() != k) // search for k
		nextEntry(p);
	return p; // return final position
}