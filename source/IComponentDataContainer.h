#pragma once

#include <vector>

#include "Defines.h"

class IComponent;

////////////////////////////////////////////////////////////////////////////////
class IComponentDataContainer
{
public:
	virtual ComponentId			Add() = 0;
	virtual void				Remove(ComponentId index) = 0;
	virtual void				Reset(ComponentId index) = 0;
	virtual IComponent*			Get(ComponentId index) = 0;
	virtual size_t				Count() const = 0;
};