#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

//Declaracion Objetos Visuales
RenderWindow(VideoMde(800, 600), "Pong");
RenderWindow ventana(VideoMode(800, 600), "Pong");
RectangleShape paleta1(Vector2f(10, 80));
RectangleShape paleta2(Vector2f(10, 80));
CircleShape pelota(5);

//velocidad y direccion de pelota
float velocidadPelota = o.45f;
float velocidadPelota = 0.45f;
Vector2f velocidadPelotaVector(velocidadPelota, velocidadPelota);

//puntuacion de cada jugador
@ -20,27 +21,35 @@ int puntajeJugador2 = 0;
//Metodo Movimiento Paletas
void moverPaletas()
{
    if (Keyboard::isKeyPressed(Keyboard::W) && paddle1.getPosition().y > 0)
    if (Keyboard::isKeyPressed(Keyboard::W) && paleta1.getPosition().y > 0)
    {
        paleta1.move(0, -0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && paddle1.getPosition().y < 600 - paddle1.getSize().y)
    if (Keyboard::isKeyPressed(Keyboard::S) && paleta1.getPosition().y < 600 - paleta1.getSize().y)
    {
        paleta1.move(0, 0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && paddle2.getPosition().y > 0)
    if (Keyboard::isKeyPressed(Keyboard::Up) && paleta2.getPosition().y > 0)
    {
        paleta2.move(0, -0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) && paddle2.getPosition().y < 600 - paddle2.getSize().y)
    if (Keyboard::isKeyPressed(Keyboard::Down) && paleta2.getPosition().y < 600 - paleta2.getSize().y)
    {
        paleta2.move(0, 0.5);
    }
}

//Metodo Resetear Pelota
void resetearPelota()
{
    pelota.setPosition(400,300);
    velocidadPelotaVector.x = velocidadPelota;
    velocidadPelotaVector.y = velocidadPelota;
}

//Metodo Movimiento Pelota
void moverPelota()
{
@ -53,49 +62,86 @@ void moverPelota()
    }

    //Colision con paletas
    if ((pelota.getGlobalBounds().intersects(paleta1.getGlobalBounds())) ||
    (pelota.getGlobalBounds().intersects(paleta2.getGlobalBounds())))
    {
        velocidadPelotaVector.x = -velocidadPelotaVector.x;
    }

    //Puntuacion y reseteo de pelota
    if (pelota.getPosition().x <= 0)
    {
        //Jugador 2
        puntajeJugador2++;
        resetearPelota();
    }
    if (pelota.getPosition().x >= 800 - pelota.getGlobalBounds().width)
    {
        //Jugador 1
        puntajeJugador1++;
        resetearPelota();
    }
}

//Metodo Resetear Pelota
void resetBall()
//Metodo Renderiza Ventada Visual
void renderizarVentana()
{
    pelota.setPosition(400,300);
    velocidadPelotaVector.x = velocidadPelota;
    velocidadPelotaVector.y = velocidadPelota;
    //Declaracion en Ventana
    ventana.clear();
    ventana.draw(paleta1);
    ventana.draw(paleta2);
    ventana.draw(pelota);

    //Mostrar puntaje
    Font fuente;
    if (fuente.loadFromFile("Arial.ttf"))
    {
        Text textoPuntaje("Jugador 1: " + to_string(puntajeJugador1) + "   Jugador 2: " + to_string(puntajeJugador2), fuente, 20);
        textoPuntaje.setPosition(250, 30);
        ventana.draw(textoPuntaje);
    }

    ventana.display();
}

// Función para manejar el menú de inicio
int mostrarMenu(){
    Font fuente;
     if (!fuente.loadFromFile("arial.ttf")) // Cambia el nombre del archivo según la fuente que uses
    {
        // Manejo del error al cargar la fuente
        return -1;
    }
    Text titulo("Pong Grupo 2 - Estructura de Datos", fuente, 30);
    titulo.setPosition(100, 50);

    Text opcion1("1. Jugar 1 vs 1", fuente, 20);
    opcion1.setPosition(150, 200);

    Text opcion2("2. Jugar 1 vs BOT (No implementado)", fuente, 20);
    opcion2.setPosition(150, 250);

    while (ventana.isOpen())
    {
        Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
            {
                ventana.close();
                return -1; // Se cerró la ventana, terminar la ejecución
            }
            else if (evento.type == Event::KeyPressed)
            {
                if (evento.key.code == Keyboard::Num1)
                {
                    return 1; // Opción 1 seleccionada
                }
                else if (evento.key.code == Keyboard::Num2)
                {
                    return 2; //Opcion 2 seleccionada
                }
            }
            else if (evento.type == Event::MouseButtonPressed)
            {
                Vector2i posicionMouse = Mouse::getPosition(ventana);
                if(opcion1.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    return 1; //Opcion 1 seleccionada
                }
                else if(opcion2.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    return 2; //Opcion 2 seleccionada
                }
            }
        }
        ventana.clear();
        ventana.draw(titulo);
        ventana.draw(opcion1);
        ventana.draw(opcion2);
        ventana.display();
    }
    return -1; // Se incluye para evitar advertencias del compilador
}


int main()
//Metodo Manejar Menu de Inicio
int mostrarMenu()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");
    //Se encargara de mostrar MENU, donde cuente con dos opciones de 1 vs 1 y 1 vs BOT

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    Sprite sprite(texture);
    //Implementar fuente ARIAL, archivo ya puesto en la carpeta del proyecto
}

    // Start the game loop
    while (app.isOpen())
//Metodo Principal(Ejecutar)
int main()
{
    int eleccionMenu = mostrarMenu();

    if (eleccionMenu == 1)
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        //Jugar 1 vs 1
        paleta1.setPosition(50, 300);
        paleta1.setPosition(750, 300);

        while (ventana.isOpen())
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
            Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                    ventana.close();
            }

            moverPaletas();
            moverPelota();
            renderizarVentana();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }
    else if (eleccionMenu == 2)
    {
        //Jugar 1 vs BOT
        //Implementar Logica con IA
    }

    return EXIT_SUCCESS;
    return 0;
}
