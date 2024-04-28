#include "Entity.h"

#include "ComponentDataManagerEntityProxy.h"
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

    m_Components[type] = ComponentDataManagerEntityProxy::Add(type);

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    AssertReturnIf(EComponentType::Transform == type);
    ReturnIf(!HasComponent(type));

    ComponentDataManagerEntityProxy::Remove(type, m_Components[type]);
    m_Components.erase(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::ResetComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type));

    ComponentDataManagerEntityProxy::Reset(type, m_Components[type]);
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently because if the vector resizes, it may be invalid
IComponent* Entity::GetComponent(EComponentType type) const
{
    ReturnIf(!HasComponent(type), nullptr);

    return ComponentDataManagerEntityProxy::Get(type, m_Components.find(type)->second);
}

////////////////////////////////////////////////////////////////////////////////
bool Entity::HasComponent(EComponentType type) const
{
    return m_Components.contains(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveAllComponents()
{
    for (const auto [type, _] : m_Components)
    {
        ContinueIf(!HasComponent(type));

        ComponentDataManagerEntityProxy::Remove(type, m_Components[type]);
    }

    m_Components.clear();
}