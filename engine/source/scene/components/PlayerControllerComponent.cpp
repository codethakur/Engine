#include "scene/components/PlayerControllerComponent.h"
#include"input/InputManager.h"
#include"Engine.h"
#include<GLFW/glfw3.h>
#include"glm/gtc/matrix_transform.hpp"
#include<glm/vec4.hpp>

namespace eng
{
    void PlayerControllerComponent::Init()
    {
       m_kinematicController = std::make_unique<KinematicCharacterController>(0.4f, 1.2f);
    }
    void PlayerControllerComponent::Update(float deltaTime) 
    {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        auto rotation = m_owner->GetRotation();

        if(inputManager.IsMousePositionChanged())
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
           // Yaw
            float yDeltaAngle = -deltaX * m_sensitivity * deltaTime;
            m_yRotation += yDeltaAngle;
            glm::quat yRot = glm::angleAxis(glm::radians(m_yRotation), glm::vec3(0, 1, 0));

            // Pitch
            float xDeltaAngle = -deltaY * m_sensitivity * deltaTime;
            m_xRotation += xDeltaAngle;
            m_xRotation = std::clamp(m_xRotation, -89.0f, 89.0f);
            glm::quat xRot = glm::angleAxis(glm::radians(m_xRotation), glm::vec3(1, 0, 0));
            // Final rotation
            rotation = glm::normalize(yRot * xRot);

            m_owner->SetRotation(rotation); 

        }

        glm::vec3 front =  rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 right =  rotation* glm::vec3(1.0f, 0.0f, 0.0f); //Local +X (right)
        
        glm::vec3 move(0.0f);
        //left/right Movement
        if (inputManager.IsKeyPressed(GLFW_KEY_A))
           move -= right;
        else if (inputManager.IsKeyPressed(GLFW_KEY_D))
           move += right;


        //Vertical movement
        if (inputManager.IsKeyPressed(GLFW_KEY_W))
         move += front;
        else if (inputManager.IsKeyPressed(GLFW_KEY_S))
             move -= front;

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        if (inputManager.IsKeyPressed(GLFW_KEY_SPACE))
           m_kinematicController->Jump(glm::vec3(0.0f, 5.0f, 0.0f));

        #if 0
            move.x = std::clamp(move.x, -0.5f, 0.5f);
            move.y = std::clamp(move.y, -0.5f, 0.5f);
        #endif
        if (glm::dot(move, move) > 0)
        {
            move = glm::normalize(move);
        }
        m_kinematicController->Walk(move * m_moveSpeed * deltaTime);
       m_owner->SetPosition(m_kinematicController->GetPosition());
    }

}