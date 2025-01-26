#include "stdafx.h"

#include "GameObject.h"

////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject()
	: m_Parent(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
GameObject::~GameObject()
{
	RemoveAllChildren();
}

////////////////////////////////////////////////////////////////////////////////
void GameObject::AddChild(GameObject* child)
{
	AssertReturnIf(!child);

	child->m_Parent = this;
	m_Children.emplace_back(child);
}

////////////////////////////////////////////////////////////////////////////////
void GameObject::AddChildren(GameObjectVector children)
{
	ReturnIf(children.empty());

	m_Children.reserve(m_Children.size() + children.size());
	for (auto child : children)
	{
		AssertContinueIf(!child);

		child->m_Parent = this;
		m_Children.emplace_back(child);
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObject::RemoveChild(int32_t index)
{
	AssertReturnIf(!HasChild(index));

	SafeDelete(m_Children[index]);
	m_Children.erase(m_Children.begin() + index);
}

////////////////////////////////////////////////////////////////////////////////
void GameObject::RemoveAllChildren()
{
	ReturnIf(m_Children.empty());

	for (auto child : m_Children)
	{
		SafeDelete(child);
	}

	m_Children.clear();
}

////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::GetChild(int32_t index) const
{
	AssertReturnIf(!HasChild(index), nullptr);

	return m_Children[index];
}

////////////////////////////////////////////////////////////////////////////////
const GameObjectVector& GameObject::GetAllChildren() const
{
	return m_Children;
}

////////////////////////////////////////////////////////////////////////////////
void GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::GetParent() const
{
	return m_Parent;
}

////////////////////////////////////////////////////////////////////////////////
bool GameObject::HasChild(int32_t index) const
{
	return !m_Children.empty() && index >= 0 && index < m_Children.size();
}