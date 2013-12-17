//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_MENU_HPP
#define SNK_MENU_HPP


#include "debug_text.hpp"

#include <functional>


namespace snk
{
	enum class difficulty_modes : char{easy, normal, hard, none};

	class menu
	{
		debug_text m_title{"consola.ttf"};
		bool m_is_active{true};

	public:
		std::function<void(difficulty_modes mode)> m_on_choose;

		menu()
		{
			m_title.set_text("MENU\n\nChoose a difficulty:\nEasy(e)\nNormal(n)\nHard(h)");
			m_title.set_position({200, 150});
		}

		void update() noexcept
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {m_on_choose(difficulty_modes::easy); m_is_active = false;}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {m_on_choose(difficulty_modes::normal); m_is_active = false;}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {m_on_choose(difficulty_modes::hard); m_is_active = false;}
		}

		bool is_active() const noexcept
		{return m_is_active;}

		auto drawable() const noexcept
		-> decltype((m_title.drawable()))
		{return m_title.drawable();}
	};
}



#endif // SNK_MENU_HPP
