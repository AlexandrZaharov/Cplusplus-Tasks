/*#include <iostream>
#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow main_window(sf::VideoMode(800, 600), "SFML works!");

    const float ball_radius = 150.0f;
    sf::CircleShape ball(ball_radius);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOrigin(sf::Vector2f(ball_radius, ball_radius));
    ball.setPosition(sf::Vector2f(2 * ball_radius, 2 * ball_radius));

    //sf::RectangleShape rectangle(sf::Vector2f(128.0f, 228.0f));
    //rectangle.setFillColor(sf::Color::Red);
    //rectangle.setPosition(320, 240);

    sf::Texture texture;
    texture.loadFromFile("../data/basketball.png");
    texture.setSmooth(true);
    ball.setTexture(&texture);
    //sf::Sprite ball(texture);
    sf::Vector2f increment(0.5f, 0.5f);

    while (main_window.isOpen())
    {
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                main_window.close();
            }
        }

        if (ball.getPosition().x < ball.getRadius() ||
            ball.getPosition().x + ball.getRadius() > main_window.getSize().x)
        {
            increment.x = -increment.x;
        }

        if (ball.getPosition().y < ball.getRadius() ||
            ball.getPosition().y + ball.getRadius() > main_window.getSize().y)
        {
            increment.y = -increment.y;
        }

        ball.setPosition(ball.getPosition() + increment);

        main_window.clear(sf::Color(16, 16, 16, 255));
        //window.draw(rectangle);
        main_window.draw(ball);
        main_window.display();
    }

    return 0;
}
*/






#include <SFML/Graphics.hpp>

#include "game.h"



int main()
{
    Game game;
    game.Run();

    return 0;
}
