#pragma once

#include "GameObject.h"
#include "Example/ITest.h"

////////////////////////////////////////////////////////////////////////////////
class SystemTest
	: public ITest
{
public:
	void Run(int32_t runs) final;
	void Init() final;
	void Update() final;
	void Render() const final;

private:
	void CreateGameObjects();
	void AddRandomComponents();
	void RemoveGameObjects();
	void RemoveComponents();
	void IterateComponents();

	GameObject m_Scene;

	size_t m_ImagesAdded = 0;
	size_t m_TextsAdded = 0;
};