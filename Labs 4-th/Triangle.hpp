#pragma once
#include<SFML/Graphics.hpp>

namespace mt
{
	class Triangle
	{
		float m_r;
		float m_x, m_y;
		sf::CircleShape m_shape;
	public:
		Triangle() = default;
		Triangle(float r, float x, float y)
		{
			Setup(x, y, r);
		}
		void Setup(float r, float x, float y)
		{
			m_r = r;
			m_x = x;
			m_y = y;
			m_shape.setRadius(m_r);
			m_shape.setPosition(m_x, m_y);
			m_shape.setPointCount(3);
			m_shape.setFillColor(sf::Color::Color(255, 0, 0, 255));
		}
		sf::CircleShape Get()
		{
			return m_shape;
		}
		
	};
}
