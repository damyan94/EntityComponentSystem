#pragma once

#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Image
	: public IComponent
{
	SET_COMPONENT_TYPE(Image);

public:
	Image();
	~Image();

	void Reset() final;

private:

};