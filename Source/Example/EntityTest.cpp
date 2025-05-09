#include <stdafx.h>

#include "Example/EntityTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#include "Example/DrawManager.h"

#define ENTITY_COUNT 500

////////////////////////////////////////////////////////////////////////////////
void EntityTest::Run(int32_t runs)
{
	//Logger::Log("Running EntityTest ...");

	Time clock;
	m_AverageTestStatistics.Reset();

	for (int32_t j = 0; j < runs; j++)
	{
		m_TestStatistics.Reset();

		Init();
		Update();

		auto start = clock.GetNow();

		Render();

		auto finish = clock.GetNow();

		m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
		m_AverageTestStatistics += m_TestStatistics;

		//m_TestStatistics.Display();
	}

	//Logger::Log("Finished running EntityTest. Averages:", ETextColor::Green);

	m_AverageTestStatistics /= runs;
	//m_AverageTestStatistics.Display(ETextColor::Green);
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::Init()
{
	CreateEntities();
	AddRandomComponents();
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::Update()
{
	//RemoveEntities();
	//RemoveComponents();
	IterateComponents();
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::Render() const
{
	auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
	for (const auto& item : images)
	{
		auto pos = item.Parent->GetComponent<Transform>();
		DrawManager::Instance().RenderRandomImage(*pos);
	}

	auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();
	for (const auto& item : texts)
	{
		auto pos = item.Parent->GetComponent<Transform>();
		DrawManager::Instance().RenderRandomImage(*pos);
	}
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::CreateEntities()
{
	m_Entities.resize(ENTITY_COUNT);
	m_TestStatistics.Created = (int32_t)m_Entities.size();
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::AddRandomComponents()
{
	for (auto& entity : m_Entities)
	{
		auto transform = entity.GetComponent<Transform>();
		if (transform)
		{
			transform->SetPosition(
				{
					Utils::Random<float>(0.0f, 1000.0f),
					Utils::Random<float>(0.0f, 1000.0f),
					Utils::Random<float>(0.0f, 1000.0f)
				});
			m_TestStatistics.ComponentsChanged++;
		}

		if (m_ImagesAdded < ENTITY_COUNT / 2 && Utils::Probability(70))
		{
			entity.AddComponent<Image>();
			m_TestStatistics.ComponentsAdded++;
			m_ImagesAdded++;
		}

		if (m_TextsAdded < ENTITY_COUNT / 2 && Utils::Probability(70))
		{
			entity.AddComponent<Text>();
			m_TestStatistics.ComponentsAdded++;
			m_TextsAdded++;
		}

		if (Utils::Probability(20))
		{
			entity.AddComponent<Action>();
			m_TestStatistics.ComponentsAdded++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::RemoveEntities()
{
	for (int32_t i = 0; i < m_Entities.size() / 2; i++)
	{
		if (Utils::Probability(20))
		{
			m_Entities.pop_back();
			m_TestStatistics.Destroyed++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void EntityTest::RemoveComponents()
{
	for (auto& entity : m_Entities)
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
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
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
			//item.SetText("Hi");
			m_TestStatistics.ComponentsChanged++;
		}
	}

	auto& actions = ComponentDataManager::Instance().GetAllComponents<Action>();
	for (auto& item : actions)
	{
		item.Execute();
	}
}