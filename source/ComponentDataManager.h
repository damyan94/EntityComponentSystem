#pragma once

#include <unordered_map>

#include "Defines.h"
#include "ComponentDataContainer.h"
#include "Components/ComponentType.h"

class IComponent;

////////////////////////////////////////////////////////////////////////////////
class ComponentDataManager
{
	friend class Entity;

private:
	ComponentDataManager();
	~ComponentDataManager();

	ComponentDataManager(const ComponentDataManager&) = delete;
	ComponentDataManager(ComponentDataManager&&) = delete;
	ComponentDataManager& operator=(const ComponentDataManager&) = delete;
	ComponentDataManager& operator=(ComponentDataManager&&) = delete;

public:
	static ComponentDataManager& Instance();
	//TODO Maybe move this to a new class, since the idea of this is to be used by the systems
	template <typename T> std::vector<T>& GetAllComponents() const;

private:
	bool				Init();
	void				Deinit();

	ComponentId			Add(EComponentType type);
	void				Remove(EComponentType type, ComponentId index);
	void				Reset(EComponentType type, ComponentId index);
	IComponent*			Get(EComponentType type, ComponentId index) const;

private:
	std::unordered_map<EComponentType, IComponentDataContainer*> m_ComponentDataContainers;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline std::vector<T>& ComponentDataManager::GetAllComponents() const
{
	static auto empty = std::vector<T>();
	AssertReturnIf(!(std::is_base_of<IComponent, T>::value), empty);

	return ((ComponentDataContainer<T>*)(m_ComponentDataContainers.find(T::Type)->second))->GetAll();
}