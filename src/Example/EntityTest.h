#pragma once

#include "Entity.h"
#include "Example/ITest.h"

////////////////////////////////////////////////////////////////////////////////
class EntityTest
	: public ITest
{
public:
	void Run(int32_t runs) final;

private:
	void CreateEntities(std::vector<Entity>& entities);
	void AddRandomComponents(std::vector<Entity>& entities);
	void RemoveEntities(std::vector<Entity>& entities);
	void RemoveComponents(std::vector<Entity>& entities);
	void IterateComponents();
};