#pragma once

#include "Defines.h"
#include "ComponentType.h"
#include "Components/IComponent.h"

////////////////////////////////////////////////////////////////////////////////
class Text
	: public IComponent
{
	SET_COMPONENT_TYPE(Text);

public:
	Text();
	~Text();

	void				Reset() final;

	void				SetText(const std::string& text);
	void				SetText(std::string&& text);
	const std::string&	GetText() const;

private:
	std::string			m_Text;
};