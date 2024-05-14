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

	// Do the initialization in the order of declaring the types in the enum class.
#define INIT_COMPONENT_DATA_CONTAINER(Type) m_ComponentDataContainers.emplace_back(new ComponentDataContainer<Type>)

	INIT_COMPONENT_DATA_CONTAINER(Transform);
	INIT_COMPONENT_DATA_CONTAINER(Image);
	INIT_COMPONENT_DATA_CONTAINER(Text);
	INIT_COMPONENT_DATA_CONTAINER(Action);

#undef INIT_COMPONENT_DATA_CONTAINER

	return true;
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManager::Deinit()
{
	for (auto& componentSystem : m_ComponentDataContainers)
	{
		SafeDelete(componentSystem);
	}

	m_ComponentDataContainers.clear();
}

////////////////////////////////////////////////////////////////////////////////
ComponentId ComponentDataManager::Add(EComponentType type, Entity* parent)
{
	return m_ComponentDataContainers[(int32_t)type]->Add(parent);
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManager::Remove(EComponentType type, ComponentId index)
{
	m_ComponentDataContainers[(int32_t)type]->Remove(index);
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManager::Reset(EComponentType type, ComponentId index)
{
	m_ComponentDataContainers[(int32_t)type]->Reset(index);
}

////////////////////////////////////////////////////////////////////////////////
IComponent* ComponentDataManager::Get(EComponentType type, ComponentId index) const
{
	return m_ComponentDataContainers[(int32_t)type]->Get(index);
}