# R-Type Project Windows Installation Guide

This guide explains how to install and set up the R-Type project on a Windows system using the provided installer executable `windows_installer.exe`.

## Overview of Installation Process

The installer takes care of installing all the required tools, libraries, and dependencies needed to build and run the R-Type project. The installation is managed through `Chocolatey`, a package manager for Windows, along with additional commands for specific steps.

### What the Installer Does:

1. **Install Chocolatey**
   - If `Chocolatey` is not already installed on your system, the installer will automatically install it.

2. **Install Required Packages**
   - The following packages are installed using `Chocolatey`:
     - **Git**: Required for version control and cloning the repository.
     - **Visual Studio 2022 Community Edition**: With necessary components for C++ desktop development.
     - **Windows SDK**: Version 10.1 for building Windows applications.
     - **Visual Studio Build Tools**: To support compilation processes.
     - **CMake**: A build system generator used for configuring and building the project.

3. **Clone vcpkg and Install Dependencies**
   - The installer clones `vcpkg` (a dependency manager for C++) from the official GitHub repository and sets it up.
   - Using `vcpkg`, the following dependencies are installed:
     - **SFML**: Used for graphics and multimedia functionalities.
     - **Boost.Asio**: Networking library used for client-server communication.
     - **libconfig**: Configuration file processing.

4. **Compile the Project**
   - A build directory is created, and the project is compiled in **Release** mode using CMake.
   - The project is then built using the Visual Studio Build Tools.
   - The compiled binaries (`r-type_client.exe` and `r-type_server.exe`) are moved to the project root directory.

5. **Library Handling**
   - Shared libraries (e.g., Rendering, Physics, Network, Game, Audio engines) are renamed and moved to a `lib` folder.
   - All remaining dynamic link libraries (`.dll` files) are moved to the root directory of the project.

6. **Assets and Configuration Files**
   - The **assets** directory is copied to the root folder to ensure all game assets are available.
   - The **lib** and **config** directories are also copied to the root, containing essential configuration and library files.

## Running the Installer

- To run the installer, simply execute `windows_installer.exe`.
- The script will guide you through the installation steps, automatically installing all necessary tools and dependencies.

### Key Points for Developers

- The project uses **CMake** for building, and **vcpkg** as the dependency manager.
- Make sure the **vcpkg** directory is in the system path to ensure that dependencies are correctly resolved during the build process.
- The compiled binaries (`r-type_client.exe` and `r-type_server.exe`) will be placed in the root directory, while dynamic libraries are moved to a `lib` subfolder.

## Directory Structure After Installation
```
R-Type-epitech/
│
├── assets/                # Game assets
├── build/                 # Directory generated for compilation
├── config/                # Configuration files
├── lib/                   # Shared libraries (.dll files)
├── r-type_client.exe      # Client executable
├── r-type_server.exe      # Server executable
└── windows_installer.exe  # Installer executable
```

## Additional Information

- **Visual Studio Components**: The installer includes the necessary workload and components for native C++ development, such as **VCTools** and **CMake support**.
- **Library Renaming**: The installer renames shared libraries to ensure they are correctly loaded by the executables (e.g., `RenderingEngine.dll` becomes `libRenderingEngine.dll`).

## Troubleshooting

- Ensure you have administrator privileges when running the installer, as some tools require elevated permissions.
- If the installation of a package fails, you may need to manually rerun the corresponding Chocolatey command.

Follow this guide to get your R-Type project up and running quickly and efficiently!
