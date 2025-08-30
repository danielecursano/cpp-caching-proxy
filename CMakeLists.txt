cmake_minimum_required(VERSION 3.10)
project(proxy_project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(proxy ${SOURCES})

# Find CPR package
find_package(cpr REQUIRED)

# Link libraries
target_link_libraries(proxy PRIVATE cpr::cpr)

# Optional: set output directories
set_target_properties(proxy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

