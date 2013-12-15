#include <iostream>
#include <SFML/Graphics.hpp>
#include <mlk/time/time_utl.h>


using namespace std;


constexpr float snake_size{10.f};
constexpr float snake_velo{10.f};
constexpr mlk::ullong snake_move_interval{50};

class snake
{
	std::vector<sf::RectangleShape> m_drawables;
	sf::Vector2f m_velo;
	mlk::hrs_time_pnt m_last_move{mlk::tm::time_pnt()};


public:
	snake(const sf::Vector2f& pos)
	{
		m_drawables.emplace_back(sf::RectangleShape{{snake_size, snake_size}});
		m_drawables[0].setPosition(pos);
		m_drawables[0].setFillColor({0, 255, 0});
	}

	void update()
	{
		this->try_move();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {this->reset_velo(); m_velo.y = -snake_velo;}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {this->reset_velo(); m_velo.y = snake_velo;}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {this->reset_velo(); m_velo.x = -snake_velo;}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {this->reset_velo(); m_velo.x = snake_velo;}
	}

	void add_body_part()
	{
		auto l_pos(this->last_body_part().getPosition());
		m_drawables.emplace_back(sf::RectangleShape{{snake_size, snake_size}});
		m_drawables.back().setPosition({l_pos.x, l_pos.y});
	}

	auto body() const noexcept
	-> decltype((m_drawables))
	{return m_drawables;}

private:
	void try_move() noexcept
	{
		if(mlk::tm::timed_out(m_last_move, snake_move_interval))
		{
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



int main()
{
	sf::RenderWindow window;
	window.create({600, 600}, "Snake");

	snake s{{300, 300}};

	auto running(true);
	auto paused(false);

	while(running)
	{
		window.clear();

		sf::Event e;
		while(window.pollEvent(e))
			if(e.type  == sf::Event::EventType::KeyPressed)
				switch(e.key.code)
				{
				case sf::Keyboard::Escape: running = false; break;
				case sf::Keyboard::Space:
				case sf::Keyboard::P: paused = !paused; break;
				default: break;
				}

		std::cout << paused << std::endl;
		// snake
		if(!paused)
		{
			s.update();

		}
		for(auto& body_part : s.body()) window.draw(body_part);
		window.display();
	}

	return 0;
}

