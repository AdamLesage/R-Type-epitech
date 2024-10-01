# Minimum version de CMake requise
cmake_minimum_required(VERSION 3.10)

# Project name
project(r-type)

# Include CMake modules for FetchContent
include(FetchContent)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

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

# Create shared libs

add_library(NetworkEngine SHARED
    src/client/NetworkEngine/NetworkEngine.cpp
    src/client/NetworkEngine/Client.cpp
)

add_library(GameEngine SHARED
    src/client/GameEngine/GameEngine.cpp
    src/client/GameEngine/ProtocolParsing.cpp
    src/shared/registry/Registry.cpp
    src/shared/systems/Systems.cpp
)

add_library(PhysicEngine SHARED
    src/client/PhysicEngine/PhysicEngine.cpp
)

add_library(AudioEngine SHARED
    src/client/AudioEngine/AudioEngine.cpp
)

target_link_libraries(GameEngine sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lconfig++ ${Boost_LIBRARIES})

add_library(RenderingEngine SHARED
    src/client/RenderEngine/RenderingEngine.cpp
    src/client/RenderEngine/Menu/Menu.cpp
    src/client/RenderEngine/Menu/Settings.cpp
    src/client/RenderEngine/Menu/Game.cpp
    src/shared/entities/Entity.cpp
    src/shared/registry/Registry.cpp
    src/shared/systems/Systems.cpp
)

target_link_libraries(RenderingEngine sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES})

# Source files for the Client
set(SRC_CLIENT
    src/client/main.cpp
    src/client/NetworkEngine/Client.cpp
    src/client/GameEngine/GameEngine.cpp
    src/client/GameEngine/ProtocolParsing.cpp
    src/client/NetworkEngine/NetworkEngine.cpp
    src/client/RenderEngine/RenderingEngine.cpp
    src/client/Mediator/Mediator.cpp
    src/shared/registry/Registry.cpp
    src/shared/systems/Systems.cpp
    src/client/RenderEngine/Menu/Menu.cpp
    src/client/RenderEngine/Menu/Settings.cpp
    src/client/RenderEngine/Menu/Game.cpp
    src/shared/entities/Entity.cpp
    src/shared/registry/Registry.cpp
    src/shared/systems/Systems.cpp
)

add_executable(r-type_client ${SRC_CLIENT})

# Linkage for SFML and Boost libraries
target_link_libraries(r-type_client sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lconfig++ ${Boost_LIBRARIES})

# Output directory for the client
set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# Source files for the Server
set(SRC_SERVER
    src/server/main_server.cpp # temp main waiting for the real one because current main should be client main
    src/server/GameLogique/GameLogique.cpp
    src/server/GameLogique/NetworkSender.cpp
    src/server/network/Server.cpp
    src/shared/entities/Entity.cpp
    src/shared/registry/Registry.cpp
    src/server/systems/Systems.cpp
    src/server/utils/Logger.cpp
)

add_executable(r-type_server ${SRC_SERVER})

# Linkage for SFML and Boost libraries
target_link_libraries(r-type_server sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES})

# Output directory for the server
set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Clean commands
add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -E remove -f *.o
    COMMAND ${CMAKE_COMMAND} -E remove -f r-type_server
    COMMAND ${CMAKE_COMMAND} -E remove -f r-type_client
)

# Commands for the tests
add_custom_target(tests_run
    COMMAND echo "Aucun test pour le moment"
)

# Commands for the coverage
add_custom_target(coverage
    COMMAND gcovr --exclude tests/
)

# Commands to run epitest
add_custom_target(run_epitest
    COMMAND sudo docker build -t epitest:latest .
    COMMAND sudo docker run -it epitest:latest
)

# Activer les tests
enable_testing()

# Recherche récursive des fichiers de tests depuis le dossier tests/
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp src/*.cpp)
file(GLOB_RECURSE MAIN_SOURCES main.cpp main_server.cpp)
list(REMOVE_ITEM TEST_SOURCES ${MAIN_SOURCES})

# Inclure les headers nécessaires si besoin
include_directories(${PROJECT_SOURCE_DIR}/include)

# Options de compilation et d'édition de liens pour la couverture de code
set(COVERAGE_LINK_FLAGS "--coverage")

# Créer un exécutable à partir des fichiers de test
add_executable(tests_client ${TEST_SOURCES})

# Appliquer les options de compilation et d'édition de liens
target_compile_options(tests_client PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_link_libraries(tests_client PRIVATE criterion sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} config++)

# Ajouter une commande pour exécuter les tests
add_test(NAME run_tests_client COMMAND tests_client)

# Optionnel : une cible pour exécuter tous les tests avec plus de détails en cas d'échec
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose
    DEPENDS tests_client
)

# Cible pour la couverture de code avec gcovr
add_custom_target(coverage_report
    COMMAND ${CMAKE_MAKE_PROGRAM} check
    COMMAND gcovr --exclude tests/ --branches --output coverage_report.txt --print-summary
    COMMAND gcovr --exclude tests/ --branches --html --html-details --output coverage_report.html
    DEPENDS tests_client
)

# Nettoyage des fichiers de couverture
add_custom_target(coverage_clean
    COMMAND find . -name "*.gcda" -o -name "*.gcno" -delete
)
