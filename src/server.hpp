#include "cache.hpp"
#include "cached_object.hpp"

class Server {

	public:
		Server(int port, size_t capacity);

		void run();

	private:
		int port;
		LRUCache cache;

		void handleClient(int client_fd);
		CachedObject fetchFromServer(const std::string& url);
};
