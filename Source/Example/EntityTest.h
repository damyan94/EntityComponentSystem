#pragma once

#include "Entity.h"
#include "Example/ITest.h"

////////////////////////////////////////////////////////////////////////////////
class EntityTest
	: public ITest
{
public:
	void Run(int32_t runs) final;
	void Init() final;
	void Update() final;
	void Render() const final;

private:
	void CreateEntities();
	void AddRandomComponents();
	void RemoveEntities();
	void RemoveComponents();
	void IterateComponents();

	std::vector<Entity> m_Entities;

	size_t m_ImagesAdded = 0;
	size_t m_TextsAdded = 0;
};