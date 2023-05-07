#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ball Game");

    // Create the ball shape
    sf::CircleShape ball(30.f);
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(100.f, 100.f);

    // Create the obstacles
    sf::RectangleShape obstacle1(sf::Vector2f(200.f, 50.f));
    obstacle1.setFillColor(sf::Color::Green);
    obstacle1.setPosition(300.f, 300.f);

    sf::RectangleShape obstacle2(sf::Vector2f(50.f, 200.f));
    obstacle2.setFillColor(sf::Color::Blue);
    obstacle2.setPosition(500.f, 100.f);

    // Set the ball's velocity
    float vx = 0.f;
    float vy = 0.f;
    float speed = 1.f;
    float gravity = 0.1f;

    // Game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Apply gravity
        vy += gravity;

        // Move the ball
        ball.move(vx * speed, vy * speed);

        // Check for collisions with obstacles
        if (ball.getGlobalBounds().intersects(obstacle1.getGlobalBounds()))
        {
            // Separate the ball from the obstacle in the X direction
            if (ball.getPosition().x < obstacle1.getPosition().x)
            {
                ball.setPosition(obstacle1.getPosition().x - ball.getRadius() * 2, ball.getPosition().y);
            }
            else
            {
                ball.setPosition(obstacle1.getPosition().x + obstacle1.getSize().x + ball.getRadius(), ball.getPosition().y);
            }

            // Stop the ball's X velocity
            vx = 0.f;
        }
        if (ball.getGlobalBounds().intersects(obstacle2.getGlobalBounds()))
        {
            // Separate the ball from the obstacle in the Y direction
            if (ball.getPosition().y < obstacle2.getPosition().y)
            {
                ball.setPosition(ball.getPosition().x, obstacle2.getPosition().y - ball.getRadius() * 2);
            }
            else
            {
                ball.setPosition(ball.getPosition().x, obstacle2.getPosition().y + obstacle2.getSize().y + ball.getRadius());
            }

            // Stop the ball's Y velocity
            vy = 0.f;
        }

        // Handle input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            vx = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            vx = 1.f;
        }
        else
        {
            vx = 0.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ball.getPosition().y + ball.getRadius() * 2 == window.getSize().y)
        {
            vy = -6.f;
        }

        // Clear the screen
        window.clear(sf::Color::White);

        // Draw the obstacles and ball
        window.draw(obstacle1);
        window.draw(obstacle2);
        window.draw(ball);

        // Display the window
        window.display();
    }

    return 0;
}
