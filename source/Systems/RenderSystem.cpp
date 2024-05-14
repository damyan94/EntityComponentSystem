#include "Systems/RenderSystem.h"

#include "Defines.h"
#include "ComponentDataManager.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/Text.h"
#include "GameObject.h"

int32_t RenderSystem::m_ImagesDrawn = 0;
int32_t RenderSystem::m_TextsDrawn = 0;

////////////////////////////////////////////////////////////////////////////////
void RenderSystem::RenderAllFromParent(const GameObject* parent)
{
	const auto& children = parent->GetAllChildren();
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
void RenderSystem::RenderAll()
{
	// Transforms should be sorted by z
	const auto& transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
	const auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
	const auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();

	const auto imagesCount = images.size();
	const auto textsCount = texts.size();
	const auto transformsCount = transforms.size();

	for (int32_t i = 0; i < transformsCount; i++)
	{
		const auto& transform = transforms[i];

		ContinueIf(!transform.Parent);

		const auto imageId = transform.Parent->GetComponentId(EComponentType::Image);
		if (imageId != INVALID_COMPONENT_ID)
		{
			const auto& image = images[transform.Parent->GetComponentId(EComponentType::Image)];
			//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
			m_ImagesDrawn++;
		}

		const auto textId = transform.Parent->GetComponentId(EComponentType::Text);
		if (textId != INVALID_COMPONENT_ID)
		{
			const auto& text = texts[transform.Parent->GetComponentId(EComponentType::Text)];
			//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
			m_TextsDrawn++;
		}
	}


	//for (int32_t i = 0; i < images.size(); i++)
	//{
	//	const auto& transform = transforms[i];
	//	//const auto transform = image.Parent->GetComponent<Transform>();
	//	//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
	//	m_ImagesDrawn++;
	//}
	//
	//for (int32_t i = 0; i < texts.size(); i++)
	//{
	//	const auto& transform = transforms[i];
	//	//const auto transform = image.Parent->GetComponent<Transform>();
	//	//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
	//	m_TextsDrawn++;
	//}


	//for (const auto& image : images)
	//{
	//	//const auto transform = transforms[rand() % transforms.size()];
	//	//const auto transform = image.Parent->GetComponent<Transform>();
	//	//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
	//	m_ImagesDrawn++;
	//}

	//for (const auto& text : texts)
	//{
	//	//const auto transform = transforms[rand() % transforms.size()];
	//	//const auto transform = image.Parent->GetComponent<Transform>();
	//	//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
	//	m_TextsDrawn++;
	//}
}

//////////////////////////////////////////////////////////////////////////////////
//void RenderSystem::RenderAll(const GameObject* parent)
//{
//	// Transforms should be sorted by z
//	const auto& transforms = ComponentDataManager::Instance().GetAllComponents<Transform>();
//	const auto& images = ComponentDataManager::Instance().GetAllComponents<Image>();
//	const auto& texts = ComponentDataManager::Instance().GetAllComponents<Text>();
//
//	// da ima edin ob6t konteiner za vsi4ki ne6ta deto 6te se risuvat
//	for (const auto& image : images)
//	{
//		//const auto transformId = image.GetTransformId();
//		//AssertContinueIf(transformId < 0);
//
//		//const auto* texture = AssetManager::Instance().GetImageTexture(image.GetTextureId()); //moje bi tova da e v drawManager-a?
//		//DrawManager::Instance().RenderIndividual(texture/*image.GetTextureId()*/, transform);
//	}
//}

//////////////////////////////////////////////////////////////////////////////////
void RenderSystem::PrintItemsDrawn()
{
	Utils::LogConsole("Images drawn: " + std::to_string(m_ImagesDrawn) +
		", Texts drawn: " + std::to_string(m_TextsDrawn));

	m_ImagesDrawn = 0;
	m_TextsDrawn = 0;
}