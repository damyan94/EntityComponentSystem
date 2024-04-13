#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Action
	: public IComponent
{
public:
	static constexpr EComponentType Type = EComponentType::Action;

public:
	Action();
	~Action();

	constexpr EComponentType GetType() const final;
	void				Reset() final;

	void				SetAction(VoidFunction callback);
	void				Execute();

private:
	VoidFunction		m_Callback;
};