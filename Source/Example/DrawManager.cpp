#include <stdafx.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Example/DrawManager.h"

////////////////////////////////////////////////////////////////////////////////
DrawManager::DrawManager()
	: m_Window(nullptr)
	, m_Renderer(nullptr)
	, m_DrawCalls(0)
	, m_Headless(true)
{
	//AssertIf(!Init());
}

////////////////////////////////////////////////////////////////////////////////
DrawManager::~DrawManager()
{
	Deinit();
}

////////////////////////////////////////////////////////////////////////////////
DrawManager& DrawManager::Instance()
{
	static DrawManager instance;
	return instance;
}

////////////////////////////////////////////////////////////////////////////////
bool DrawManager::Init(bool headless)
{
	m_Headless = headless;

	AssertReturnIf(EXIT_SUCCESS != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO)
		&& SDL_GetError(), false);

	AssertReturnIf(EXIT_SUCCESS == (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
		&& SDL_GetError(), false);

	/*AssertReturnIf(EXIT_SUCCESS != TTF_Init()
		&& SDL_GetError(), false);

	AssertReturnIf(0 > Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048)
		&& SDL_GetError(), false);*/

	m_Window = SDL_CreateWindow("Test", 100, 100, 1280, 720, 36);
	AssertReturnIf(!m_Window, false);

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	//m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	AssertReturnIf(!m_Renderer, false);

	LoadResources();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::Deinit()
{
	for (auto& image : m_ImagesToDraw)
	{
		ContinueIf(!image);

		SDL_DestroyTexture(image);
		image = nullptr;
	}

	/*Mix_Quit();
	TTF_Quit();*/
	IMG_Quit();
	SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::Update()
{
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::ClearScreen()
{
	m_DrawCalls = 0;
	
	if (!m_Headless)
	{
		SDL_RenderClear(m_Renderer);
	}
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::RenderRandomImage(const Transform& transform)
{
	const Rectangle src{ 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT };
	const Rectangle dst{ (int)transform.GetPosition().X, (int)transform.GetPosition().Y, IMAGE_WIDTH, IMAGE_HEIGHT };

	DrawManager::Instance().Render(DrawCommand(Utils::Random<size_t>(0, IMAGES_COUNT - 1), src, dst));
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::Render(const DrawCommand& drawCmd)
{
	const auto texture = m_ImagesToDraw[drawCmd.ImageId];
	SDL_Rect srcRect{ drawCmd.SourceRectangle.x, drawCmd.SourceRectangle.y, drawCmd.SourceRectangle.w, drawCmd.SourceRectangle.h };
	SDL_Rect dstRect{ drawCmd.DestinationRectangle.x, drawCmd.DestinationRectangle.y, drawCmd.DestinationRectangle.w, drawCmd.DestinationRectangle.h };

	if (!m_Headless)
	{
		SDL_RenderCopyEx(m_Renderer, texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
	}

	m_DrawCalls++;
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::FinishFrame()
{
	if (!m_Headless)
	{
		SDL_RenderPresent(m_Renderer);
	}
	//Logger::Log(Format("Draw calls: {0}.", m_DrawCalls));
}

////////////////////////////////////////////////////////////////////////////////
SDL_Surface* DrawManager::CreateSurfaceFromFile(const std::string& filename)
{
	SDL_Surface* result = nullptr;

	result = IMG_Load(filename.c_str());

	return result;
}

////////////////////////////////////////////////////////////////////////////////
SDL_Texture* DrawManager::CreateTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* result = nullptr;

	AssertReturnIf(!surface, nullptr);

	result = SDL_CreateTextureFromSurface(m_Renderer, surface);
	SDL_FreeSurface(surface);
	surface = nullptr;

	return result;
}

////////////////////////////////////////////////////////////////////////////////
void DrawManager::LoadResources()
{
	m_ImagesToDraw.emplace_back(CreateTextureFromSurface(CreateSurfaceFromFile("../../Assets/Images/1.png")));
	m_ImagesToDraw.emplace_back(CreateTextureFromSurface(CreateSurfaceFromFile("../../Assets/Images/2.png")));
	m_ImagesToDraw.emplace_back(CreateTextureFromSurface(CreateSurfaceFromFile("../../Assets/Images/3.png")));
}