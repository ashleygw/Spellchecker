//#ifndef STRINGHASH_H
//#define STRINGHASH_H
//template <typename K, typename V, typename H>
//class HashMap { // map interface
//public:	// public types
//
//	typedef Entry<const K, V> Entry; // a (key,value) pair
//
//	class Iterator; // a iterator/position
//
//public: // public functions
//
//	stringhash(int capacity = 100); // constructor
//
//	int size() const; // number of entries
//
//	bool empty() const; // is the map empty?
//
//	Iterator find(const K& k); // find entry with key k
//
//	Iterator put(const K& k, const V& v); // insert/replace (k,v)
//
//	void erase(const K& k); // remove entry with key k
//
//	void erase(const Iterator& p); // erase entry at p
//
//	Iterator begin(); // iterator to first entry
//
//	Iterator end(); // iterator to end entry
//
//protected: // protected types
//
//	typedef std::list<Entry> Bucket; // a bucket of entries
//
//	typedef std::vector<Bucket> BktArray; // a bucket array
//
//	Iterator finder(const K& k); // find utility
//
//	Iterator inserter(const Iterator& p, const Entry& e); // insert utility
//
//	void eraser(const Iterator& p); // remove utility
//
//	typedef typename BktArray::iterator BItor; // bucket iterator
//
//	typedef typename Bucket::iterator EItor; // entry iterator
//
//	static void nextEntry(Iterator& p) // bucket�fs next entry
//	{
//		++p.ent;
//	}
//	static bool endOfBkt(const Iterator& p) // end of bucket?
//	{//		return p.ent == p.bkt ? > end();//	}//	// . . .insert HashMap utilities here
//
//private:
//
//	int n; // number of entries
//
//	H hash; // the hash comparator
//
//	BktArray B; // bucket array
//
//	unsigned _size;
//
//public: // public types
//
//	class Iterator { // an iterator (& position)
//
//	private:
//		EItor ent; // which entry
//		BItor bkt; // which bucket
//		const BktArray* ba; // which bucket array
//
//	public:
//		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor()) : ent(q), bkt(b), ba(&a) { }Entry& operator*() const; // get entry
//
//		bool operator==(const Iterator& p) const; // are iterators equal?
//
//		Iterator& operator++(); // advance to next entry
//
//		friend class HashMap; // give HashMap access
//
//	};//};
//#endif
