#include <string>
#include <unordered_map>
#include <list>

#include "cached_object.hpp"

class LRUCache {

	using ListNode = std::list<std::string>::iterator;
	using Entry = std::pair<ListNode, CachedObject>;

	public:
		LRUCache(size_t capacity);
		CachedObject get(const std::string& url);
		void put(const std::string& url, const CachedObject& value);

	private:
		size_t capacity;
		std::unordered_map<std::string, Entry> memory;
		std::list<std::string> queue;
};
