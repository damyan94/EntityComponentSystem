#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Action
	: public IComponent
{
	DECLARE_COMPONENT(Action);

public:
	Action();
	~Action();

	void				Reset() final;

	void				SetAction(VoidFunction callback);
	void				Execute();

private:
	VoidFunction		m_Callback;
};