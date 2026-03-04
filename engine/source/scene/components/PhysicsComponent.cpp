#include"scene/components/PhysicsComponent.h"
#include"scene/GameObject.h"
#include"Engine.h"
#include<iostream>
namespace eng
{
    PhysicsComponent::PhysicsComponent(const std::shared_ptr<RigidBody>& body):m_rigidBody(body)
    {
    }
    void PhysicsComponent:: LoadProperties(const nlohmann::json& json)
    {
        std::shared_ptr<Collider>collider;
        if(json.contains("collider"))
        {
            const auto colliderObj = json["collider"];
            std::string type = colliderObj.value("type", "");

            if(type == "box")
            {
                glm::vec3 extents(
                    colliderObj.value("x", 1.0f),
                    colliderObj.value("y", 1.0f),
                    colliderObj.value("z", 1.0f)
                );
                collider = std::make_shared<BoxCollider>(extents);
            }
            else if (type == "sphere") 
            {
                float radius = colliderObj.value("r", 1.0f);
                collider = std::make_shared<SphereCollider>(radius);
            }
            else if (type == "capsule") 
            {
                float radius = colliderObj.value("r", 1.0f);
                float height = colliderObj.value("h", 1.0f);
                collider = std::make_shared<CapsuleCollider>(radius, height);
            }
            if (!collider)
            {
                return;
            }
            std::shared_ptr<RigidBody> rigidbody;
            if (json.contains("body")) 
            {
                const auto& bodyObj = json["body"];

                float mass = bodyObj.value("mass", 0.0f);
                float friction = bodyObj.value("friction", 0.5f);
                std::string typeStr = bodyObj.value("type", "static");

                BodyType type = BodyType::Static;
                if (typeStr == "dynamic")
                { 
                    type = BodyType::Dynamic;
                }
                else if (typeStr == "kinematic")
                {
                    type = BodyType::Kinematic;
                }

                rigidbody = std::make_shared<RigidBody>(type, collider, mass, friction);
            }

            if (rigidbody)
            {
                SetRigidBody(rigidbody);
            }
        }
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