#include "ComponentDataManager.h"

#include "ComponentDataContainer.h"

#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

////////////////////////////////////////////////////////////////////////////////
ComponentDataManager::ComponentDataManager()
{
	Init();
}

////////////////////////////////////////////////////////////////////////////////
ComponentDataManager::~ComponentDataManager()
{
	Deinit();
}

////////////////////////////////////////////////////////////////////////////////
ComponentDataManager& ComponentDataManager::Instance()
{
	static ComponentDataManager m_Instance;
	return m_Instance;
}

////////////////////////////////////////////////////////////////////////////////
bool ComponentDataManager::Init()
{
	m_ComponentDataContainers.reserve((size_t)EComponentType::Count);

#define INIT_COMPONENT_DATA_CONTAINER(Type) m_ComponentDataContainers[EComponentType::Type] = new ComponentDataContainer<Type>

	INIT_COMPONENT_DATA_CONTAINER(Transform);
	INIT_COMPONENT_DATA_CONTAINER(Image);
	INIT_COMPONENT_DATA_CONTAINER(Text);
	INIT_COMPONENT_DATA_CONTAINER(Action);

#undef INIT_COMPONENT_SYSTEM

	return true;
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManager::Deinit()
{
	for (auto& [_, componentSystem] : m_ComponentDataContainers)
	{
		SafeDelete(componentSystem);
	}

	m_ComponentDataContainers.clear();
}

////////////////////////////////////////////////////////////////////////////////
ComponentId ComponentDataManager::AddComponent(EComponentType type)
{
	return m_ComponentDataContainers[type]->Add();
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManager::RemoveComponent(EComponentType type, ComponentId index)
{
	m_ComponentDataContainers[type]->Remove(index);
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManager::ResetComponent(EComponentType type, ComponentId index)
{
	m_ComponentDataContainers[type]->Reset(index);
}

////////////////////////////////////////////////////////////////////////////////
IComponent* ComponentDataManager::GetComponent(EComponentType type, ComponentId index) const
{
	return m_ComponentDataContainers.find(type)->second->Get(index);
}