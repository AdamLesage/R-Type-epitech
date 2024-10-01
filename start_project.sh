# This file is used to start the project such as:
# Compile the project with install dependencies on your OS, Cmake, move binaries to the root directory and delete build/ directory

# Remove the binaries if they exist
rm -f r-type_server r-type_client

# Remove the shared libraries if they exist
rm -f lib/libNetworkEngine.so lib/libRenderingEngine.so lib/libGameEngine.so lib/libPhysicEngine.so libAudioEngine.so


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

# Move the binaries and shared libraries to the root directory if they exist
for file in r-type_server r-type_client libNetworkEngine.so libGameEngine.so libRenderingEngine.so libPhysicEngine.so libAudioEngine.so; do
    if [ -f "$file" ]; then
        mv "$file" ..
    fi
done

# Move back to the root directory
cd ..

# Remove the build directory
rm -rf build

# Move shared libraries to the lib directory
# Move shared libraries to the lib directory
for file in libNetworkEngine.so libGameEngine.so libRenderingEngine.so libPhysicEngine.so libAudioEngine.so; do
    if [ -f "$file" ]; then
        mv "$file" lib/
    fi
done

# Print a message to the user
echo "Project compiled successfully"
