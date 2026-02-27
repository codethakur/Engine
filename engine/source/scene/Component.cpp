#include"scene/Component.h"

namespace eng
{
    size_t Component::nextId = 1;
    void Component::Init()
    {
    }
    void  Component::LoadProperties(const nlohmann::json& json)
    {

    }
    GameObject* Component::GetOwner()
    {
      return m_owner;
    }
    ComponentFactory& ComponentFactory::GetInstance()
    {
      static ComponentFactory instance;
      return instance;
    }
};