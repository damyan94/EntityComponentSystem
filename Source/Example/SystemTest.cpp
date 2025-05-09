#include <stdafx.h>

#include "Example/SystemTest.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#include "Systems/RenderSystem.h"

#define MOTHER_OBJECTS_COUNT 55
#define CHILDREN_COUNT 100
#define TOTAL_OBJECTS MOTHER_OBJECTS_COUNT * CHILDREN_COUNT

////////////////////////////////////////////////////////////////////////////////
void SystemTest::Run(int32_t runs)
{
	auto runRenderAllFromParent = [this, runs](const std::string& name)
		{
			//Logger::Log(Format("Running SystemTest [{0}] ...", name));

			Time clock;
			m_AverageTestStatistics.Reset();

			for (int32_t j = 0; j < runs; j++)
			{
				m_TestStatistics.Reset();
				//auto start = clock.now();

				CreateGameObjects();
				AddRandomComponents();
				RemoveGameObjects();
				RemoveComponents();
				IterateComponents();

				auto start = clock.GetNow();
				RenderSystem::RenderAllFromParent(&m_Scene);

				auto finish = clock.GetNow();

				m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
				m_AverageTestStatistics += m_TestStatistics;

				m_TestStatistics.Display();
				//RenderSystem::PrintItemsDrawn();
			}

			//Logger::Log(Format("Finished running SystemTest [{0}]. Averages:", name), ETextColor::Green);

			m_AverageTestStatistics /= runs;
			//m_AverageTestStatistics.Display(ETextColor::Green);
		};

	auto run = [this, runs](const std::string& name, VoidFunction callback)
		{
			//Logger::Log(Format("Running SystemTest [{0}] ...", name));

			Time clock;
			m_AverageTestStatistics.Reset();

			for (int32_t j = 0; j < runs; j++)
			{
				m_TestStatistics.Reset();
				//auto start = clock.now();

				CreateGameObjects();
				AddRandomComponents();
				RemoveGameObjects();
				RemoveComponents();
				IterateComponents();

				auto start = clock.GetNow();
				callback();

				auto finish = clock.GetNow();

				m_TestStatistics.Duration = (finish - start).GetAs(EUnitOfTime::Microsecond);
				m_AverageTestStatistics += m_TestStatistics;

				m_TestStatistics.Display();
				//RenderSystem::PrintItemsDrawn();
			}

			//Logger::Log(Format("Finished running SystemTest [{0}]. Averages:", name), ETextColor::Green);

			m_AverageTestStatistics /= runs;
			//m_AverageTestStatistics.Display(ETextColor::Green);
		};

	//runRenderAllFromParent("RenderSystem::RenderAllFromParent");
	//run("RenderSystem::RenderAllZOrdered", RenderSystem::RenderAllZOrdered);
	//run("RenderSystem::RenderAllSeparateGetComponent", RenderSystem::RenderAllSeparateGetComponent);
	run("RenderSystem::RenderAllSeparateIndexing", RenderSystem::RenderAllSeparateIndexing);
}

////////////////////////////////////////////////////////////////////////////////
void SystemTest::Init()
{
	CreateGameObjects();
	AddRandomComponents();
}

////////////////////////////////////////////////////////////////////////////////
void SystemTest::Update()
{
	//RemoveGameObjects();
	//RemoveComponents();
	IterateComponents();
}

////////////////////////////////////////////////////////////////////////////////
void SystemTest::Render() const
{
	//RenderSystem::RenderAllFromParent(&scene);
	//RenderSystem::RenderAllZOrdered();
	//RenderSystem::RenderAllSeparateGetComponent();
	RenderSystem::RenderAllSeparateIndexing();
}

////////////////////////////////////////////////////////////////////////////////
void SystemTest::CreateGameObjects()
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
void SystemTest::AddRandomComponents()
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
void SystemTest::RemoveGameObjects()
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
void SystemTest::RemoveComponents()
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