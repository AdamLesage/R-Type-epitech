cmake_minimum_required(VERSION 3.10)

# Détecter l'OS
if(WIN32)
    message(STATUS "Building for Windows")
elseif(UNIX)
    message(STATUS "Building for Linux")
else()
    message(FATAL_ERROR "Unsupported OS")
endif()

# Explicitly use the VCPKG toolchain
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
    message(STATUS "Using VCPKG toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project(r-type)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    # Spécificités pour Windows
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4") # Utiliser les flags MSVC pour Windows
    add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7 target, modifier selon besoin
    
    # Ignorer tous les warnings sous Windows
    add_compile_options(/w)  # /w désactive tous les warnings pour MSVC
else()
    # Spécificités pour Linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")
endif()

# Force Boost to be found via vcpkg
find_package(Boost 1.70 REQUIRED COMPONENTS system asio)
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

# Find and configure libconfig++
if(WIN32)
    # Sous Windows, libconfig++ utilise des noms de cibles légèrement différents
    find_package(libconfig CONFIG REQUIRED)
    if (libconfig_FOUND)
        message(STATUS "libconfig++ found: ${libconfig_INCLUDE_DIRS}")
        include_directories(${libconfig_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "libconfig++ not found!")
    endif()
else()
    # Sous Linux, utilise la configuration standard de libconfig++
    find_package(libconfig++ CONFIG REQUIRED)
    if (libconfig++_FOUND)
        message(STATUS "libconfig++ found: ${libconfig_INCLUDE_DIRS}")
        include_directories(${libconfig_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "libconfig++ not found!")
    endif()
endif()

# Gestion des chemins de bibliothèque pour chaque OS
if(WIN32)
    # Sous Windows, on génère des bibliothèques en .dll
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    message(STATUS "Configuring DLL output for Windows")
else()
    # Sous Unix, on génère des bibliothèques en .so
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    set(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()

# Add sources and create libraries and executables
file(GLOB_RECURSE SRC_CLIENT "../src/client/*.cpp" "../src/shared/*.cpp")
file(GLOB_RECURSE SRC_SERVER "../src/server/*.cpp" "../src/shared/*.cpp")

# Create shared libraries
add_library(NetworkEngine SHARED ${SRC_CLIENT})
add_library(GameEngine SHARED ${SRC_CLIENT})
add_library(PhysicEngine SHARED ${SRC_CLIENT})
add_library(AudioEngine SHARED ${SRC_CLIENT})
add_library(RenderingEngine SHARED ${SRC_CLIENT})

# Ensure all necessary libraries are linked correctly
target_link_libraries(NetworkEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
target_link_libraries(GameEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
target_link_libraries(PhysicEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
target_link_libraries(AudioEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
target_link_libraries(RenderingEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)

# Create the client executable
add_executable(r-type_client ${SRC_CLIENT})

# Link SFML, Boost, and libconfig to the client
target_link_libraries(r-type_client NetworkEngine GameEngine PhysicEngine AudioEngine RenderingEngine ${Boost_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio libconfig::libconfig++)

# Create the server executable
add_executable(r-type_server ${SRC_SERVER})

# Link SFML, Boost, and libconfig to the server
target_link_libraries(r-type_server NetworkEngine GameEngine PhysicEngine AudioEngine RenderingEngine ${Boost_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio libconfig::libconfig++)
