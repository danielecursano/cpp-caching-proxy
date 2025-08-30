# LRU HTTP Caching Proxy

A simple **HTTP caching proxy** implemented in C++ using an **LRU cache**.

This project demonstrates a basic proxy server that caches web pages to reduce repeated requests to the same URLs.


## Features

* LRU (Least Recently Used) cache for storing web page content
* Caches HTML, CSS, JS, and other text-based resources
* Handles multiple GET requests sequentially
* Simple HTTP server implementation using POSIX sockets
* Uses [CPR](https://github.com/libcpr/cpr) for fetching content from upstream servers


## TODO

- Make the server multi-threaded to handle multiple clients simultaneously.
- Detect and return the correct Content-Type for HTML, CSS, JS, and other resources.


## Requirements

* C++17 or newer
* [CPR](https://github.com/libcpr/cpr) library installed
* POSIX-compatible OS (tested on macOS)


## Building

```bash
mkdir build && cd build 
cmake ..
make
```

This builds the proxy executable in `build/bin/proxy`.

## Usage

1. Start the proxy on a port with a specified cache capacity:

```bash
./build/bin/proxy <port> <cache_capacity>
```

2. Configure your browser or `curl` to use the proxy:

```bash
curl -x http://localhost:<port> http://example.com/
```

3. The proxy logs cache hits and misses to the console:

```
[CACHE MISS] http://example.com/
[CACHE HIT] http://example.com/
```
