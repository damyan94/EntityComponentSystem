#include "stdafx.h"

#include "ComponentDataManagerEntityProxy.h"

#include "ComponentDataManager.h"

////////////////////////////////////////////////////////////////////////////////
ComponentId ComponentDataManagerEntityProxy::Add(EComponentType type, Entity* parent)
{
	return ComponentDataManager::Instance().Add(type, parent);
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManagerEntityProxy::Remove(EComponentType type, ComponentId index)
{
	ComponentDataManager::Instance().Remove(type, index);
}

////////////////////////////////////////////////////////////////////////////////
void ComponentDataManagerEntityProxy::Reset(EComponentType type, ComponentId index)
{
	ComponentDataManager::Instance().Reset(type, index);
}

////////////////////////////////////////////////////////////////////////////////
IComponent* ComponentDataManagerEntityProxy::Get(EComponentType type, ComponentId index)
{
	return ComponentDataManager::Instance().Get(type, index);
}