#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <cpr/cpr.h>

#include "server.hpp"

Server::Server(int port, size_t capacity)
    : port(port), cache(capacity) {}

void Server::run() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed\n";
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        close(server_fd);
        return;
    }

    if (listen(server_fd, 5) < 0) {
        std::cerr << "Listen failed\n";
        close(server_fd);
        return;
    }

    std::cout << "Server listening on port " << port << "...\n";

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            std::cerr << "Accept failed\n";
            continue;
        }
	std::thread([this, client_fd]() {
        	handleClient(client_fd);
        	close(client_fd);
	}).detach();
    }

    close(server_fd);
}

void Server::handleClient(int client_fd) {
    char buffer[4096];
    int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read <= 0) return;

    buffer[bytes_read] = '\0';
    std::string request(buffer);

    // Very simple GET parsing
    size_t pos1 = request.find("GET ");
    size_t pos2 = request.find(" HTTP");
    if (pos1 == std::string::npos || pos2 == std::string::npos) return;
    std::string url = request.substr(pos1 + 4, pos2 - (pos1 + 4));

    // Check cache
    CachedObject cached;
    {
    	std::lock_guard<std::mutex> lock(cache_mutex);
    	cached = cache.get(url);
    }

    if (cached.getStatus() == CachedObject::Status::HIT) {
        std::cout << "[CACHE HIT] " << url << "\n";
    } else {
        std::cout << "[CACHE MISS] " << url << "\n";
        cached = fetchFromServer(url);
    	{
		std::lock_guard<std::mutex> lock(cache_mutex);
        	cache.put(url, cached);
	}
    }

    // Send response
    std::string response =
        "HTTP/1.1 200 OK\r\nContent-Length: " +
        std::to_string(cached.getBody().size()) +
        "\r\nContent-Type:" + cached.getContentType() + "\r\n\r\n" +
        cached.getBody();

    send(client_fd, response.c_str(), response.size(), 0);
}

CachedObject Server::fetchFromServer(const std::string& url) {
    auto response =  cpr::Get(cpr::Url{url});
    return CachedObject(response.header["content-type"], response.text, CachedObject::Status::HIT);
}
