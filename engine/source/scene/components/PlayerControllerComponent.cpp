#include "scene/components/PlayerControllerComponent.h"
#include"input/InputManager.h"
#include"Engine.h"
#include<GLFW/glfw3.h>
#include"glm/gtc/matrix_transform.hpp"
#include<glm/vec4.hpp>

namespace eng
{
    void PlayerControllerComponent::Update(float deltaTime) 
    {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        auto rotation = m_owner->GetRotation();

        if(inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            const auto& oldPos = inputManager.GetMousePosittionOld();
            const auto& currentPos= inputManager.GetMousePosittionCurrent();

            float deltaX = currentPos.x - oldPos.x;
            float deltaY = currentPos.y - oldPos.y;

            /*
            rotation.y -= deltaX * m_sensitivity * deltaTime;
            rotation.x -= deltaY * m_sensitivity * deltaTime;
            */

            //rot around y axis 
            float yAngle = -deltaX * m_sensitivity * deltaTime;
            glm::quat yRot = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f)); //World +Y (up)

            //rot around X axis
            float xAngle = -deltaY * m_sensitivity *deltaTime;
            glm::vec3 right = rotation* glm::vec3(1.0f, 0.0f, 0.0f); //Local +X (right)
            glm::quat xRot = glm::angleAxis(xAngle, right);

            glm::quat deltaTime = yRot * xRot;
            rotation = glm::normalize(deltaTime * rotation);

            m_owner->SetRotation(rotation); 
        }

        glm::vec3 font = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 right =  rotation* glm::vec3(1.0f, 0.0f, 0.0f); //Local +X (right)

        auto position = m_owner->GetPosition();
        //left/right Movement
        if (inputManager.IsKeyPressed(GLFW_KEY_A))
           position += right * m_moveSpeed *deltaTime;
        else if (inputManager.IsKeyPressed(GLFW_KEY_D))
            position -= right * m_moveSpeed *deltaTime;


        //Vertical movement
        if (inputManager.IsKeyPressed(GLFW_KEY_W))
            position += font * m_moveSpeed *deltaTime;
        else if (inputManager.IsKeyPressed(GLFW_KEY_S))
            position -= font * m_moveSpeed *deltaTime;


        #if 0
            position.x = std::clamp(position.x, -0.5f, 0.5f);
            position.y = std::clamp(position.y, -0.5f, 0.5f);
        #endif
        
        m_owner->SetPosition(position);
    }

}