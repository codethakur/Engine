cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add engine module
add_subdirectory(engine)

# Game executable
add_executable(${PROJECT_NAME}
    source/main.cpp
    source/Game.h    
    source/Game.cpp
)
include_directories(engine/source)
# Link against engine
target_link_libraries(${PROJECT_NAME}
    Engine
)
