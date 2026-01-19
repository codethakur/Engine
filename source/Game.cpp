#include"Game.h"
#include<iostream>
#include <GLFW/glfw3.h>

bool Game::Init() 
{
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