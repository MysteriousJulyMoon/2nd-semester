#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <SpaceObject.hpp>
#include <UFO.hpp>
#include <Destroyer.hpp>
#include <SpaceGarbage.hpp>
#include <Asteroid.hpp>
#include <Comet.hpp>


namespace sf
{

	const float pi = acos(-1);

	class Game
	{
		const int m_bulletR = 10;
		int m_width;
		int m_height;
		std::string m_capture;
		sf::Circle* m_c;
		sf::Bullet m_b;
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
		float dt1 = 0;
		UFO ufo;
		Destroyer destroyer;
		std::vector<SpaceObject*> m_spaceObjects;
		Asteroid asteroid;
		Comet comet;
		std::vector<SpaceGarbage*> m_spaceGarbage;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		~Game()
		{
			for (int i = 0; i < m_spaceObjects.size(); i++) 
				delete m_spaceObjects[i];
			for (int i = 0; i < m_spaceGarbage.size(); i++)
				delete m_spaceGarbage[i];

			delete[] m_c;
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

			m_c = new sf::Circle[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 10;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;
				int v = rand() % 50 + 100;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}
			m_spaceObjects.push_back(new UFO);
			m_spaceObjects[0]->Setup(400, 400, 1, 0, "assets\\UFO.png", 0.07f);

			m_spaceObjects.push_back(new Destroyer);
			m_spaceObjects[1]->Setup(800, 800, 0, 1, "assets\\Destroyer.png", 0.26f);

			m_spaceGarbage.push_back(new Asteroid);
			m_spaceGarbage[0]->Setup(800, 300, 300, 1, 1, "assets\\Asteroid.png", 0.26f);

			m_spaceGarbage.push_back(new Comet);
			m_spaceGarbage[1]->Setup(1920, 0, 300, -7, 7, "assets\\Comet.png", 0.26f);
		}

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


				dt1 += 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (dt1 > 500) {
						m_ship.Attack();
						float m_v = m_ship.V();
						float m_x = m_ship.X();
						float m_y = m_ship.Y();
						float m_alpha = m_ship.Alpha();
						float m_v_bullet = 200;
						float alphaRad = acos(-1) * m_alpha / 180;
						m_b.Setup(m_x, m_y, m_bulletR, (m_v + m_v_bullet) * cos(alphaRad), (m_v + m_v_bullet) * sin(alphaRad));
						bullets.push_back(m_b);
						destroyer.Attack();
						dt1 = 0;
					}
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

				for (int i = 0; i < m_spaceObjects.size(); i++) {
					m_spaceObjects[i]->Move(dt);
				}

				for (int i = 0; i < m_spaceGarbage.size(); i++) {
					m_spaceGarbage[i]->Move(dt);
				}

				m_fpsText.setString(std::to_string(1 / dt));

				// Отображение
				m_window.clear();

				m_window.draw(m_spriteBackground);

				m_window.draw(m_fpsText);

				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());

				for (int i = 0; i < m_spaceObjects.size(); i++) {
					m_window.draw(m_spaceObjects[i]->Get());
				}

				for (int i = 0; i < m_spaceGarbage.size(); i++) {
					m_window.draw(m_spaceGarbage[i]->Get());
				}
				
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