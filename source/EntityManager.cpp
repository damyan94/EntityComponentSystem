#include "EntityManager.h"

#include "ComponentDataContainer.h"

#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

////////////////////////////////////////////////////////////////////////////////
EntityManager::EntityManager()
{
	Init();
}

////////////////////////////////////////////////////////////////////////////////
EntityManager::~EntityManager()
{
	Deinit();
}

////////////////////////////////////////////////////////////////////////////////
EntityManager& EntityManager::Instance()
{
	static EntityManager m_Instance;
	return m_Instance;
}

////////////////////////////////////////////////////////////////////////////////
bool EntityManager::Init()
{
	m_ComponentDataContainers.reserve((size_t)EComponentType::Count);

#define INIT_COMPONENT_SYSTEM(Type) m_ComponentDataContainers[EComponentType::Type] = new ComponentDataContainer<Type>

	INIT_COMPONENT_SYSTEM(Transform);
	INIT_COMPONENT_SYSTEM(Image);
	INIT_COMPONENT_SYSTEM(Text);
	INIT_COMPONENT_SYSTEM(Action);

#undef INIT_COMPONENT_SYSTEM

	return true;
}

////////////////////////////////////////////////////////////////////////////////
void EntityManager::Deinit()
{
	for (auto& [_, componentSystem] : m_ComponentDataContainers)
	{
		SafeDelete(componentSystem);
	}

	m_ComponentDataContainers.clear();
}

////////////////////////////////////////////////////////////////////////////////
ComponentId EntityManager::AddComponent(EComponentType type)
{
	return m_ComponentDataContainers[type]->Add();
}

////////////////////////////////////////////////////////////////////////////////
void EntityManager::RemoveComponent(EComponentType type, ComponentId index)
{
	m_ComponentDataContainers[type]->Remove(index);
}

////////////////////////////////////////////////////////////////////////////////
void EntityManager::ResetComponent(EComponentType type, ComponentId index)
{
	m_ComponentDataContainers[type]->Reset(index);
}

////////////////////////////////////////////////////////////////////////////////
IComponent* EntityManager::GetComponent(EComponentType type, ComponentId index) const
{
	return m_ComponentDataContainers.find(type)->second->Get(index);
}
