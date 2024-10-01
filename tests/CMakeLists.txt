# Minimum version de CMake requise
cmake_minimum_required(VERSION 3.10)

# Project name
project(r-type_tests)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")

# Download and configure Boost
find_package(Boost 1.70 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Download and configure SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

# Recherche récursive des fichiers sources
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

# Exclure les fichiers main.cpp du client et du serveur
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/../src/client/main.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/../src/server/main_server.cpp")

# Recherche récursive des fichiers de test
file(GLOB_RECURSE TEST_SOURCES "client/*.cpp")

# Créer un exécutable pour les tests
add_executable(tests_client ${TEST_SOURCES} ${SRC_FILES})

# Lier les bibliothèques aux dépendances
target_link_libraries(tests_client sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} criterion -lconfig++)

# Activer les tests
enable_testing()

# Ajouter une commande pour exécuter les tests
add_test(NAME run_tests_client COMMAND tests_client)
