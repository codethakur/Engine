#include"Game.h"
#include<iostream>
#include <GLFW/glfw3.h>

bool Game::Init() 
{
    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform vec2 uOffSet;
        uniform vec2 uScale;

        void main()
        {
            vec2 position = (aPos * uScale) + uOffSet;
            gl_Position = vec4(position, 0.0, 1.0);
        }

    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec3 uColor;

        void main()
        {
            FragColor = vec4(uColor, 1.0);
        }

    )";

    auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
    auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    m_material.SetshaderProgram(shaderProgram);

    return true;
}
void Game::Update(float deltaTime ) 
{
    auto& input = eng::Engine::GetInstance().GetInputManager();
    if(input.IsKeyPreeesed(GLFW_KEY_A))
    {
        std::cout<<"[A] key is presed: \n";
    }
}
void Game::Destroy() 
{

}