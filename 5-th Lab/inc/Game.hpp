#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <math.h>
#include <cmath>

namespace mt {

	const float pi = acos(-1);

	class Game {
	private:
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;

	public:
		Game(int width, int height, const std::string& capture) {
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		void Setup(int n) {

			m_n = n;

			m_window.create(sf::VideoMode(m_width, m_height), m_capture);
			m_window.setTitle(m_capture);

			m_c = new mt::Circle[m_n];

			srand(time(0));
			for (int i = 0; i < m_n; i++) {
				int r = rand() % 100 + 1;
				int x = rand() % (1100 - 2 * r) + r;
				int y = rand() % (800 - 2 * r) + r;
				int dx = (rand() % 200);
				int dy = (rand() % 200);
				m_c[i].Setup(x, y, r, dx, dy);
			}
		}

		void TouchBorder(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float dx1 = obj.dx();
			float dy1 = obj.dy();
			float r = obj.R();

			if (x + r >= m_width || x - r <= 0) {
				obj.dx(obj.dx());
			}
			if (y + r >= m_height || y - r <= 0) {
				obj.dy(obj.dy());
			}
		}

		void Encounter(Circle& obj, Circle& obj2) {
			float x1 = obj.X();
			float y1 = obj.Y();
			float x2 = obj2.X();
			float y2 = obj2.Y();
			float r1 = obj.R();
			float r2 = obj2.R();
			float dx1 = obj.dx();
			float dy1 = obj.dy();
			float dx2 = obj2.dx();
			float dy2 = obj2.dy();
			float Dx = x1 - x2;
			float Dy = y1 - y2;
			float d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) + 1;
			float s = Dx / d;
			float e = Dy / d;

			if (d < r1 + r2) {
				float Vn1 = dx2 * s + dy2 * e;
				float Vn2 = dx1 * s + dy1 * e;
				float dt = (r2 + r1 - d) / (Vn1 - Vn2);
				if (dt > 0.6) dt = 0.6;
				if (dt < -0.6) dt = -0.6;

				x1 -= dx1 * dt;
				y1 -= dy1 * dt;
				x2 -= dx2 * dt;
				x2 -= dx2 * dt;
				obj.x(x1);
				obj.y(y1);
				obj2.x(x2);
				obj2.y(y2);
				Dx = x1 - x2;
				Dy = y1 - y2;
				float d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) + 1;
				float s = Dx / d;
				float e = Dy / d;
				Vn1 = dx2 * s + dy2 * e;
				Vn2 = dx1 * s + dy1 * e;
				float Vt1 = -dx2 * e + dy2 * s;
				float Vt2 = -dx1 * e + dy1 * s;

				float o = Vn2;
				Vn2 = Vn1;
				Vn1 = o;

				dx1 = Vn2 * s - Vt2 * e;
				dy1 = Vn2 * e + Vt2 * s;
				dx2 = Vn1 * s - Vt1 * e;
				dy2 = Vn1 * e + Vt1 * s;

				x1 += dx1 * dt;
				y1 += dy1 * dt;
				x2 += dx2 * dt;
				x2 += dx2 * dt;
				obj.x(x1);
				obj.y(y1);
				obj2.x(x2);
				obj2.y(y2);

				obj.DX(dx1);
				obj.DY(dy1);
				obj2.DX(dx2);
				obj2.DY(dy2);
			}
		}

		void Life()
		{
			sf::Clock clock;
			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed) {
						m_window.close();
					}
				}

				//Логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				//Перемещение шарика
				for (int i = 0; i < m_n; i++) {
					m_c[i].Move(dt);
				}

				for (int i = 0; i < m_n; i++) {
					TouchBorder(m_c[i]);
					for (int j = 0; j < i; j++) {
						Encounter(m_c[i], m_c[j]);
					}
				}


				//Отображение
				m_window.clear();
				for (int i = 0; i < m_n; i++) {
					m_window.draw(m_c[i].Get());
				}
				m_window.display();
			}
		}

		~Game()
		{
			delete[] m_c;
		}
	};
}