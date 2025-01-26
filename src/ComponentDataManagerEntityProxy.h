#pragma once

#include "Defines.h"
#include "Components/ComponentType.h"

class IComponent;
class Entity;

////////////////////////////////////////////////////////////////////////////////
class ComponentDataManagerEntityProxy
{
public:
	ComponentDataManagerEntityProxy() = delete;
	~ComponentDataManagerEntityProxy() = default;

	static ComponentId		Add(EComponentType type, Entity* parent);
	static void				Remove(EComponentType type, ComponentId index);
	static void				Reset(EComponentType type, ComponentId index);
	static IComponent*		Get(EComponentType type, ComponentId index);
};