#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


sf::RenderWindow(sf::VideoMde(800, 600), "Pong")
sf::RectangleShape padde1(sf::Vector2f(10, 80));
sf::RectangleShape padde2(sf::Vector2f(10, 80));
sf::CircleShape ball(5);

//velocidad y direccion de la pelota
float ballSpeed = o.45f;
sf::Vector2f ballVelocity(ballSpeed, ballSpeed);

//puntuacion de cada jugador
int scorePlayer1 = 0;
int scorePlayer2 = 0;

void resetBall(){
ball.setPosition(400,300);
ballVelocity.x = ballSpeed;
ballVelocity.y = ballSpeed;
}

void movePaddles(){
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPosition().y > 0)
    {
        paddle1.move(0, -0.5);
    }

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPosition().y < 600 - paddle1.getSize().y)
    {
        paddle1.move(0, 0.5);
    }

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPosition().y > 0)
    {
        paddle2.move(0, -0.5);
    }

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPosition().y < 600 - paddle2.getSize().y)
    {
        paddle2.move(0, 0.5);
    }
}



int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
