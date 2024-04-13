#pragma once

#include <unordered_map>

#include "Defines.h"
#include "Components/ComponentType.h"

class IComponent;
class IComponentDataContainer;

////////////////////////////////////////////////////////////////////////////////
class EntityManager
{
	friend class Entity;

private:
	EntityManager();
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager& operator=(EntityManager&&) = delete;

private:
	static EntityManager& Instance();

	bool				Init();
	void				Deinit();

	ComponentId			AddComponent(EComponentType type);
	void				RemoveComponent(EComponentType type, ComponentId index);
	void				ResetComponent(EComponentType type, ComponentId index);
	IComponent*			GetComponent(EComponentType type, ComponentId index) const;

	template <typename T> ComponentId	AddComponent();
	template <typename T> void			RemoveComponent(ComponentId index);
	template <typename T> void			ResetComponent(ComponentId index);
	template <typename T> T*			GetComponent(ComponentId index) const;

private:
	std::unordered_map<EComponentType, IComponentDataContainer*> m_ComponentDataContainers;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ComponentId EntityManager::AddComponent()
{
	//AssertReturnIf(!std::is_base_of(IComponent, T)::value, INVALID_COMPONENT_ID);
	return AddComponent(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void EntityManager::RemoveComponent(ComponentId index)
{
	//AssertReturnIf(!std::is_base_of(IComponent, T)::value);
	RemoveComponent(T::Type, index);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void EntityManager::ResetComponent(ComponentId index)
{
	//AssertReturnIf(!std::is_base_of(IComponent, T)::value);
	ResetComponent(T::Type, index);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T* EntityManager::GetComponent(ComponentId index) const
{
	//AssertReturnIf(!std::is_base_of(IComponent, T)::value, nullptr);
	return (T*)GetComponent(T::Type, index);
}