#pragma once

#include "Defines.h"

class IComponent;

////////////////////////////////////////////////////////////////////////////////
class IComponentDataContainer
{
public:
	IComponentDataContainer() = default;
	virtual ~IComponentDataContainer() = default;

	virtual ComponentId			Add(Entity* parent) = 0;
	virtual void				Remove(ComponentId index) = 0;
	virtual void				Reset(ComponentId index) = 0;
	virtual IComponent*			Get(ComponentId index) = 0;
	virtual size_t				Count() const = 0;
};