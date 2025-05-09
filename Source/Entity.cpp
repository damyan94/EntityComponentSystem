#include "stdafx.h"

#include "Entity.h"

#include "ComponentDataManagerEntityProxy.h"
#include "Components/Transform.h"

static constexpr uint64_t GetComponentMask(EComponentType type)
{
    return 1ull << (int64_t)type;
}

static bool pred(const std::pair<EComponentType, ComponentId>& pair, EComponentType value)
{
    return pair.first < value;
};

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
    ReturnIf(HasComponent(type), nullptr);

#ifdef USE_VECTOR_MAP
    m_Components.emplace_back(type, ComponentDataManagerEntityProxy::Add(type, this));
    std::sort(m_Components.begin(), m_Components.end());

#else
    m_Components[type] = ComponentDataManagerEntityProxy::Add(type, this);

#endif

    m_ComponentMask |= ((uint64_t)type + 1);

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    AssertReturnIf(EComponentType::Transform == type);
    ReturnIf(!HasComponent(type));

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
    //TODO if we would have more than 64 components in total, we could sort the vectormap
    //and then search more efficiently using the binary search functions of STL
    const auto it = std::lower_bound(m_Components.begin(), m_Components.end(), type, pred);

    return it != m_Components.end();
    //return std::binary_search(m_Components.begin(), m_Components.end(), type, pred);
    return m_ComponentMask & GetComponentMask(type);

//#ifdef USE_VECTOR_MAP
//    for (const auto& [componentType, _] : m_Components)
//    {
//        ReturnIf(componentType == type, true);
//    }
//
//    return false;
//
//#else
//    //return m_Components.contains(type);
//    return m_ComponentMask & GetComponentMask(type);
//
//#endif
}

////////////////////////////////////////////////////////////////////////////////
ComponentId Entity::GetComponentId(EComponentType type) const
{
#ifdef USE_VECTOR_MAP
    const auto it = std::lower_bound(m_Components.begin(), m_Components.end(), type, pred);

    ReturnIf(it != m_Components.end(), it->second);

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