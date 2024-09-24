# This file is used to start the project such as:
# Compile the project with install dependencies on your OS, Cmake, move binaries to the root directory and delete build/ directory

# Remove the binaries if they exist
if [ -f "r-type_server" ]; then
    rm r-type_server
fi

if [ -f "r-type_client" ]; then
    rm r-type_client
fi

# Check if the build directory exists
if [ -d "build" ]; then
    # If the build directory exists, remove it
    rm -rf build
fi

# Create a build directory
mkdir build

# Move to the build directory
cd build

# Compile the project with Cmake
cmake ..

# Compile the project with make
make

# Move the binaries to the root directory if files exist
if [ -f "r-type_server" ]; then
    mv r-type_server ..
fi

if [ -f "r-type_client" ]; then
    mv r-type_client ..
fi

# Move back to the root directory
cd ..

# Remove the build directory
rm -rf build

# Print a message to the user
echo "Project compiled successfully"
