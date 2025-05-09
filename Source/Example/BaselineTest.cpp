#include <stdafx.h>

#include "Example/BaselineTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#include "Example/DrawManager.h"

#define UI_COUNT 2500
#define TILE_COUNT 1500
#define UNIT_COUNT 1000
#define TOTAL_COUNT UI_COUNT + TILE_COUNT + UNIT_COUNT

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::Run(int32_t runs)
{
	//Logger::Log("Running BaselineTest ...");

	Time clock;
	m_AverageTestStatistics.Reset();

	for (int32_t j = 0; j < runs; j++)
	{
		m_TestStatistics.Reset();
		//auto start = clock.GetNow();

		Init();
		Update();

		auto start = clock.GetNow();

		Render();

		auto finish = clock.GetNow();

		m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
		m_AverageTestStatistics += m_TestStatistics;

		m_TestStatistics.Display();
	}

	//Logger::Log("Finished running BaselineTest. Averages:", ETextColor::Green);

	m_AverageTestStatistics /= runs;
	//m_AverageTestStatistics.Display(ETextColor::Green);
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::Init()
{
	CreateEntities();
	AddRandomComponents();
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::Update()
{
	//RemoveEntities();
	//RemoveComponents();
	IterateComponents();
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::Render() const
{
	int32_t m_ImagesDrawn = 0;
	int32_t m_TextsDrawn = 0;

	for (const auto& item : m_UIs)
	{
		item.Render();
		m_TextsDrawn++;
	}

	for (const auto& item : m_Tiles)
	{
		item.Render();
		m_ImagesDrawn++;
	}

	for (const auto& item : m_Units)
	{
		item.Render();
		m_ImagesDrawn++;
	}

	//Logger::Log(Format("Images drawn: {0}, Texts drawn: {1}.", m_ImagesDrawn, m_TextsDrawn));
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::CreateEntities()
{
	m_UIs.resize(UI_COUNT);
	m_Tiles.resize(TILE_COUNT);
	m_Units.resize(UNIT_COUNT);
	m_TestStatistics.Created = TOTAL_COUNT;

	m_TestStatistics.ComponentsAdded = UI_COUNT * 1 + TILE_COUNT * 1 + UNIT_COUNT * 2;
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::AddRandomComponents()
{
	for (auto& entity : m_UIs)
	{
		entity.pos.SetPosition(
			{
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
			});
		m_TestStatistics.ComponentsChanged++;
	}

	for (auto& entity : m_Tiles)
	{
		entity.pos.SetPosition(
			{
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
			});
		m_TestStatistics.ComponentsChanged++;
	}

	for (auto& entity : m_Units)
	{
		entity.pos.SetPosition(
			{
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
			});
		m_TestStatistics.ComponentsChanged++;
	}
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::RemoveEntities()
{
	for (int32_t i = 0; i < m_UIs.size() / 2; i++)
	{
		if (Utils::Probability(20))
		{
			m_UIs.pop_back();
			m_TestStatistics.Destroyed++;
		}
	}

	for (int32_t i = 0; i < m_Tiles.size() / 2; i++)
	{
		if (Utils::Probability(20))
		{
			m_Tiles.pop_back();
			m_TestStatistics.Destroyed++;
		}
	}

	for (int32_t i = 0; i < m_Units.size() / 2; i++)
	{
		if (Utils::Probability(20))
		{
			m_Units.pop_back();
			m_TestStatistics.Destroyed++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::RemoveComponents()
{
	/*for (auto& entity : entities)
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
	}*/
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::IterateComponents()
{
	for (auto& item : m_UIs)
	{
		item.pos.SetPosition(
			{
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
			});
		m_TestStatistics.ComponentsChanged++;

		if (Utils::Probability(30))
		{
			//item.text.SetText("Hi");
			m_TestStatistics.ComponentsChanged++;
		}
	}

	for (auto& item : m_Tiles)
	{
		item.pos.SetPosition(
			{
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
			});
		m_TestStatistics.ComponentsChanged++;
	}

	for (auto& item : m_Units)
	{
		item.pos.SetPosition(
			{
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f),
				Utils::Random<float>(0.0f, 1000.0f)
			});
		m_TestStatistics.ComponentsChanged++;
		item.action.Execute();
	}
}