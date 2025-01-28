#pragma once

#include "Entity.h"
#include "Example/ITest.h"

#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "Components/Action.h"

#include "Example/DrawManager.h"

////////////////////////////////////////////////////////////////////////////////
class BaselineTest
	: public ITest
{
public:
	void Run(int32_t runs) final;

private:
	void CreateEntities();
	void AddRandomComponents();
	void RemoveEntities();
	void RemoveComponents();
	void IterateComponents();

	void Render() const;

private:
	////////////////////////////////////////////////////////////////////////////////
	class UI
	{
	public:
		Transform pos;
		float b;
		Text text;
		bool a;
		int16_t c;

		void Render() const
		{
			DrawManager::Instance().RenderRandomImage(pos);
		}
	};

	////////////////////////////////////////////////////////////////////////////////
	class Tile
	{
	public:
		Transform pos;
		bool a;
		float b;
		int16_t c;
		Image image;

		void Render() const
		{
			DrawManager::Instance().RenderRandomImage(pos);
		}
	};

	////////////////////////////////////////////////////////////////////////////////
	class Unit
	{
	public:
		int16_t c;
		Transform pos;
		bool a;
		float b;
		Image image;
		Action action;

		void Render() const
		{
			DrawManager::Instance().RenderRandomImage(pos);
		}
	};

private:
	std::vector<UI> m_UIs;
	std::vector<Tile> m_Tiles;
	std::vector<Unit> m_Units;
};