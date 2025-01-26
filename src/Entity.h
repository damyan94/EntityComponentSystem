#pragma once

#include <type_traits>
#include <vector>
#include <unordered_map>

#include "Defines.h"
#include "Components/ComponentType.h"
#include "Components/IComponent.h"

template<typename K, typename V>
using VectorMap = std::vector<std::pair<K, V>>;

////////////////////////////////////////////////////////////////////////////////
class Entity
{
public:
	Entity();
	~Entity();

	IComponent*			AddComponent(EComponentType type);
	void				RemoveComponent(EComponentType type);
	void				ResetComponent(EComponentType type);
	IComponent*			GetComponent(EComponentType type) const;
	bool				HasComponent(EComponentType type) const;

	template <typename T> T*			AddComponent();
	template <typename T> void			RemoveComponent();
	template <typename T> void			ResetComponent();
	template <typename T> T*			GetComponent() const;
	template <typename T> bool			HasComponent() const;

	ComponentId			GetComponentId(EComponentType type) const;
private:
	void				RemoveAllComponents();
	int32_t				GetIndex(EComponentType type) const;

private:
	VectorMap<EComponentType, ComponentId> m_Components;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T* Entity::AddComponent()
{
	AssertReturnIf(!(std::is_base_of<IComponent, T>::value), nullptr);

	return (T*)AddComponent(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void Entity::RemoveComponent()
{
	AssertReturnIf(!(std::is_base_of<IComponent, T>::value));

	RemoveComponent(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void Entity::ResetComponent()
{
	AssertReturnIf(!(std::is_base_of<IComponent, T>::value));

	ResetComponent(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently because if the vector resizes, it may be invalid
template <typename T>
inline T* Entity::GetComponent() const
{
	AssertReturnIf(!(std::is_base_of<IComponent, T>::value), nullptr);

	return (T*)GetComponent(T::Type);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool Entity::HasComponent() const
{
	AssertReturnIf(!(std::is_base_of<IComponent, T>::value), false);

	return HasComponent(T::Type);
}