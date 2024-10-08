
# R-Type Project Linux Installation Guide

This guide explains how to install and set up the R-Type project on a Linux system, focusing on the `make release` process.

## Project Structure
```
R-Type-epitech/
│
├── src/
│   ├── client/           # Source files for the client
│   ├── server/           # Source files for the server
│   └── shared/           # Shared source files between client and server
│
├── build/                # Directory generated for compilation
├── lib/                  # Directory containing shared libraries
├── release/              # Directory for the release build
└── Makefile              # Build automation script
```

## Script Overview

The project is compiled using `make` with CMake. The release process builds both the client and server executables, and shared libraries for various components (Network, Game, Physics, Rendering, and Audio engines).

### Bash Script (Installation Process)
- **Step 1:** Detect the Linux distribution and package manager.
- **Step 2:** Install necessary dependencies (g++, make, git, autoconf, libtool, curl, pkg-config, and SFML).
- **Step 3:** Install CMake and vcpkg (if not already installed).
- **Step 4:** Download and build vcpkg for dependency management.
- **Step 5:** Install dependencies like Boost, SFML, and libconfig using vcpkg.
- **Step 6:** Build the project in `release` mode using CMake and Make.

### CMakeLists Configuration
- **Compiler Configuration:** Set C++17 standard and enable warnings.
- **Dependency Management:** Use vcpkg to manage external libraries like Boost and SFML.
- **Shared Libraries:** Build shared libraries for each engine (Network, Game, Physics, Rendering, and Audio).
- **Executables:** Build `r-type_client` and `r-type_server`.

### Makefile Summary

```Makefile
.PHONY: all clean fclean re release

release:
	@mkdir -p release/build
	@cd release/build && cmake -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake .. && make
	@cp release/build/r-type_server release/build/r-type_client ./
	@cp release/build/*.so lib/
	@echo "Project compiled successfully (release mode)"
```

- **`make release`**: Creates a `release/build` directory, runs CMake with the vcpkg toolchain, compiles the project, and copies the binaries and shared libraries.

## Documentation Links:
- [CMake Documentation](https://cmake.org/documentation/)
- [Make Documentation](https://www.gnu.org/software/make/manual/make.html)
- [vcpkg Documentation](https://vcpkg.io/en/index.html)

## ASCII Diagram

```
                            +-----------------------+
                            |       User Input      |
                            +-----------------------+
                                        |
                                        v
                            +-----------------------+
                            |   Bash Install Script |
                            +-----------------------+
                                        |
                                        v
                          +----------------------------+
                          |     Dependency Manager     |
                          +----------------------------+
                                        |
                                        v
                      +------------------------------------+
                      | CMake + Make (Release Compilation) |
                      +------------------------------------+
                                        |
                                        v
             +-----------------------+     +-----------------------+
             |   Client Executable   | <-> |   Server Executable   |
             +-----------------------+     +-----------------------+
                                        |
                                        v
                  +--------------------------------------------+
                  |      Shared Libraries (Network, Game, etc) |
                  +--------------------------------------------+
```

Follow this guide to set up your project quickly and efficiently!

