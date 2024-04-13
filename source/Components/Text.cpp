#include "Components/Text.h"

////////////////////////////////////////////////////////////////////////////////
Text::Text()
{
}

////////////////////////////////////////////////////////////////////////////////
Text::~Text()
{
}

////////////////////////////////////////////////////////////////////////////////
void Text::Reset()
{
	m_Text.clear();
}

////////////////////////////////////////////////////////////////////////////////
void Text::SetText(const std::string& text)
{
	m_Text = text;
}

////////////////////////////////////////////////////////////////////////////////
const std::string& Text::GetText() const
{
	return m_Text;
}