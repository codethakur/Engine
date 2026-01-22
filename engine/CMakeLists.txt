cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Engine library
# =========================
add_library(${PROJECT_NAME} STATIC
    source/Engine.cpp
    source/Application.cpp
    source/input/InputManager.cpp
    source/graphics/ShaderProgram.cpp
    source/graphics/GraphicsAPI.cpp
    source/render/Material.cpp
    source/render/Mesh.cpp
    source/render/RenderQueue.cpp
    source/Scene/GameObject.cpp
    source/Scene/Scene.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
)

# =========================
# GLAD
# =========================
add_library(glad STATIC
    thirdparty/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    thirdparty/glad/include
)

# =========================
# GLFW
# =========================
add_subdirectory(thirdparty/glfw-3.4)

# =========================
# OpenGL (portable)
# =========================
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glfw
        glad
    PRIVATE
        OpenGL::GL
)
