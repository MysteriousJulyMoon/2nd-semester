#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{
	class Rectangle
	{
		float m_a, m_b;
		float m_x, m_y;
		sf::RectangleShape m_rectangle;
	public:
		Rectangle() = default;
		Rectangle(float x, float y, float a, float b)
		{
			Setup(x, y, a, b);
		}
		void Setup(float x, float y, float a, float b)
		{
			m_x = x;
			m_y = y;
			m_a = a;
			m_b = b;
			m_rectangle.setSize(sf::Vector2f(m_a, m_b));
			m_rectangle.setPosition(m_x, m_y);
			m_rectangle.setFillColor(sf::Color::Color(255, 0, 0, 255));
		}
		sf::RectangleShape Get()
		{
			return m_rectangle;
		}
	};
}
