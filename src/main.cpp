#include "server.hpp"

int main() {
    Server proxyServer(8080, 10);
    proxyServer.run();
    return 0;
}
