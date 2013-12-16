//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef SNK_COLLISION_HPP
#define SNK_COLLISION_HPP


namespace snk
{
	template<typename T>
	class collision
	{
		const T& m_object;

	public:
		collision(const T& object) :
			m_object{object}
		{ }

		bool is_colliding(const T& other) const noexcept
		{
			return this->right_out(m_object) >= this->left_out(other) &&
					this->left_out(m_object) <= this->right_out(other) &&
					this->bottom_out(m_object) >= this->top_out(other) &&
					this->top_out(m_object) <= this->bottom_out(other);
		}

	private:
		float pos_x(const T& object) const noexcept
		{return object.getPosition().x;}

		float pos_y(const T& object) const noexcept
		{return object.getPosition().y;}

		float top_out(const T& object) const noexcept
		{return this->pos_y(object) - (object.getSize().y / 2.f);}

		float bottom_out(const T& object) const noexcept
		{return this->pos_y(object) + (object.getSize().y / 2.f);}

		float left_out(const T& object) const noexcept
		{return this->pos_x(object) - (object.getSize().x / 2.f);}

		float right_out(const T& object) const noexcept
		{return this->pos_x(object) + (object.getSize().x / 2.f);}
	};
}


#endif // SNK_COLLISION_HPP
