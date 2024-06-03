#pragma once

#include "Defines.h"
#include "ComponentType.h"

class Entity;

#define SET_COMPONENT_TYPE(ComponentType)										\
public:																			\
	static constexpr EComponentType Type = EComponentType::ComponentType;		\
	inline constexpr EComponentType GetType() const final { return Type; }

////////////////////////////////////////////////////////////////////////////////
// @brief When adding a new component class, you can use the DECLARE_COMPONENT
// macro with the new type name for convenience
class IComponent
{
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	virtual constexpr EComponentType GetType() const = 0;
	virtual inline void Reset()
	{
		IsValid = false;
		Parent = nullptr;
	}

	bool IsValid = false;
	Entity* Parent = nullptr;
};