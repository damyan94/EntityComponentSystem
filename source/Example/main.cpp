#include <cstdint>
#include <vector>
#include <chrono>

#include "Defines.h"
#include "Entity.h"

#include "Utils/Random.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

int32_t main(int32_t argC, char** argV)
{
	srand((uint32_t)time(nullptr));

	// Run test 1000 times
	for (int32_t j = 0; j < 1000; j++)
	{
		int32_t created = 0;
		int32_t destroyed = 0;
		int32_t componentsAdded = 0;
		int32_t componentsChanged = 0;
		int32_t componentsRemoved = 0;

		std::chrono::system_clock clock;
		auto start = clock.now();

		// Create 500 entities, assign and change components on random
		std::vector<Entity> entities;
		entities.resize(500);
		created = entities.size();

		for (auto& entity : entities)
		{
			auto transform = entity.GetComponent<Transform>();
			if (transform)
			{
				transform->SetPosition(
					{
						Utils::Random<float>(0, 100),
						Utils::Random<float>(0, 100),
						Utils::Random<float>(0, 100)
					});
				componentsChanged++;
			}

			if (Utils::Probability(30))
			{
				entity.AddComponent<Image>();
				componentsAdded++;
			}

			if (Utils::Probability(50))
			{
				entity.AddComponent<Text>();
				componentsAdded++;
			}

			if (Utils::Probability(20))
			{
				entity.AddComponent<Action>();
				componentsAdded++;
			}
		}

		// Randomly remove some entities
		for (int32_t i = 0; i < entities.size() / 2; i++)
		{
			if (Utils::Probability(20))
			{
				entities.pop_back();
				destroyed++;
			}
		}

		// Randomly remove some components
		for (auto& entity : entities)
		{
			if (Utils::Probability(30))
			{
				entity.RemoveComponent<Image>();
				componentsRemoved++;
			}

			if (Utils::Probability(50))
			{
				entity.RemoveComponent<Text>();
				componentsRemoved++;
			}

			if (Utils::Probability(20))
			{
				entity.RemoveComponent<Action>();
				componentsRemoved++;
			}
		}

		auto finish = clock.now();

		Log(std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count()) + " microseconds" +
		" | created: " + std::to_string(created) +
		" | destroyed: " + std::to_string(destroyed) +
		" | componentsAdded: " + std::to_string(componentsAdded) +
		" | componentsChanged: " + std::to_string(componentsChanged) +
		" | componentsRemoved: " + std::to_string(componentsRemoved));
	}

	system("pause");
	return EXIT_SUCCESS;
}