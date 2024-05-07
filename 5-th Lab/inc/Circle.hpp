#pragma once
#include <SFML/Graphics.hpp>

namespace mt {
	class Circle
	{
	private:
		float m_r;
		float m_x, m_y;
		float m_dx, m_dy;
		float m_alfa;
		sf::CircleShape m_shape;

	public:
		Circle() = default;

		Circle(float x, float y, float r, float dx, float dy) {
			Setup(x, y, r, dx, dy);
		}

		void Setup(float x, float y, float r, float dx, float dy) {
			m_x = x;
			m_y = y;
			m_r = r;
			m_dx = dx;
			m_dy = dy;
			m_shape.setOrigin(m_r, m_r);
			m_shape.setRadius(m_r);
			m_shape.setPosition(m_x, m_y);
			int color_r = rand() % 256;
			int color_g = rand() % 256;
			int color_b = rand() % 256;
			m_shape.setFillColor(sf::Color::Color(color_r, color_g, color_b, 127));
		}
		sf::CircleShape Get()
		{
			return m_shape;
		}

		float X() { return m_x; }
		float Y() { return m_y; }
		float dx() { return m_dx; }
		float dy() { return m_dy; }
		float R() { return m_r; };

		void x(float x) {
			m_x = x;
		}
		void y(float y) {
			m_y = y;
		}
		void dx(float dx) {
			m_dx = -dx;
		}
		void dy(float dy) {
			m_dy = -dy;
		}

		void DY(float dy) {
			m_dy = dy;
		}
		void DX(float dx) {
			m_dx = dx;
		}

		void Move(float dt)
		{
			float vx = m_dx;
			float vy = m_dy;
			m_x += vx * dt;
			m_y += vy * dt;
			m_shape.setPosition(m_x, m_y);
		}
	};
}
