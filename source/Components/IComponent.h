#pragma once

#include "Defines.h"
#include "ComponentType.h"

////////////////////////////////////////////////////////////////////////////////
class IComponent
{
public:
	virtual constexpr EComponentType GetType() const = 0;
	virtual void Reset() = 0;
};