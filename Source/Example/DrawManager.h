#pragma once

#include "Components/Transform.h"

#define IMAGES_COUNT 3
#define IMAGE_WIDTH 64
#define IMAGE_HEIGHT 64

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

////////////////////////////////////////////////////////////////////////////////
struct Point
{
	int32_t x;
	int32_t y;
};

////////////////////////////////////////////////////////////////////////////////
struct Rectangle
{
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
};

////////////////////////////////////////////////////////////////////////////////
struct DrawCommand
{
	size_t ImageId;
	Rectangle SourceRectangle;
	Rectangle DestinationRectangle;
};

////////////////////////////////////////////////////////////////////////////////
class DrawManager
{
private:
	DrawManager();

public:
	~DrawManager();

	static DrawManager& Instance();

	bool Init(bool headless);
	void Deinit();
	void Update();

	void ClearScreen();
	void RenderRandomImage(const Transform& transform);
	void Render(const DrawCommand& drawCmd);
	void FinishFrame();

	size_t GetDrawCalls() const;

private:
	SDL_Surface* CreateSurfaceFromFile(const std::string& filename);
	SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);
	void LoadResources();

private:
	std::vector<SDL_Texture*> m_ImagesToDraw;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	size_t m_DrawCalls;
	bool m_Headless;
};