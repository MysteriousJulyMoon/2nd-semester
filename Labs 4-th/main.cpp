#include <SFML/Graphics.hpp>
#include <Circle.hpp>
#include <Triangle.hpp>
#include <Rectangle.hpp>
#include <Line.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works");
    srand(time(0));
    const int n = 5;

    mt::Circle c[n];
    for (int i = 0; i < n; i++)
    {
        int x = rand() % 1000;
        int y = rand() % 600;
        int r = rand() % 100 + 1;
        c[i].Setup(x, y, r);
    }


    mt::Triangle t[n];
    for (int i = 0; i < n; i++)
    {
        int x = rand() % 1000;
        int y = rand() % 600;
        int r = rand() % 100 + 1;
        t[i].Setup(x, y, r);
    }

    mt::Rectangle r[n];
    for (int i = 0; i < n; i++)
    {
        int x = rand() % 1000;
        int y = rand() % 600;
        int a = rand() % 100 + 1;
        int b = rand() % 200 + 1;
        r[i].Setup(x, y, a, b);
    }

    mt::Line l[n];
    for (int i = 0; i < n; i++)
    {
        int x = rand() % 1000;
        int y = rand() % 600;
        int a = rand() % 800 + 1;
        int b = rand() % 10 + 1;
        l[i].Setup(x, y, a, b);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < n; i++)
        {
            window.draw(c[i].Get());
            window.draw(t[i].Get());
            window.draw(r[i].Get());
            window.draw(l[i].Get());
        }
        window.display();
    }
    return 0;
}











/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
   sf::CircleShape shape(100.f);
   shape.setFillColor(sf::Color::Green);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}*/