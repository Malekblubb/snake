//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_GAME_HPP
#define SNK_GAME_HPP


#include "debug_text.hpp"
#include "fruit_handler.hpp"
#include "menu.hpp"
#include "snake.hpp"

#include <mlk/time/time.h>
#include <mlk/tools/stl_string_utl.h>

#include <SFML/Graphics.hpp>


namespace snk
{
	struct difficulty_values
	{
		static constexpr mlk::ullong m_easy_move_interval{100};
		static constexpr mlk::ullong m_easy_spawn_interval{5000};

		static constexpr mlk::ullong m_hard_move_interval{10};
		static constexpr mlk::ullong m_hard_spawn_interval{500};
	};

	class game
	{
		sf::RenderWindow m_window;

		snake m_snake_player;
		fruit_handler m_fh;
		debug_text m_debug_text{"consola.ttf"};
		menu m_menu;

		bool m_running{false};
		bool m_paused{false};
		bool m_debug{false};

	public:
		game(const sf::VideoMode& size, const std::string& title) :
			m_window{size, title},
			m_snake_player{{size.width / 2.f, size.height / 2.f}}
		{
			m_snake_player.m_on_self_hit = [this]{this->stop();};
			m_menu.m_on_choose = [this](difficulty_modes mode){this->menu_choose(mode);};
		}

		int run()
		{
			m_running = true;
			while(m_running)
			{
				auto start(mlk::tm::time_pnt());

				this->update();

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
		void menu_choose(difficulty_modes mode) noexcept
		{
			switch (mode)
			{
			case difficulty_modes::easy:
				m_snake_player.set_move_interval(difficulty_values::m_easy_move_interval);
				m_fh.set_spawn_interval(difficulty_values::m_easy_spawn_interval);
				break;
			case difficulty_modes::normal: break;
			case difficulty_modes::hard:
				m_snake_player.set_move_interval(difficulty_values::m_hard_move_interval);
				m_fh.set_spawn_interval(difficulty_values::m_hard_spawn_interval);
			default:
				break;
			}
		}

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

		void update()
		{
			this->update_events();

			if(m_menu.is_active())
				m_menu.update();
			else
				this->update_game();

			this->render();
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

			if(!m_menu.is_active())
			{
				for(const auto& body_part : m_snake_player.body())
					m_window.draw(body_part);

				for(const auto& fruit : m_fh.fruits())
					m_window.draw(fruit);
			}

			if(m_debug)
				m_window.draw(m_debug_text.drawable());

			if(m_menu.is_active())
				m_window.draw(m_menu.drawable());

			m_window.display();
		}
	};
}


#endif // SNK_GAME_HPP
