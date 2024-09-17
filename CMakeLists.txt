# Version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(r-type)

# Définition des fichiers sources
set(SRC_SERVER src/server/main.cpp)

# Options de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")

# Ajout de l'exécutable serveur et nom explicite du binaire r-type_server
add_executable(r-type_server ${SRC_SERVER})

# Spécifie le dossier de sortie pour l'exécutable
set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Ajout d'une cible pour le nettoyage (renommée en custom_clean)
add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -E remove -f *.o
    COMMAND ${CMAKE_COMMAND} -E remove -f r-type_server
)

# Tests (pas encore implémentés)
add_custom_target(tests_run
    COMMAND echo "No tests for the moment"
)

# Commande pour la couverture de code
add_custom_target(coverage
    COMMAND gcovr --exclude tests/
)

# Commande pour lancer les tests Docker epitest
add_custom_target(run_epitest
    COMMAND sudo docker build -t epitest:latest .
    COMMAND sudo docker run -it epitest:latest
)
