#include "stdafx.h"

#include "Entity.h"

#include "ComponentDataManagerEntityProxy.h"
#include "Components/Transform.h"

uint64_t GetComponentMask(EComponentType type)
{
    uint64_t result = 1;

    for (int32_t i = 0; i < (int32_t)type; i++)
    {
        result <<= 1;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
Entity::Entity()
    : m_ComponentMask(0)
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
    //ReturnIf(HasComponent(type), nullptr);
    if (m_ComponentMask & GetComponentMask(type))
        return nullptr;

#ifdef USE_VECTOR_MAP
    m_Components.emplace_back(type, ComponentDataManagerEntityProxy::Add(type, this));

#else
    m_Components[type] = ComponentDataManagerEntityProxy::Add(type, this);

#endif

    m_ComponentMask |= (uint64_t)type;

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    AssertReturnIf(EComponentType::Transform == type);
    //ReturnIf(!HasComponent(type));
    if (!(m_ComponentMask & GetComponentMask(type)))
        return;

    const auto id = GetComponentId(type);
    ComponentDataManagerEntityProxy::Remove(type, id);

#ifdef USE_VECTOR_MAP
    m_Components.erase(m_Components.begin() + GetIndex(type));

#else
    m_Components.erase(type);

#endif
}

////////////////////////////////////////////////////////////////////////////////
void Entity::ResetComponent(EComponentType type)
{
    //ReturnIf(!HasComponent(type));
    if (!(m_ComponentMask & GetComponentMask(type)))
        return;

    ComponentDataManagerEntityProxy::Reset(type, GetComponentId(type));
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently because if the vector resizes, it may be invalid
IComponent* Entity::GetComponent(EComponentType type) const
{
    //ReturnIf(!HasComponent(type), nullptr);
    if (!(m_ComponentMask & GetComponentMask(type)))
        return nullptr;

    return ComponentDataManagerEntityProxy::Get(type, GetComponentId(type));
}

////////////////////////////////////////////////////////////////////////////////
bool Entity::HasComponent(EComponentType type) const
{
#ifdef USE_VECTOR_MAP
    for (const auto& [componentType, _] : m_Components)
    {
        ReturnIf(componentType == type, true);
    }

    return false;

#else
    //return m_Components.contains(type);
    return m_ComponentMask & GetComponentMask(type);

#endif
}

////////////////////////////////////////////////////////////////////////////////
ComponentId Entity::GetComponentId(EComponentType type) const
{
#ifdef USE_VECTOR_MAP
    for (const auto& [componentType, id] : m_Components)
    {
        ReturnIf(componentType == type, id);
    }

#else
    const auto it = m_Components.find(type);
    if (it != m_Components.end())
    {
        return it->second;
    }

#endif

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
#ifdef USE_VECTOR_MAP
    const auto count = m_Components.size();
    for (int32_t i = 0; i < count; i++)
    {
        ReturnIf(m_Components[i].first == type, i);
    }

#endif

    return INVALID_COMPONENT_ID;
}