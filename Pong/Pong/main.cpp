#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
sf::RectangleShape paddle1(sf::Vector2f(10, 80));
sf::RectangleShape paddle2(sf::Vector2f(10, 80));
sf::CircleShape ball(5);

// Velocidad y dirección de la pelota
float ballSpeed = 0.45f;
sf::Vector2f ballVelocity(ballSpeed, ballSpeed);

// Puntuación de cada jugador
int scorePlayer1 = 0;
int scorePlayer2 = 0;

void resetBall()
{
    ball.setPosition(400, 300);
    ballVelocity.x = ballSpeed;
    ballVelocity.y = ballSpeed;
}

void movePaddles()
{
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

void moveBall()
{
    ball.move(ballVelocity);

    // Colisiones con las paredes
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= 600 - ball.getGlobalBounds().height)
    {
        ballVelocity.y = -ballVelocity.y;
    }

    // Colisiones con las paletas
    if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
    {
        ballVelocity.x = -ballVelocity.x;
    }

    // Puntuación y reseteo de la pelota
    if (ball.getPosition().x <= 0)
    {
        // Jugador 2 anota un punto
        scorePlayer2++;
        resetBall();
    }
    if (ball.getPosition().x >= 800 - ball.getGlobalBounds().width)
    {
        // Jugador 1 anota un punto
        scorePlayer1++;
        resetBall();
    }
}

void draw()
{
    window.clear();
    window.draw(paddle1);
    window.draw(paddle2);
    window.draw(ball);

    // Mostrar puntaje
    sf::Font font;
    if (font.loadFromFile("arial.ttf"))
    {
        sf::Text scoreText("Player 1: " + std::to_string(scorePlayer1) + "   Player 2: " + std::to_string(scorePlayer2), font, 20);
        scoreText.setPosition(250, 20);
        window.draw(scoreText);
    }

    window.display();
}

// Función para manejar el menú de inicio
int showMenu()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) // Cambia el nombre del archivo según la fuente que uses
    {
        // Manejo del error al cargar la fuente
        return -1;
    }

    sf::Text title("Pong Grupo 2 - Estructura de Datos", font, 30);
    title.setPosition(100, 50);

    sf::Text option1("1. Jugar 1 vs 1", font, 20);
    option1.setPosition(150, 200);

    sf::Text option2("2. Jugar 1 vs BOT (No implementado)", font, 20);
    option2.setPosition(150, 250);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return -1; // Se cerró la ventana, terminar la ejecución
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    return 1; // Opción 1 seleccionada
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    return 2; // Opción 2 seleccionada
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (option1.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    return 1; // Opción 1 seleccionada
                }
                else if (option2.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    return 2; // Opción 2 seleccionada
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.display();
    }

    return -1; // Esto no debería ocurrir, pero lo incluyo para evitar advertencias del compilador
}

int main()
{
    int menuChoice = showMenu();

    if (menuChoice == 1)
    {
        // Jugar 1 vs 1
        paddle1.setPosition(50, 300);
        paddle2.setPosition(750, 300);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            movePaddles();
            moveBall();
            draw();
        }
    }
    else if (menuChoice == 2)
    {
        // Jugar 1 vs BOT (Aún no implementado)
        // Puedes implementar la lógica del BOT aquí
    }

    return 0;
}
