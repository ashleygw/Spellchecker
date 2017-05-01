template <typename K, typename V, typename H> // get entry
typename HashMap<K, V, H>::Entry&
HashMap<K, V, H>::Iterator::operator*() const
{	return *ent;}