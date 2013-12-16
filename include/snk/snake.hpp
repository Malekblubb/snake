//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_SNAKE_HPP
#define SNK_SNAKE_HPP


#include <mlk/time/time.h>
#include <mlk/types/types.h>

#include <SFML/Graphics.hpp>


namespace snk
{
	class snake
	{
		static constexpr float m_snake_size{10.f};
		static constexpr float m_snake_velo{10.f};
		static constexpr mlk::ullong m_snake_move_interval{50};

		std::vector<sf::RectangleShape> m_drawables;
		sf::Vector2f m_velo;
		mlk::hrs_time_pnt m_last_move{mlk::tm::time_pnt()};

	public:
		snake(const sf::Vector2f& pos)
		{
			m_drawables.emplace_back(sf::RectangleShape{{m_snake_size, m_snake_size}});
			m_drawables[0].setPosition(pos);
			m_drawables[0].setFillColor({0, 255, 0});
		}

		void update()
		{
			this->try_move();

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {this->reset_velo(); m_velo.y = -m_snake_velo;}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {this->reset_velo(); m_velo.y = m_snake_velo;}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {this->reset_velo(); m_velo.x = -m_snake_velo;}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {this->reset_velo(); m_velo.x = m_snake_velo;}
		}

		void add_body_part()
		{
			auto l_pos(this->last_body_part().getPosition());
			m_drawables.emplace_back(sf::RectangleShape{{m_snake_size, m_snake_size}});
			m_drawables.back().setPosition(l_pos);
		}

		auto body() const noexcept
		-> decltype((m_drawables))
		{return m_drawables;}

	private:
		void try_move() noexcept
		{
			if(!mlk::tm::timed_out(m_last_move, m_snake_move_interval))
				return;

			// get head pos before move
			auto last_pos(this->head().getPosition());

			// move head
			m_drawables[0].move(m_velo);

			// move body
			for(auto iter(m_drawables.begin() + 1); iter != m_drawables.end(); ++iter)
			{
				auto pre_pos(iter->getPosition());
				iter->setPosition(last_pos);
				last_pos = pre_pos;
			}

			m_last_move = mlk::tm::time_pnt();
		}

		void reset_velo() noexcept
		{m_velo = {0, 0};}

		auto head() noexcept
		-> decltype((m_drawables.front()))
		{return m_drawables.front();}

		auto last_body_part() noexcept
		-> decltype((m_drawables.back()))
		{return m_drawables.back();}
	};
}


#endif // SNK_SNAKE_HPP
