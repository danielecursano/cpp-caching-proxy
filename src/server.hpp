#include "cache.hpp"

class Server {

	public:
		Server(int port, size_t capacity);

		void run();

	private:
		int port;
		LRUCache cache;

		void handleClient(int client_fd);
		std::string fetchFromServer(const std::string& url);
};
