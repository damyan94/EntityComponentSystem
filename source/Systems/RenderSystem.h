#pragma once

#include <cstdint>

class GameObject;

////////////////////////////////////////////////////////////////////////////////
class RenderSystem
{
public:
	static void RenderAllFromParent(const GameObject* parent);
	static void RenderAll();
	//static void RenderAll(const GameObject* parent);

	static void PrintItemsDrawn();

private:
	static int32_t m_ImagesDrawn;
	static int32_t m_TextsDrawn;
};