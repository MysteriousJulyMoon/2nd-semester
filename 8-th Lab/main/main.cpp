#include <SFML/Graphics.hpp>
#include <Circle.hpp>
#include <Game.hpp>
#include <Bullet.hpp>

int main()
{
    sf::Game game(1920, 1080, "Game");

    if (!game.Setup(4))
        return -1;
    game.LifeCycle();

    return 0;
}