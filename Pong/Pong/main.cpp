#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

//Declaracion Objetos Visuales
RenderWindow(VideoMde(800, 600), "Pong");
RectangleShape paleta1(Vector2f(10, 80));
RectangleShape paleta2(Vector2f(10, 80));
CircleShape pelota(5);

//velocidad y direccion de pelota
float velocidadPelota = o.45f;
Vector2f velocidadPelotaVector(velocidadPelota, velocidadPelota);

//puntuacion de cada jugador
int puntajeJugador1 = 0;
int puntajeJugador2 = 0;

//Metodo Movimiento Paletas
void moverPaletas()
{
    if (Keyboard::isKeyPressed(Keyboard::W) && paddle1.getPosition().y > 0)
    {
        paleta1.move(0, -0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && paddle1.getPosition().y < 600 - paddle1.getSize().y)
    {
        paleta1.move(0, 0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && paddle2.getPosition().y > 0)
    {
        paleta2.move(0, -0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) && paddle2.getPosition().y < 600 - paddle2.getSize().y)
    {
        paleta2.move(0, 0.5);
    }
}

//Metodo Movimiento Pelota
void moverPelota()
{
    pelota.move(velocidadPelotaVector);

    //Colision con paredes
    if (pelota.getPosition().y <= 0 || pelota.getPosition().y >= 600 - pelota.getGlobalBounds().height)
    {
        velocidadPelotaVector.y = -velocidadPelotaVector.y;
    }

    //Colision con paletas

}

//Metodo Resetear Pelota
void resetBall()
{
    pelota.setPosition(400,300);
    velocidadPelotaVector.x = velocidadPelota;
    velocidadPelotaVector.y = velocidadPelota;
}

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    Sprite sprite(texture);

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
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
