#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Image
	: public IComponent
{
	DECLARE_COMPONENT(Image);

public:
	Image();
	~Image();

	void Reset() final;

private:

};