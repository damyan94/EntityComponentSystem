#include <stdafx.h>

#include "Components/Action.h"

////////////////////////////////////////////////////////////////////////////////
Action::Action()
	: m_Callback(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
Action::~Action()
{
}

////////////////////////////////////////////////////////////////////////////////
void Action::Reset()
{
	m_Callback = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
void Action::SetAction(VoidFunction callback)
{
	m_Callback = callback;
}

////////////////////////////////////////////////////////////////////////////////
void Action::Execute()
{
	if (m_Callback)
	{
		m_Callback();
	}
}