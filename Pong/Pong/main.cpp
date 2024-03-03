#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


sf::RenderWindow(sf::VideoMde(800, 600), "Pong")
sf::RectangleShape padde1(sf::Vector2f(10, 80));
sf::RectangleShape padde2(sf::Vector2f(10, 80));
sf::CircleShape ball(5);


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
