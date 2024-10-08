# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(r-type_tests)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")

# Find and configure Boost
find_package(Boost 1.70 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Find and configure SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

# Recursively find source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

# Exclude client and server main.cpp files
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/../src/client/main.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/../src/server/main_server.cpp")

# Recursively find test files
file(GLOB_RECURSE TEST_SOURCES "client/*.cpp")

# Create an executable for the tests
add_executable(tests_client ${TEST_SOURCES} ${SRC_FILES})

# Link libraries and dependencies
target_link_libraries(tests_client sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} criterion -lconfig++)

# Enable testing
enable_testing()

# Add a command to run the tests
add_test(NAME run_tests_client COMMAND tests_client)
