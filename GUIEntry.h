#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "FontManager.h"

struct GUIEntry
{
	GUIEntry(FontManager* fontManager, const std::string& text, const sf::Vector2f& position, const std::string& fontName, const unsigned int charSize)
	{
		if (fontManager->requireResource(fontName))
		{
			m_font = *fontManager->getResource(fontName);
		}
		m_text.setFont(m_font);
		m_text.setPosition(position);
		m_text.setString(text);
		m_text.setCharacterSize(charSize);
	}

	sf::Text m_text;
	sf::Vector2f m_position;
	sf::Font m_font;

};