//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_FRUIT_HANDLER_HPP
#define SNK_FRUIT_HANDLER_HPP


#include "collision.hpp"

#include <mlk/time/time.h>
#include <mlk/tools/random_utl.h>

#include <SFML/Graphics.hpp>

#include <vector>


namespace snk
{
	class fruit_handler
	{
		mlk::ullong m_interval{2000};

		std::vector<sf::RectangleShape> m_fruits;
		mlk::hrs_time_pnt m_last_added{mlk::tm::time_pnt()};

	public:
		fruit_handler() = default;

		void update()
		{this->try_generate_fruit();}

		void set_spawn_interval(mlk::ullong interval) noexcept
		{m_interval = interval;}

		bool check_collision(const sf::RectangleShape& o)
		{
			collision<sf::RectangleShape> coll{o};
			for(auto iter(m_fruits.begin()); iter != m_fruits.end(); ++iter)
				if(coll.is_colliding(*iter))
				{
					m_fruits.erase(iter);
					return true;
				}
			return false;
		}

		auto fruits()
		-> decltype((m_fruits))
		{return m_fruits;}

	private:
		void try_generate_fruit() noexcept
		{
			if(!mlk::tm::timed_out(m_last_added, m_interval))
				return;
			this->generate_fruit_impl();
		}

		void generate_fruit_impl() noexcept
		{
			auto x(mlk::rnd(0, 600));
			auto y(mlk::rnd(0, 600));
			m_fruits.emplace_back(sf::RectangleShape{{10.f, 10.f}});
			m_fruits.back().setPosition(x, y);
			m_fruits.back().setFillColor({255, 0, 0});
			m_last_added = mlk::tm::time_pnt();
		}
	};
}



#endif // SNK_FRUIT_HANDLER_HPP
