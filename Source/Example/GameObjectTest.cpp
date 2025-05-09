#include <stdafx.h>

#include "Example/GameObjectTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#include "Example/DrawManager.h"

#define MOTHER_OBJECTS_COUNT 50
#define CHILDREN_COUNT 100
#define TOTAL_OBJECTS MOTHER_OBJECTS_COUNT * CHILDREN_COUNT

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::Run(int32_t runs)
{
	//Logger::Log("Running GameObjectTest ...");

	Time clock;
	m_AverageTestStatistics.Reset();

	for (int32_t j = 0; j < runs; j++)
	{
		m_TestStatistics.Reset();
		auto start = clock.GetNow();

		CreateGameObjects();
		AddRandomComponents();
		RemoveGameObjects();
		RemoveComponents();
		IterateComponents();

		auto finish = clock.GetNow();

		m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
		m_AverageTestStatistics += m_TestStatistics;

		//m_TestStatistics.Display();
	}

	//Logger::Log("Finished running GameObjectTest. Averages:", ETextColor::Green);

	m_AverageTestStatistics /= runs;
	//m_AverageTestStatistics.Display(ETextColor::Green);
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::Init()
{
	CreateGameObjects();
	AddRandomComponents();
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::Update()
{
	//RemoveGameObjects();
	//RemoveComponents();
	IterateComponents();
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::Render() const
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
void GameObjectTest::CreateGameObjects()
{
	for (int32_t i = 0; i < MOTHER_OBJECTS_COUNT; i++)
	{
		m_Scene.AddChild(new GameObject);
		m_TestStatistics.Created++;
	}

	for (auto gameObject : m_Scene.GetAllChildren())
	{
		GameObjectVector children;
		children.resize(CHILDREN_COUNT);
		for (int32_t i = 0; i < children.size(); i++)
		{
			children[i] = new GameObject;
			m_TestStatistics.Created++;
		}

		gameObject->AddChildren(children);
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::AddRandomComponents()
{
	for (auto object : m_Scene.GetAllChildren())
	{
		for (auto child : object->GetAllChildren())
		{
			auto transform = child->GetComponent<Transform>();
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

			if (m_ImagesAdded < TOTAL_OBJECTS / 2 && Utils::Probability(70))
			{
				child->AddComponent<Image>();
				m_TestStatistics.ComponentsAdded++;
				m_ImagesAdded++;
			}

			if (m_TextsAdded < TOTAL_OBJECTS / 2 && Utils::Probability(70))
			{
				child->AddComponent<Text>();
				m_TestStatistics.ComponentsAdded++;
				m_TextsAdded++;
			}

			if (Utils::Probability(20))
			{
				child->AddComponent<Action>();
				m_TestStatistics.ComponentsAdded++;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::RemoveGameObjects()
{
	for (int32_t i = 0; i < m_Scene.GetAllChildren().size(); i++)
	{
		if (Utils::Probability(10))
		{
			m_TestStatistics.Destroyed++;
			m_TestStatistics.Destroyed += (int32_t)m_Scene.GetChild(i)->GetAllChildren().size();
			m_Scene.RemoveChild(i);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::RemoveComponents()
{
	for (auto object : m_Scene.GetAllChildren())
	{
		for (auto child : object->GetAllChildren())
		{
			if (Utils::Probability(30))
			{
				child->RemoveComponent<Image>();
				m_TestStatistics.ComponentsRemoved++;
			}

			if (Utils::Probability(50))
			{
				child->RemoveComponent<Text>();
				m_TestStatistics.ComponentsRemoved++;
			}

			if (Utils::Probability(20))
			{
				child->RemoveComponent<Action>();
				m_TestStatistics.ComponentsRemoved++;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::IterateComponents()
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