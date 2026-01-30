cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(Engine)
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

# =========================
# Engine library
# =========================
add_library(${PROJECT_NAME} STATIC
    source/Engine.cpp
    source/Application.cpp
    source/input/InputManager.cpp
    source/graphics/ShaderProgram.cpp
    source/graphics/GraphicsAPI.cpp
    source/graphics/Texture.cpp
    source/render/Material.cpp
    source/render/Mesh.cpp
    source/render/RenderQueue.cpp
    source/Scene/GameObject.cpp
    source/Scene/Scene.cpp
    source/Scene/Component.cpp
    source/Scene/components/MeshComponent.cpp
    source/Scene/components/CamraComponent.cpp
    source/Scene/components/PlayerControllerComponent.cpp
    source/io/FileSystem.cpp

)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm
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
include_directories(thirdparty/stb_image)
include_directories(thirdparty/json)
include_directories(thirdparty/cgltf)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glfw
        glad
    PRIVATE
        OpenGL::GL
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}
    ${CMAKE_BINARY_DIR}/assets
)
