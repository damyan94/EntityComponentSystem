#pragma once

#include <vector>

#include "Example/ITest.h"

#include "Defines.h"
#include "Entity.h"

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