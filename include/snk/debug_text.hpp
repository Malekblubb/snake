//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_DEBUG_TEXT_HPP
#define SNK_DEBUG_TEXT_HPP


#include <SFML/Graphics.hpp>


namespace snk
{
	class debug_text
	{
		sf::Font m_font;
		sf::Text m_text;

	public:
		debug_text(const std::string& font_file_name)
		{
			m_font.loadFromFile(font_file_name);
			m_text = {"nA", m_font, 20};
		}

		void set_text(const std::string& text) noexcept
		{m_text.setString(text);}

		void set_position(const sf::Vector2f& pos) noexcept
		{m_text.setPosition(pos);}

		auto drawable() const noexcept
		-> decltype((m_text))
		{return m_text;}
	};
}


#endif // SNK_DEBUG_TEXT_HPP
