#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>
#include <Bullet.hpp>

namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		const int m_bulletR = 10;
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		mt::Bullet m_b;
		std::vector<Bullet> bullets;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Ship m_ship;
		bool isVisible = true;
		bool isTouchBorder = true;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Setup(int n)
		{
			m_n = n;
			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);

			// Загрузка текстуры фона
			if (!m_textureBackground.loadFromFile("assets\\background.jpg"))
			{
				std::cout << "Error while loading background.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			// Загрузка шрифта
			if (!m_font.loadFromFile("assets\\arial.ttf"))
			{
				std::cout << "Error while loading arial.ttf" << std::endl;
				return false;
			}
			m_fpsText.setFont(m_font);

			// Создание корабля игрока
			if (!m_ship.Setup(100, 100))
				return false;

			srand(time(0));

			m_c = new mt::Circle[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 10;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;
				int v = rand() % 50 + 100;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}
		}

		//void TouchBorder(Circle& obj)
		//{
		//	float x = obj.X();
		//	float y = obj.Y();
		//	float r = obj.R();


		//	if (isTouchBorder)
		//	{
		//		isTouchBorder = false;

		//		if (x + r >= m_width || x - r <= 0)
		//		{
		//			obj.Alfa(pi - obj.Alfa());
		//		}

		//		if (y + r >= m_height || y - r <= 0)
		//		{
		//			obj.Alfa(2 * pi - obj.Alfa());
		//		}

		//	}
		//	else
		//	{
		//		if (x + r + 20 <= m_width || x - r - 20 >= 0)
		//		{
		//			isTouchBorder = true;
		//		}

		//		if (y + r + 20 <= m_height || y - r - 20 >= 0)
		//		{
		//			isTouchBorder = true;
		//		}
		//	}

		//}

		//void Collision(int i)
		//{
		//	Circle& c = m_c[i];
		//	float dist = sqrt(pow(m_ship.X() - c.X(), 2) + pow(m_ship.Y() - c.Y(), 2));
		//	if (m_ship.R() + c.R() >= dist)
		//	{
		//		std::cout << "Collision " << m_ship.V() << std::endl;
		//		isVisible = false;
		//	}
		//}

		void delete_Circle(Circle& obj, Bullet& obj2) {
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();
			/*std::cout << x << " " << y << " " << r << "   ";*/
			float x1 = obj2.X();
			float y1 = obj2.Y();
			float r1 = obj2.R();
			/*std::cout << x1 << " " << y1 << " " << r1 << std::endl;*/
			float Dx = x - x1;
			float Dy = y - y1;
			float dist = sqrt(pow(Dx, 2) + pow(Dy, 2));
			if (dist < r + r1) {
				obj.~Circle();
				obj2.BulletReset();
			}
		}

		void LifeCycle()
		{
			sf::Clock clock;


			while (m_window.isOpen())
			{
				// Обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				// Обработка клавиатуры TODO
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_ship.setVelocity(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_ship.setVelocity(-1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_ship.Rotate(-0.5);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_ship.Rotate(0.5);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					m_ship.Attack();
					float m_v = m_ship.V();
					float m_x = m_ship.X();
					float m_y = m_ship.Y();
					float m_alpha = m_ship.Alpha();
					float m_v_bullet = 200;
					float alphaRad = acos(-1) * m_alpha / 180;
					m_b.Setup(m_x, m_y, m_bulletR, (m_v + m_v_bullet) * cos(alphaRad), (m_v + m_v_bullet) * sin(alphaRad));
					bullets.push_back(m_b);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					m_ship.BulletReset();
				}

				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				for (int i = 0; i < m_n; i++) {
					for (int j = 0; j < bullets.size(); j++)
					delete_Circle(m_c[i], bullets[j]);
				}

				for (int i = 0; i < m_n; i++)
				{
					float x = m_c[i].X();
					float y = m_c[i].Y();
					float r = m_c[i].R();
					float v = m_c[i].V();
					float alfa = m_c[i].Alfa();

					float x_s = x + v * cos(alfa) * dt;
					float y_s = y + v * sin(alfa) * dt;


					bool collision = false;
					if (x_s + r >= m_width)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(m_width - r);
						collision = true;
					}

					if (x_s - r <= 0)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(r);
						collision = true;
					}

					if (y_s + r >= m_height)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(m_height - r);
						collision = true;
					}

					if (y_s - r <= 0)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(r);
						collision = true;
					}

					if (!collision)
					{
						m_c[i].X(x_s);
						m_c[i].Y(y_s);
					}
				}
				m_b.Move(dt);
				for(int i = 0; i < bullets.size(); i++)
					bullets[i].Move(dt);
				// Перемещение корабля
				m_ship.Move(dt);

				m_fpsText.setString(std::to_string(1 / dt));

				// Отображение
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_fpsText);
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());

				//std::cout << m_ship.BulletAvailable() << std::endl;

				if (m_ship.BulletAvailable())
					for(int i = 0; i < bullets.size(); i++)
					m_window.draw(bullets[i].Get());
				if (isVisible)
					m_window.draw(m_ship.Get());
				m_window.display();


			}
		}
	};
}