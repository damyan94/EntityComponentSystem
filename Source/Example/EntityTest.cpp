#include <stdafx.h>

#include "Example/EntityTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

////////////////////////////////////////////////////////////////////////////////
void EntityTest::Run(int32_t runs)
{
	Logger::Log("Running EntityTest ...");

	Time clock;
	m_AverageTestStatistics.Reset();

	for (int32_t j = 0; j < runs; j++)
	{
		m_TestStatistics.Reset();
		auto start = clock.GetNow();

		std::vector<Entity> entities;
		CreateEntities(entities);
		AddRandomComponents(entities);
		RemoveEntities(entities);
		RemoveComponents(entities);
		IterateComponents();

		auto finish = clock.GetNow();

		m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
		m_AverageTestStatistics += m_TestStatistics;

		m_TestStatistics.Display();
	}

	Logger::Log("Finished running EntityTest. Averages:", ETextColor::Green);

	m_AverageTestStatistics /= runs;
	m_AverageTestStatistics.Display(ETextColor::Green);
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::CreateEntities(std::vector<Entity>& entities)
{
	entities.resize(50000);
	m_TestStatistics.Created = (int32_t)entities.size();
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::AddRandomComponents(std::vector<Entity>& entities)
{
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
			m_TestStatistics.ComponentsChanged++;
		}

		if (Utils::Probability(30))
		{
			entity.AddComponent<Image>();
			m_TestStatistics.ComponentsAdded++;
		}

		if (Utils::Probability(50))
		{
			entity.AddComponent<Text>();
			m_TestStatistics.ComponentsAdded++;
		}

		if (Utils::Probability(20))
		{
			entity.AddComponent<Action>();
			m_TestStatistics.ComponentsAdded++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::RemoveEntities(std::vector<Entity>& entities)
{
	for (int32_t i = 0; i < entities.size() / 2; i++)
	{
		if (Utils::Probability(20))
		{
			entities.pop_back();
			m_TestStatistics.Destroyed++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::RemoveComponents(std::vector<Entity>& entities)
{
	for (auto& entity : entities)
	{
		if (Utils::Probability(30))
		{
			entity.RemoveComponent<Image>();
			m_TestStatistics.ComponentsRemoved++;
		}

		if (Utils::Probability(50))
		{
			entity.RemoveComponent<Text>();
			m_TestStatistics.ComponentsRemoved++;
		}

		if (Utils::Probability(20))
		{
			entity.RemoveComponent<Action>();
			m_TestStatistics.ComponentsRemoved++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::IterateComponents()
{
	auto& transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
	for (auto& item : transforms)
	{
		item.SetPosition(
			{
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100)
			});
		m_TestStatistics.ComponentsChanged++;
	}

	auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
	for (auto& item : images)
	{
		item.GetType();
	}

	auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();
	for (auto& item : texts)
	{
		if (Utils::Probability(30))
		{
			item.SetText("Hi");
			m_TestStatistics.ComponentsChanged++;
		}
	}

	auto& actions = ComponentDataManager::Instance().GetAllComponents<Action>();
	for (auto& item : actions)
	{
		item.Execute();
	}
}