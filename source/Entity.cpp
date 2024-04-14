#include "Entity.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"

////////////////////////////////////////////////////////////////////////////////
Entity::Entity()
{
    AddComponent(EComponentType::Transform);
}

////////////////////////////////////////////////////////////////////////////////
Entity::~Entity()
{
    RemoveAllComponents();
}

////////////////////////////////////////////////////////////////////////////////
IComponent* Entity::AddComponent(EComponentType type)
{
    ReturnIf(HasComponent(type), nullptr);

    m_Components[type] = ComponentDataManager::Instance().Add(type);

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type) || EComponentType::Transform == type);

    ComponentDataManager::Instance().Remove(type, m_Components[type]);
    m_Components.erase(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::ResetComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type));

    ComponentDataManager::Instance().Reset(type, m_Components[type]);
}

////////////////////////////////////////////////////////////////////////////////
bool Entity::HasComponent(EComponentType type) const
{
    return m_Components.contains(type);
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently because if the vector resizes, it may be invalid
IComponent* Entity::GetComponent(EComponentType type) const
{
    ReturnIf(!HasComponent(type), nullptr);

    return ComponentDataManager::Instance().Get(type, m_Components.find(type)->second);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveAllComponents()
{
    for (const auto [type, _] : m_Components)
    {
        ContinueIf(!HasComponent(type));

        ComponentDataManager::Instance().Remove(type, m_Components[type]);
    }

    m_Components.clear();
}