#pragma once

#include <vector>

#include "Defines.h"
#include "Entity.h"

class GameObject;

using GameObjectVector = std::vector<GameObject*>;

////////////////////////////////////////////////////////////////////////////////
class GameObject
	: public Entity
{
public:
	GameObject();
	~GameObject();

	void				AddChild(GameObject* child);
	void				AddChildren(GameObjectVector children);

	void				RemoveChild(int32_t index);
	void				RemoveAllChildren();

	GameObject*			GetChild(int32_t index) const;
	GameObjectVector	GetAllChildren() const;

	void				SetParent(GameObject* parent);
	GameObject*			GetParent() const;

private:
	bool				HasChild(int32_t index) const;

private:
	GameObject*			m_Parent;
	GameObjectVector	m_Children;
};