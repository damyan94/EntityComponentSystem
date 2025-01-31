#include <stdafx.h>

#include "Example/GameObjectTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::Run(int32_t runs)
{
	Logger::Log("Running GameObjectTest ...");

	Time clock;
	m_AverageTestStatistics.Reset();

	for (int32_t j = 0; j < runs; j++)
	{
		m_TestStatistics.Reset();
		auto start = clock.GetNow();

		GameObject scene;
		CreateGameObjects(scene);
		AddRandomComponents(scene);
		RemoveGameObjects(scene);
		RemoveComponents(scene);
		IterateComponents();

		auto finish = clock.GetNow();

		m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
		m_AverageTestStatistics += m_TestStatistics;

		m_TestStatistics.Display();
	}

	Logger::Log("Finished running GameObjectTest. Averages:", ETextColor::Green);

	m_AverageTestStatistics /= runs;
	m_AverageTestStatistics.Display(ETextColor::Green);
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::CreateGameObjects(GameObject& scene)
{
	for (int32_t i = 0; i < 500; i++)
	{
		scene.AddChild(new GameObject);
		m_TestStatistics.Created++;
	}

	for (auto gameObject : scene.GetAllChildren())
	{
		GameObjectVector children;
		children.resize(100);
		for (int32_t i = 0; i < children.size(); i++)
		{
			children[i] = new GameObject;
			m_TestStatistics.Created++;
		}

		gameObject->AddChildren(children);
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::AddRandomComponents(GameObject& scene)
{
	for (auto object : scene.GetAllChildren())
	{
		for (auto child : object->GetAllChildren())
		{
			auto transform = child->GetComponent<Transform>();
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
				child->AddComponent<Image>();
				m_TestStatistics.ComponentsAdded++;
			}

			if (Utils::Probability(50))
			{
				child->AddComponent<Text>();
				m_TestStatistics.ComponentsAdded++;
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
void GameObjectTest::RemoveGameObjects(GameObject& scene)
{
	for (int32_t i = 0; i < scene.GetAllChildren().size(); i++)
	{
		if (Utils::Probability(10))
		{
			m_TestStatistics.Destroyed++;
			m_TestStatistics.Destroyed += (int32_t)scene.GetChild(i)->GetAllChildren().size();
			scene.RemoveChild(i);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void GameObjectTest::RemoveComponents(GameObject& scene)
{
	for (auto object : scene.GetAllChildren())
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