#pragma once

#include <vector>
#include <deque>

class Entity;
#include "Defines.h"
#include "IComponentDataContainer.h"

////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ComponentDataContainer
	: public IComponentDataContainer
{
	friend class ComponentDataManager;

private:
	ComponentDataContainer();
	~ComponentDataContainer();

	ComponentId			Add(Entity* parent) final;
	void				Remove(ComponentId index) final;
	void				Reset(ComponentId index) final;
	T*					Get(ComponentId index) final;
	size_t				Count() const final;

	std::vector<T>&		GetAll();

private:
	bool				DoesIndexExist(ComponentId index) const;
	bool				CanAdd() const;
	ComponentId			AddInternal();

	bool				HasFreeSlot() const;
	void				EmplaceFreeSlot(ComponentId index);
	ComponentId			PopFreeSlot();

private:
	std::vector<T>			m_ComponentsData;
	std::deque<ComponentId>	m_FreeSlots;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ComponentDataContainer<T>::ComponentDataContainer()
{
	m_ComponentsData.reserve(MAX_ENTITIES / 10);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline ComponentDataContainer<T>::~ComponentDataContainer()
{
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline ComponentId ComponentDataContainer<T>::Add(Entity* parent)
{
	AssertReturnIf(!(CanAdd() || HasFreeSlot()), INVALID_COMPONENT_ID);

	ComponentId index = PopFreeSlot();
	if (INVALID_COMPONENT_ID == index)
	{
		index = AddInternal();
	}

	m_ComponentsData[index].IsValid = true;
	m_ComponentsData[index].Parent = parent;

	return index;
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void ComponentDataContainer<T>::Remove(ComponentId index)
{
	ReturnIf(!DoesIndexExist(index));

	m_ComponentsData[index].Reset();
	EmplaceFreeSlot(index);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void ComponentDataContainer<T>::Reset(ComponentId index)
{
	ReturnIf(!DoesIndexExist(index));

	m_ComponentsData[index].Reset();
}

////////////////////////////////////////////////////////////////////////////////
// @brief Do not store permanently pointers to elements of the vector since they
// could be invalid after vector resizing. Prefer to use this locally.
template <typename T>
inline T* ComponentDataContainer<T>::Get(ComponentId index)
{
	AssertReturnIf(!DoesIndexExist(index), nullptr);

	return &m_ComponentsData[index];
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline size_t ComponentDataContainer<T>::Count() const
{
	return m_ComponentsData.size();
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline std::vector<T>& ComponentDataContainer<T>::GetAll()
{
	return m_ComponentsData;
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool ComponentDataContainer<T>::DoesIndexExist(ComponentId index) const
{
	return index >= 0 && index < (ComponentId)m_ComponentsData.size();
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool ComponentDataContainer<T>::CanAdd() const
{
	return m_ComponentsData.size() < MAX_ENTITIES;
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline ComponentId ComponentDataContainer<T>::AddInternal()
{
	static T empty;
	m_ComponentsData.emplace_back(empty);

	return (ComponentId)(m_ComponentsData.size() - 1);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool ComponentDataContainer<T>::HasFreeSlot() const
{
	return !m_FreeSlots.empty();
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void ComponentDataContainer<T>::EmplaceFreeSlot(ComponentId index)
{
	m_FreeSlots.emplace_back(index);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline ComponentId ComponentDataContainer<T>::PopFreeSlot()
{
	ComponentId result = INVALID_COMPONENT_ID;

	if (HasFreeSlot())
	{
		result = m_FreeSlots.front();
		m_FreeSlots.pop_front();
	}

	return result;
}