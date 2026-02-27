#include"scene/components/PhysicsComponent.h"
#include"scene/GameObject.h"
#include"Engine.h"
#include<iostream>
namespace eng
{
    PhysicsComponent::PhysicsComponent(const std::shared_ptr<RigidBody>& body):m_rigidBody(body)
    {
    }
    void PhysicsComponent::Init()
    {
        if(!m_rigidBody)
        {
            return;
        }
        const auto position = m_owner->GetWorldPosition();
        const auto rotation = m_owner->GetWorldRotation();

        m_rigidBody->SetPosition(position);
        m_rigidBody->SetRotation(rotation);
        Engine::GetInstance().GetPhysicsManager().AddRigidBody(m_rigidBody.get());
        std::cout << "PhysicsComponent Init called\n";
    }
    void PhysicsComponent::Update(float deltaTime) 
    {
        if(!m_rigidBody)
        {
            return;
        }
        if(m_rigidBody->GetType()==BodyType::Dynamic)
        {
            m_owner->SetWorldPosition(m_rigidBody->GetPosition());
            m_owner->SetWorldRotation(m_rigidBody->GetRotation());
        }
    }
    void PhysicsComponent::SetRigidBody(const std::shared_ptr<RigidBody>& body)
    {
        m_rigidBody = body;
        
    }
}