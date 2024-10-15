# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

if(WIN32)
    # Project name
    project(r-type)

    if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
        message(STATUS "Using VCPKG toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
    endif()

    project(r-type)

    # Compiler flags
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-D_WIN32_WINNT=0x0601)

    add_compile_options(/w)

    find_package(Boost 1.70 REQUIRED COMPONENTS system asio)
    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
    else()
        message(FATAL_ERROR "Boost not found!")
    endif()

    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        message(STATUS "SFML found: ${SFML_INCLUDE_DIR}")
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()

    find_package(libconfig CONFIG REQUIRED)
    if (libconfig_FOUND)
        message(STATUS "libconfig++ found: ${libconfig_INCLUDE_DIRS}")
        include_directories(${libconfig_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "libconfig++ not found!")
    endif()

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    message(STATUS "Configuring DLL output for Windows")

    file(GLOB_RECURSE SRC_CLIENT "src/client/*.cpp" "src/shared/*.cpp")
    file(GLOB_RECURSE SRC_SERVER "src/server/*.cpp" "src/shared/*.cpp")
    file(GLOB_RECURSE SRC_ASSET_EDITOR "src/asset_editor/*.cpp" "src/shared/*.cpp")

    add_library(NetworkEngine SHARED ${SRC_CLIENT})
    add_library(GameEngine SHARED ${SRC_CLIENT})
    add_library(PhysicEngine SHARED ${SRC_CLIENT})
    add_library(AudioEngine SHARED ${SRC_CLIENT})
    add_library(RenderingEngine SHARED ${SRC_CLIENT})

    target_link_libraries(NetworkEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
    target_link_libraries(GameEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
    target_link_libraries(PhysicEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
    target_link_libraries(AudioEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)
    target_link_libraries(RenderingEngine PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${Boost_LIBRARIES} libconfig::libconfig++)

    add_executable(r-type_client ${SRC_CLIENT})

    target_link_libraries(r-type_client NetworkEngine GameEngine PhysicEngine AudioEngine RenderingEngine ${Boost_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio libconfig::libconfig++)

    add_executable(r-type_server ${SRC_SERVER})

    target_link_libraries(r-type_server NetworkEngine GameEngine PhysicEngine AudioEngine RenderingEngine ${Boost_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio libconfig::libconfig++)

    add_executable(r-type_asset_editor ${SRC_ASSET_EDITOR})

    target_link_libraries(r-type_asset_editor NetworkEngine GameEngine PhysicEngine AudioEngine RenderingEngine ${Boost_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio libconfig::libconfig++)
else()
    # Project name
    project(r-type)

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

    # Recursively find source files for each binary
    file(GLOB_RECURSE SRC_CLIENT "src/client/*.cpp" "src/shared/*.cpp")
    file(GLOB_RECURSE SRC_SERVER "src/server/*.cpp" "src/shared/*.cpp")
    file(GLOB_RECURSE SRC_ASSET_EDITOR "src/asset_editor/*.cpp" "src/shared/*.cpp")

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
    target_link_libraries(r-type_server sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lconfig++ ${Boost_LIBRARIES})

    # Create the asset editor executable
    add_executable(r-type_asset_editor ${SRC_ASSET_EDITOR})

    # Linkage for SFML and Boost libraries
    target_link_libraries(r-type_asset_editor sfml-system sfml-window sfml-graphics sfml-network sfml-audio -lconfig++ ${Boost_LIBRARIES})
endif()