#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Image
	: public IComponent
{
public:
	static constexpr EComponentType Type = EComponentType::Image;

public:
	Image();
	~Image();

	constexpr EComponentType GetType() const final;
	void Reset() final;

private:

};