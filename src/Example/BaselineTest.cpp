#include <stdafx.h>

#include "Example/BaselineTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#define UI_COUNT 25000
#define TILE_COUNT 15000
#define UNIT_COUNT 10000
#define TOTAL_COUNT UI_COUNT + TILE_COUNT + UNIT_COUNT

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::Run(int32_t runs)
{
	Logger::Log("Running BaselineTest ...");

	Time clock;
	m_AverageTestStatistics.Reset();

	for (int32_t j = 0; j < runs; j++)
	{
		m_TestStatistics.Reset();
		//auto start = clock.GetNow();

		CreateEntities();
		AddRandomComponents();
		RemoveEntities();
		RemoveComponents();
		IterateComponents();

		auto start = clock.GetNow();

		Render();

		auto finish = clock.GetNow();

		m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
		m_AverageTestStatistics += m_TestStatistics;

		m_TestStatistics.Display();
	}

	Logger::Log("Finished running BaselineTest. Averages:", ETextColor::Green);

	m_AverageTestStatistics /= runs;
	m_AverageTestStatistics.Display(ETextColor::Green);
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
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100)
			});
		m_TestStatistics.ComponentsChanged++;
	}

	for (auto& entity : m_Tiles)
	{
		entity.pos.SetPosition(
			{
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100)
			});
		m_TestStatistics.ComponentsChanged++;
	}

	for (auto& entity : m_Units)
	{
		entity.pos.SetPosition(
			{
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100),
				Utils::Random<float>(0, 100)
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
		item.pos.SetPosition({ 1, 1, 1 });
		m_TestStatistics.ComponentsChanged++;

		if (Utils::Probability(30))
		{
			item.text.SetText("Hi");
			m_TestStatistics.ComponentsChanged++;
		}
	}

	for (auto& item : m_Tiles)
	{
		item.pos.SetPosition({ 1, 1, 1 });
		m_TestStatistics.ComponentsChanged++;
	}

	for (auto& item : m_Units)
	{
		item.pos.SetPosition({ 1, 1, 1 });
		m_TestStatistics.ComponentsChanged++;
		item.action.Execute();
	}
}

////////////////////////////////////////////////////////////////////////////////
void BaselineTest::Render() const
{
	int32_t m_ImagesDrawn = 0;
	int32_t m_TextsDrawn = 0;

	const auto uiCount = m_UIs.size();
	const auto tileCount = m_Tiles.size();
	const auto unitCount = m_Units.size();

	for (int32_t i = 0; i < uiCount / 2; i++)
	{
		m_UIs[/*Utils::Random<size_t>(0, uiCount / 2)*/i].Render();
		m_TextsDrawn++;
	}

	for (int32_t i = 0; i < tileCount / 2; i++)
	{
		m_Tiles[/*Utils::Random<size_t>(0, tileCount / 2)*/i].Render();
		m_ImagesDrawn++;
	}

	for (int32_t i = 0; i < m_Units.size() / 2; i++)
	{
		m_Units[/*Utils::Random<size_t>(0, unitCount / 2)*/i].Render();
		m_ImagesDrawn++;
	}

	Logger::LogInfo(Format("Images drawn: {0}, Texts drawn: {1}.", m_ImagesDrawn, m_TextsDrawn));
}