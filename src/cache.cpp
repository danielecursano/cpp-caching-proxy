#include "cache.hpp"

LRUCache::LRUCache(size_t capacity) : capacity(capacity) {

}

CachedObject LRUCache::get(const std::string& url) {
	auto it = memory.find(url);
	if (it == memory.end()) {
		return CachedObject();
	}

	queue.splice(queue.begin(), queue, it->second.first);

	return it->second.second;
}

void LRUCache::put(const std::string& url, const CachedObject& value) {		
	auto it = memory.find(url);

	if (it != memory.end()) {
		it->second.second = value;
		queue.splice(queue.begin(), queue, it->second.first);
	} else {
		queue.push_front(url);
		memory[url] = { queue.begin(), value };

		if (memory.size() > capacity) {
			const std::string& lru_url = queue.back();
			memory.erase(lru_url);
			queue.pop_back();
		}
	}
}
