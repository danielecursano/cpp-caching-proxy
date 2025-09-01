#include <mutex>

#include "cache.hpp"
#include "cached_object.hpp"

class Server {

	public:
		Server(int port, size_t capacity);

		void run();

	private:
		int port;
		LRUCache cache;
		std::mutex cache_mutex;

		void handleClient(int client_fd);
		CachedObject fetchFromServer(const std::string& url);
};
