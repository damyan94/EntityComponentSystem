#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Transform
	: public IComponent
{
	DECLARE_COMPONENT(Transform);

public:
	struct Position
	{
		float X = 0;
		float Y = 0;
		float Z = 0;
	};

	struct Rotation
	{
		float X = 0;
		float Y = 0;
		float Z = 0;
	};

	struct Scale
	{
		float X = 1.0f;
		float Y = 1.0f;
		float Z = 1.0f;
	};

public:
	Transform();
	~Transform();

	void				Reset() final;

	void				SetPosition(Position position);
	void				SetRotation(Rotation rotation);
	void				SetScale(Scale scale);

	Position			GetPosition() const;
	Rotation			GetRotation() const;
	Scale				GetScale() const;

private:
	Position			m_Position;
	Rotation			m_Rotation;
	Scale				m_Scale;
};