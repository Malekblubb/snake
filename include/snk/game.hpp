//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_GAME_HPP
#define SNK_GAME_HPP


#include "debug_text.hpp"
#include "fruit_handler.hpp"
#include "snake.hpp"

#include <mlk/time/time.h>
#include <mlk/tools/stl_string_utl.h>

#include <SFML/Graphics.hpp>


namespace snk
{
	class game
	{
		sf::RenderWindow m_window;

		snake m_snake_player;
		fruit_handler m_fh;
		debug_text m_debug_text{"consola.ttf"};

		bool m_running{false};
		bool m_paused{false};
		bool m_debug{false};

	public:
		game(const sf::VideoMode& size, const std::string& title) :
			m_window{size, title},
			m_snake_player{{size.width / 2.f, size.height / 2.f}}
		{m_snake_player.m_on_self_hit = [this]{this->stop();};}

		int run()
		{
			m_running = true;
			while(m_running)
			{
				auto start(mlk::tm::time_pnt());

				this->update_events();
				this->update_game();
				this->render();

				auto end(mlk::tm::time_pnt());
				auto duration(mlk::tm::duration_as<float>(start, end));
				m_debug_text.set_text("Update duration: " + mlk::stl_string::to_string(duration) +
									  "\nFPS: " + mlk::stl_string::to_string(1.f / (duration / 1000.f)));
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
					case sf::Keyboard::D: m_debug = !m_debug; break;
					default: break;
					}
		}

		void update_game()
		{
			if(this->is_paused()) return;

			m_snake_player.update();
			m_fh.update();
			if(m_fh.check_collision(m_snake_player.body().at(0)))
				m_snake_player.add_body_part();
		}

		void render() noexcept
		{
			m_window.clear();

			for(const auto& body_part : m_snake_player.body())
				m_window.draw(body_part);

			for(const auto& fruit : m_fh.fruits())
				m_window.draw(fruit);

			if(m_debug)
				m_window.draw(m_debug_text.drawable());

			m_window.display();
		}
	};
}


#endif // SNK_GAME_HPP
