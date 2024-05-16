#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace sf
{
	class SpaceObject
	{
	protected:
		float m_x, m_y;
		float m_vx, m_vy;
		float m_r;
		sf::Texture m_textureObject;
		sf::Sprite m_spriteObject;

	public:
		SpaceObject() = default;
		virtual ~SpaceObject() {};

		bool Setup(float x, float y, float vx, float vy, const std::string& TexturePath, float ScaleFactor)
		{
			m_x = x;
			m_y = y;
			m_vx = vx;
			m_vy = vy;

			// Загрузка текстуры фона
			if (!m_textureObject.loadFromFile(TexturePath))
			{
				std::cout << "Error while loading" << TexturePath << std::endl;
				return false;
			}
			m_spriteObject.setTexture(m_textureObject);

			m_spriteObject.setScale(ScaleFactor, ScaleFactor);
			m_spriteObject.setOrigin(m_textureObject.getSize().x / 2., m_textureObject.getSize().y / 2.);
			m_spriteObject.setPosition(m_x, m_y);
			//m_spriteShip.setRotation(m_alpha);

			if (m_textureObject.getSize().x > m_textureObject.getSize().y)
				m_r = ScaleFactor * m_textureObject.getSize().x / 2;
			else
				m_r = ScaleFactor * m_textureObject.getSize().y / 2;

		}

		sf::Sprite Get()
		{
			return m_spriteObject;
		}

		void Move(float dt)
		{
			m_x += m_vx  * dt;
			m_y += m_vy  * dt;
			m_spriteObject.setPosition(m_x, m_y);
		}
		virtual void Attack() = 0;
		virtual void SpecialAbility() = 0;
	};
}