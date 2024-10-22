cmake_minimum_required(VERSION 3.10)

project(r-type_asset_editor)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Define source files
set(SOURCES
    main.cpp
    Sidebar/RightSidebar.cpp
    Sidebar/Toolbar.cpp
    Sidebar/ToolbarButton.cpp
    Sidebar/assetSelector/AssetSelector.cpp
    Sidebar/componentsEditor/ComponentsEditor.cpp
    Sidebar/componentsEditor/Input.cpp
    Sidebar/componentsEditor/InputNumber.cpp
    Sidebar/componentsEditor/SelectButton.cpp
    Sidebar/selectBar/SelectBar.cpp
    AssetEditor/AssetEditor.cpp
    EditionScreen/EditionScreen.cpp
    EditionScreen/SaveScene.cpp
    history/Asset.cpp
    history/AddAsset.cpp
    history/RemoveAsset.cpp
    history/MoveAsset.cpp
    history/CommandManager.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    -lconfig++
)

# Platform-specific settings
if (WIN32)
    # Windows-specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
elseif (UNIX)
    # Linux-specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
