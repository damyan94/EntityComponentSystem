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

    m_Components.emplace_back(type, ComponentDataManagerEntityProxy::Add(type, this));

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    AssertReturnIf(EComponentType::Transform == type);
    ReturnIf(!HasComponent(type));

    const auto id = GetComponentId(type);
    ComponentDataManagerEntityProxy::Remove(type, id);
    m_Components.erase(m_Components.begin() + GetIndex(type));
}

////////////////////////////////////////////////////////////////////////////////
void Entity::ResetComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type));

    ComponentDataManagerEntityProxy::Reset(type, GetComponentId(type));
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently because if the vector resizes, it may be invalid
IComponent* Entity::GetComponent(EComponentType type) const
{
    ReturnIf(!HasComponent(type), nullptr);

    return ComponentDataManagerEntityProxy::Get(type, GetComponentId(type));
}

////////////////////////////////////////////////////////////////////////////////
bool Entity::HasComponent(EComponentType type) const
{
    for (const auto& [componentType, _] : m_Components)
    {
        ReturnIf(componentType == type, true);
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
ComponentId Entity::GetComponentId(EComponentType type) const
{
    for (const auto& [componentType, id] : m_Components)
    {
        ReturnIf(componentType == type, id);
    }

    return INVALID_COMPONENT_ID;
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveAllComponents()
{
    for (const auto& [type, id] : m_Components)
    {
        ComponentDataManagerEntityProxy::Remove(type, id);
    }

    m_Components.clear();
}

////////////////////////////////////////////////////////////////////////////////
int32_t Entity::GetIndex(EComponentType type) const
{
    const auto count = m_Components.size();
    for (int32_t i = 0; i < count; i++)
    {
        ReturnIf(m_Components[i].first == type, i);
    }

    return INVALID_COMPONENT_ID;
}