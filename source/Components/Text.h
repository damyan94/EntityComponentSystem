#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Text
	: public IComponent
{
public:
	static constexpr EComponentType Type = EComponentType::Text;

public:
	Text();
	~Text();

	constexpr EComponentType GetType() const final;
	void				Reset() final;

	void				SetText(const std::string& text);
	const std::string&	GetText() const;

private:
	std::string			m_Text;
};