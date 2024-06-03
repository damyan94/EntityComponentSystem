#include "Systems/RenderSystem.h"

#include "Defines.h"
#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "GameObject.h"

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

////////////////////////////////////////////////////////////////////////////////
void RenderSystem::RenderAllFromParent(const GameObject* parent)
{
	const auto& children = parent->GetAllChildren();
	ReturnIf(children.empty());

	for (const auto child : children)
	{
		RenderAllFromParent(child);

		const auto transform = child->GetComponent<Transform>();

		const auto image = child->GetComponent<Image>();
		if (image)
		{
			//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
			m_ImagesDrawn++;
		}

		const auto text = child->GetComponent<Text>();
		if (text)
		{
			//DrawManager::Instance().RenderIndividual(texture/*text.GetTextureId()*/, transform);
			m_TextsDrawn++;
		}
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
			//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
			m_ImagesDrawn++;
		}

		const auto textId = transform.Parent->GetComponentId(EComponentType::Text);
		if (textId != INVALID_COMPONENT_ID)
		{
			const auto& text = texts[textId];
			//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
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
		//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
		m_ImagesDrawn++;
	}
	
	for (const auto& text : texts)
	{
		ContinueIf(!text.IsValid || !text.Parent);

		const auto& transform = text.Parent->GetComponent<Transform>();
		//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
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

	const auto transformsCount = transforms.size();
	const auto imagesCount = images.size();
	const auto textsCount = texts.size();

	for (const auto& image : images)
	{
		ContinueIf(!image.IsValid || !image.Parent);

		const auto transformId = image.Parent->GetComponentId(EComponentType::Transform);
		ContinueIf(transformId == INVALID_COMPONENT_ID);

		const auto& transform = transforms[transformId];
		//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
		m_ImagesDrawn++;
	}

	for (const auto& text : texts)
	{
		ContinueIf(!text.Parent);

		const auto transformId = text.Parent->GetComponentId(EComponentType::Transform);
		ContinueIf(transformId == INVALID_COMPONENT_ID);

		const auto& transform = transforms[transformId];
		//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
		m_TextsDrawn++;
	}
}

//////////////////////////////////////////////////////////////////////////////////
void RenderSystem::PrintItemsDrawn()
{
	Utils::LogConsole("Images drawn: " + std::to_string(m_ImagesDrawn) +
		", Texts drawn: " + std::to_string(m_TextsDrawn));

	m_ImagesDrawn = 0;
	m_TextsDrawn = 0;
}