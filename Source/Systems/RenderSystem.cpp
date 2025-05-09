#include <stdafx.h>

#include "Systems/RenderSystem.h"

#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "GameObject.h"
#include "Example/DrawManager.h"

/*
* Average normalized access times for each mode. 1.0 was measured to be 37 microseconds
* 
*				|	RenderAllFromParent	| RenderAllZOrdered	| RenderAllSeparateGetComponent	| RenderAllSeparateIndexing
* ----------------------------------------------------------------------------------------------------------------------
*	Release		|					4.5	|				2.6	|							1.7	|						1.0
*	Debug		|				   62.2 |			   29.9 |						   15.0 |						7.6
* 
*/

int32_t RenderSystem::m_ImagesDrawn = 0;
int32_t RenderSystem::m_TextsDrawn = 0;

// Hack but should be ok, since the vector size is not changed
static const auto& _transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
static const auto& _images = ComponentDataManager::Instance().GetAllComponents<Image>();
static const auto& _texts = ComponentDataManager::Instance().GetAllComponents<Text>();

////////////////////////////////////////////////////////////////////////////////
void RenderSystem::RenderAllFromParent(const GameObject* obj)
{
	const auto transformId = obj->GetComponentId(EComponentType::Transform);
	ReturnIf(transformId == INVALID_COMPONENT_ID);

	const auto& transform = _transforms[transformId];

	if (const auto imageId = obj->GetComponentId(EComponentType::Image) != INVALID_COMPONENT_ID)
	{
		const auto& image = _images[imageId];
		DrawManager::Instance().RenderRandomImage(transform);
		m_ImagesDrawn++;
	}

	if (const auto textId = obj->GetComponentId(EComponentType::Text) != INVALID_COMPONENT_ID)
	{
		const auto& text = _texts[textId];
		DrawManager::Instance().RenderRandomImage(transform);
		m_TextsDrawn++;
	}

	/////

	//const auto transform = obj->GetComponent<Transform>();

	//const auto image = obj->GetComponent<Image>();
	//if (image)
	//{
	//	//DrawManager::Instance().RenderRandomImage(transform);
	//	m_ImagesDrawn++;
	//}

	//const auto text = obj->GetComponent<Text>();
	//if (text)
	//{
	//	//DrawManager::Instance().RenderRandomImage(transform);
	//	m_TextsDrawn++;
	//}

	const auto& children = obj->GetAllChildren();
	ReturnIf(children.empty());

	for (const auto child : children)
	{
		RenderAllFromParent(child);		
	}
}

////////////////////////////////////////////////////////////////////////////////
void RenderSystem::RenderAllZOrdered()
{
	// Transforms should be sorted by z
	const auto& transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
	const auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
	const auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();

	const auto transformsCount = transforms.size();
	const auto imagesCount = images.size();
	const auto textsCount = texts.size();

	for (int32_t i = 0; i < transformsCount; i++)
	{
		const auto& transform = transforms[i];
		ContinueIf(!transform.Parent);

		const auto imageId = transform.Parent->GetComponentId(EComponentType::Image);
		if (imageId != INVALID_COMPONENT_ID)
		{
			const auto& image = images[imageId];
			DrawManager::Instance().RenderRandomImage(transform);
			m_ImagesDrawn++;
		}

		const auto textId = transform.Parent->GetComponentId(EComponentType::Text);
		if (textId != INVALID_COMPONENT_ID)
		{
			const auto& text = texts[textId];
			DrawManager::Instance().RenderRandomImage(transform);
			m_TextsDrawn++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
void RenderSystem::RenderAllSeparateGetComponent()
{
	// Transforms should be sorted by z
	const auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
	const auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();

	for (const auto& image : images)
	{
		ContinueIf(!image.IsValid || !image.Parent);

		const auto& transform = image.Parent->GetComponent<Transform>();
		DrawManager::Instance().RenderRandomImage(*transform);
		m_ImagesDrawn++;
	}
	
	for (const auto& text : texts)
	{
		ContinueIf(!text.IsValid || !text.Parent);

		const auto& transform = text.Parent->GetComponent<Transform>();
		DrawManager::Instance().RenderRandomImage(*transform);
		m_TextsDrawn++;
	}
}

////////////////////////////////////////////////////////////////////////////////
void RenderSystem::RenderAllSeparateIndexing()
{
	// Transforms should be sorted by z
	const auto& transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
	const auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
	const auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();

	for (const auto& image : images)
	{
		ContinueIf(!image.IsValid || !image.Parent);

		const auto transformId = image.Parent->GetComponentId(EComponentType::Transform);
		ContinueIf(transformId == INVALID_COMPONENT_ID);

		const auto& transform = transforms[transformId];
		DrawManager::Instance().RenderRandomImage(transform);
		m_ImagesDrawn++;
	}

	for (const auto& text : texts)
	{
		ContinueIf(!text.Parent);

		const auto transformId = text.Parent->GetComponentId(EComponentType::Transform);
		ContinueIf(transformId == INVALID_COMPONENT_ID);

		const auto& transform = transforms[transformId];
		DrawManager::Instance().RenderRandomImage(transform);
		m_TextsDrawn++;
	}
}

//////////////////////////////////////////////////////////////////////////////////
void RenderSystem::PrintItemsDrawn()
{
	Logger::Log(Format("Images drawn: {0}, Texts drawn: {1}.", m_ImagesDrawn, m_TextsDrawn));

	m_ImagesDrawn = 0;
	m_TextsDrawn = 0;
}