#pragma once

#include <cstdint>

class GameObject;

////////////////////////////////////////////////////////////////////////////////
class RenderSystem
{
public:
	static void RenderAllFromParent(const GameObject* parent);
	static void RenderAllZOrdered();
	static void RenderAllSeparateGetComponent();
	static void RenderAllSeparateIndexing();

	static void PrintItemsDrawn();

private:
	static int32_t m_ImagesDrawn;
	static int32_t m_TextsDrawn;
};