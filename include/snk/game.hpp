//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_GAME_HPP
#define SNK_GAME_HPP


#include "snake.hpp"

#include <SFML/Graphics.hpp>


namespace snk
{
	class game
	{
		sf::RenderWindow m_window;

		snake m_snake_player;

		bool m_running{false};
		bool m_paused{false};

	public:
		game(const sf::VideoMode& size, const std::string& title) :
			m_window{size, title},
			m_snake_player{{size.width / 2.f, size.height / 2.f}}
		{ }

		int run()
		{
			m_running = true;
			while(m_running)
			{
				m_window.clear();
				this->update_events();
				this->render();
				m_window.display();
			}

			return 0;
		}

		void stop() noexcept
		{m_running = false;}

		bool is_paused() const noexcept
		{return m_paused;}

	private:
		void update_events() noexcept
		{
			sf::Event e;
			while(m_window.pollEvent(e))
				if(e.type == sf::Event::EventType::KeyPressed)
					switch(e.key.code)
					{
					case sf::Keyboard::Escape: this->stop(); break;
					case sf::Keyboard::Space:
					case sf::Keyboard::P: m_paused = !m_paused; break;
					default: break;
					}
		}

		void render() noexcept
		{
			if(!this->is_paused())
				m_snake_player.update();

			for(const auto& body_part : m_snake_player.body())
				m_window.draw(body_part);
		}
	};
}


#endif // SNK_GAME_HPP
