#include "Entity.h"

#include "ComponentDataManagerEntityProxy.h"
#include "Components/Transform.h"

////////////////////////////////////////////////////////////////////////////////
Entity::Entity()
{
    m_Components.resize((size_t)EComponentType::Count, INVALID_COMPONENT_ID);

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

    m_Components[(size_t)type] = ComponentDataManagerEntityProxy::Add(type, this);
    //m_Components.emplace_back(type, ComponentDataManagerEntityProxy::Add(type, this));

    return GetComponent(type);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveComponent(EComponentType type)
{
    AssertReturnIf(EComponentType::Transform == type);
    ReturnIf(!HasComponent(type));

    //const auto id = GetIndex(type);
    ComponentDataManagerEntityProxy::Remove(type, m_Components[(size_t)type]);
    //ComponentDataManagerEntityProxy::Remove(type, GetComponentId(type));
    m_Components[(size_t)type] = INVALID_COMPONENT_ID;
    //m_Components.erase(m_Components.begin() + id);
}

////////////////////////////////////////////////////////////////////////////////
void Entity::ResetComponent(EComponentType type)
{
    ReturnIf(!HasComponent(type));

    return ComponentDataManagerEntityProxy::Reset(type, m_Components[(size_t)type]);
    //ComponentDataManagerEntityProxy::Reset(type, GetComponentId(type));
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently because if the vector resizes, it may be invalid
IComponent* Entity::GetComponent(EComponentType type) const
{
    ReturnIf(!HasComponent(type), nullptr);

    return ComponentDataManagerEntityProxy::Get(type, m_Components[(size_t)type]);
    //return ComponentDataManagerEntityProxy::Get(type, GetComponentId(type));
}

////////////////////////////////////////////////////////////////////////////////
bool Entity::HasComponent(EComponentType type) const
{
    return m_Components[(size_t)type] != INVALID_COMPONENT_ID;
    //return m_Components.contains(type);
    //return GetIndex(type) != INVALID_COMPONENT_ID;
}

////////////////////////////////////////////////////////////////////////////////
void Entity::RemoveAllComponents()
{
    for (int i = 0; i < (size_t)EComponentType::Count; i++)
    {
        ContinueIf(i == INVALID_COMPONENT_ID);

        ComponentDataManagerEntityProxy::Remove((EComponentType)i, m_Components[i]);
    }
    /*for (const auto& [type, id] : m_Components)
    {
        ContinueIf(!HasComponent(type));

        ComponentDataManagerEntityProxy::Remove(type, id);
    }*/

    //m_Components.clear();
}

//////////////////////////////////////////////////////////////////////////////////
//int32_t Entity::GetIndex(EComponentType type) const
//{
//    for (int32_t i = 0; i < m_Components.size(); i++)
//    {
//        const auto& item = m_Components[i];
//        ReturnIf(item.first == type, i);
//    }
//
//    return INVALID_COMPONENT_ID;
//}

////////////////////////////////////////////////////////////////////////////////
ComponentId Entity::GetComponentId(EComponentType type) const
{
    return m_Components[(size_t)type];

    /*ReturnIf(!HasComponent(type), INVALID_COMPONENT_ID);

    return m_Components.find(type)->second;*/

    /*const auto count = m_Components.size();
    for (int i = 0; i < count; i++)
    {
        const auto& element = m_Components[i];
        ReturnIf(element.first == type, element.second);
    }

    return INVALID_COMPONENT_ID;*/
}