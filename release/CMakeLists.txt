# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(r-type)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")

# Use VCPKG toolchain if available
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
    message(STATUS "Using VCPKG toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Find and configure Boost (use COMPONENTS asio if needed)
find_package(Boost 1.70 REQUIRED COMPONENTS system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Find and configure SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    message(STATUS "SFML found: ${SFML_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "SFML not found!")
endif()

# Recursively find source files for each binary
file(GLOB_RECURSE SRC_CLIENT "../src/client/*.cpp" "../src/shared/*.cpp")
file(GLOB_RECURSE SRC_SERVER "../src/server/*.cpp" "../src/shared/*.cpp")

# Create shared libraries
add_library(NetworkEngine SHARED ${SRC_CLIENT})
add_library(GameEngine SHARED ${SRC_CLIENT})
add_library(PhysicEngine SHARED ${SRC_CLIENT})
add_library(AudioEngine SHARED ${SRC_CLIENT})
add_library(RenderingEngine SHARED ${SRC_CLIENT})

# Link libraries and dependencies
target_link_libraries(GameEngine sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lconfig++ ${Boost_LIBRARIES})
target_link_libraries(RenderingEngine sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES})

# Create the client executable
add_executable(r-type_client ${SRC_CLIENT})

# Linkage for SFML and Boost libraries
target_link_libraries(r-type_client sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lconfig++ ${Boost_LIBRARIES})

# Create the server executable
add_executable(r-type_server ${SRC_SERVER})

# Linkage for SFML and Boost libraries
target_link_libraries(r-type_server sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES})
