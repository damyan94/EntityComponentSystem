#include "Entity.h"

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

    m_Components[type] = EntityManager::Instance().AddComponent(type);

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type));

    EntityManager::Instance().RemoveComponent(type, m_Components[type]);
    m_Components.erase(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::ResetComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type));

    EntityManager::Instance().ResetComponent(type, m_Components[type]);
}

////////////////////////////////////////////////////////////////////////////////
bool Entity::HasComponent(EComponentType type) const
{
    return m_Components.contains(type);
}

////////////////////////////////////////////////////////////////////////////////
IComponent* Entity::GetComponent(EComponentType type) const
{
    ReturnIf(!HasComponent(type), nullptr);

    return EntityManager::Instance().GetComponent(type, m_Components.find(type)->second);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveAllComponents()
{
    for (const auto [type, _] : m_Components)
    {
        ContinueIf(!HasComponent(type));

        EntityManager::Instance().RemoveComponent(type, m_Components[type]);
    }

    m_Components.clear();
}