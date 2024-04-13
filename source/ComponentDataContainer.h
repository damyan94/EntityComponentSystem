#pragma once

#include <vector>
#include <deque>

#include "Defines.h"
#include "IComponentDataContainer.h"

////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ComponentDataContainer
	: public IComponentDataContainer
{
	friend class ComponentDataManager;

private:
	ComponentId			Add() final;
	void				Remove(ComponentId index) final;
	void				Reset(ComponentId index) final;
	T*					Get(ComponentId index) final;
	size_t				Count() const final;

	std::vector<T>&		GetAll();

private:
	bool				DoesIndexExist(ComponentId index) const;
	bool				CanAdd() const;
	ComponentId			AddInternal(const T& newData);

	bool				HasFreeSlot() const;
	void				EmplaceFreeSlot(ComponentId index);
	ComponentId			PopFreeSlot();

private:
	std::vector<T>			m_ComponentsData;
	std::deque<ComponentId>	m_FreeSlots;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline ComponentId ComponentDataContainer<T>::Add()
{
	AssertReturnIf(!(CanAdd() || HasFreeSlot()), INVALID_COMPONENT_ID);

	ComponentId index = PopFreeSlot();
	if (INVALID_COMPONENT_ID == index)
	{
		index = AddInternal(T());
	}

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
template<typename T>
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
inline ComponentId ComponentDataContainer<T>::AddInternal(const T& newData)
{
	m_ComponentsData.emplace_back(newData);

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