#pragma once

#include "GameObject.h"
#include "Example/ITest.h"

////////////////////////////////////////////////////////////////////////////////
class SystemTest
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