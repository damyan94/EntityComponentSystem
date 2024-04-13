#pragma once

#include <unordered_map>

#include "Defines.h"
#include "EntityManager.h"
#include "Components/ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Entity
{
public:
	Entity();
	~Entity();

	IComponent*			AddComponent(EComponentType type);
	void				RemoveComponent(EComponentType type);
	void				ResetComponent(EComponentType type);
	bool				HasComponent(EComponentType type) const;
	IComponent*			GetComponent(EComponentType type) const;

	template <typename T> T*			AddComponent();
	template <typename T> void			RemoveComponent();
	template <typename T> void			ResetComponent();
	template <typename T> bool			HasComponent() const;
	template <typename T> T*			GetComponent() const;

private:
	void				RemoveAllComponents();
	template <typename T> ComponentId	GetComponentId() const;

private:
	std::unordered_map<EComponentType, ComponentId> m_Components;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T* Entity::AddComponent()
{
	ReturnIf(HasComponent<T>(), nullptr);

	m_Components[T::Type] = EntityManager::Instance().AddComponent<T>();

	return GetComponent<T>();
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void Entity::RemoveComponent()
{
	ReturnIf(!HasComponent<T>());

	EntityManager::Instance().RemoveComponent<T>(GetComponentId<T>());
	m_Components.erase(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void Entity::ResetComponent()
{
	ReturnIf(!HasComponent<T>());

	EntityManager::Instance().ResetComponent<T>(GetComponentId<T>());
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool Entity::HasComponent() const
{
	return m_Components.contains(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T* Entity::GetComponent() const
{
	ReturnIf(!HasComponent<T>(), nullptr);

	return EntityManager::Instance().GetComponent<T>(GetComponentId<T>());
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ComponentId Entity::GetComponentId() const
{
	return m_Components.find(T::Type)->second;
}