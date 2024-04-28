#pragma once

#include <vector>

#include "Example/ITest.h"

#include "Defines.h"
#include "GameObject.h"

////////////////////////////////////////////////////////////////////////////////
class GameObjectTest
	: public ITest
{
public:
	void Run(int32_t runs) final;

private:
	void CreateGameObjects(GameObject& scene);
	void AddRandomComponents(GameObject& scene);
	void RemoveGameObjects(GameObject& scene);
	void RemoveComponents(GameObject& scene);
	void IterateComponents();
};