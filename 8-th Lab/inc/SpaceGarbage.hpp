#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace sf {

	class SpaceGarbage 
	{
	protected:
		float m_r;
		float m_x, m_y;
		float m_vx, m_vy;
		float m_alfa;
		sf::CircleShape m_shape;
		sf::Texture m_textureGarbage;
		sf::Sprite m_spriteGarbage;

	public:
		SpaceGarbage() = default;
		virtual ~SpaceGarbage() {};

		bool Setup(float x, float y, float r, float vx, float vy, const std::string& TexturePath, float ScaleFactor)
		{
			m_x = x;
			m_y = y;
			m_r = r;
			m_vx = vx;
			m_vy = vy;

			// Загрузка текстуры фона
			if (!m_textureGarbage.loadFromFile(TexturePath))
			{
				std::cout << "Error while loading" << TexturePath << std::endl;
				return false;
			}
			m_spriteGarbage.setTexture(m_textureGarbage);

			m_spriteGarbage.setScale(ScaleFactor, ScaleFactor);
			m_spriteGarbage.setOrigin(m_textureGarbage.getSize().x / 2., m_textureGarbage.getSize().y / 2.);
			m_spriteGarbage.setPosition(m_x, m_y);
			//m_spriteShip.setRotation(m_alpha);

			if (m_textureGarbage.getSize().x > m_textureGarbage.getSize().y)
				m_r = ScaleFactor * m_textureGarbage.getSize().x / 2;
			else
				m_r = ScaleFactor * m_textureGarbage.getSize().y / 2;

		}

		sf::Sprite Get()
		{
			return m_spriteGarbage;
		}

		void Move(float dt)
		{
			m_x += m_vx * dt;
			m_y += m_vy * dt;
			m_spriteGarbage.setPosition(m_x, m_y);
		}

		virtual void SpecialAbility() = 0;
	};

}