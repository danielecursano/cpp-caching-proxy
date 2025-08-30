#include "server.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <cache_capacity>\n";
        return 1;
    }

    int port = std::atoi(argv[1]);
    int cache_capacity = std::atoi(argv[2]);

    Server proxyServer(port, cache_capacity);
    proxyServer.run();
    return 0;
}
