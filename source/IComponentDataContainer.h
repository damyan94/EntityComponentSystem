#pragma once

#include <cstdint>

class IComponent;

////////////////////////////////////////////////////////////////////////////////
class IComponentDataContainer
{
public:
	virtual ComponentId			Add() = 0;
	virtual void				Remove(ComponentId index) = 0;
	virtual void				Reset(ComponentId index) = 0;
	virtual IComponent*			Get(ComponentId index) = 0;
};