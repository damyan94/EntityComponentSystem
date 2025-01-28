#include <stdafx.h>

#include "Example/SystemTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#include "Systems/RenderSystem.h"

////////////////////////////////////////////////////////////////////////////////
void SystemTest::Run(int32_t runs)
{

	auto run = [this, runs](const std::string& name, VoidFunction callback)
		{
			Logger::Log(Format("Running SystemTest [{0}] ...", name));

			Time clock;
			m_AverageTestStatistics.Reset();

			for (int32_t j = 0; j < runs; j++)
			{
				m_TestStatistics.Reset();
				//auto start = clock.now();

				GameObject scene;
				CreateGameObjects(scene);
				AddRandomComponents(scene);
				RemoveGameObjects(scene);
				RemoveComponents(scene);
				IterateComponents();

				auto start = clock.GetNow();
				callback();

				auto finish = clock.GetNow();

				m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
				m_AverageTestStatistics += m_TestStatistics;

				m_TestStatistics.Display();
				RenderSystem::PrintItemsDrawn();
			}

			Logger::Log(Format("Finished running SystemTest [{0}]. Averages:", name), ETextColor::Green);

			m_AverageTestStatistics /= runs;
			m_AverageTestStatistics.Display(ETextColor::Green);
		};

	//RenderSystem::RenderAllFromParent(&scene);
	//RenderSystem::RenderAllZOrdered();
	//RenderSystem::RenderAllSeparateGetComponent();
	//RenderSystem::RenderAllSeparateIndexing();

	//run("RenderSystem::RenderAllFromParent", RenderSystem::RenderAllFromParent);
	run("RenderSystem::RenderAllZOrdered", RenderSystem::RenderAllZOrdered);
	run("RenderSystem::RenderAllSeparateGetComponent", RenderSystem::RenderAllSeparateGetComponent);
	run("RenderSystem::RenderAllSeparateIndexing", RenderSystem::RenderAllSeparateIndexing);
}

////////////////////////////////////////////////////////////////////////////////
void SystemTest::CreateGameObjects(GameObject& scene)
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
void SystemTest::AddRandomComponents(GameObject& scene)
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
void SystemTest::RemoveGameObjects(GameObject& scene)
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
void SystemTest::RemoveComponents(GameObject& scene)
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
void SystemTest::IterateComponents()
{
	auto& transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
	for (auto& item : transforms)
	{
		item.SetPosition({ 1, 1, 1 });
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