#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

//Declaracion Objetos Visuales
RenderWindow ventana(VideoMode(800, 600), "Pong");
RectangleShape paleta1(Vector2f(10, 80));
RectangleShape paleta2(Vector2f(10, 80));
CircleShape pelota(5);

//velocidad y direccion de pelota
float velocidadPelota = 0.60f;
Vector2f velocidadPelotaVector(velocidadPelota, velocidadPelota);

//puntuacion de cada jugador
int puntajeJugador1 = 0;
int puntajeJugador2 = 0;

//Metodo Movimiento Paletas
void moverPaletas()
{
    if (Keyboard::isKeyPressed(Keyboard::W) && paleta1.getPosition().y > 0)
    {
        paleta1.move(0, -1.0);
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && paleta1.getPosition().y < 600 - paleta1.getSize().y)
    {
        paleta1.move(0, 1.0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && paleta2.getPosition().y > 0)
    {
        paleta2.move(0, -1.0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) && paleta2.getPosition().y < 600 - paleta2.getSize().y)
    {
        paleta2.move(0, 1.0);
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
    pelota.move(velocidadPelotaVector);

    // Colisiones con las paredes
    if (pelota.getPosition().y <= 0 || pelota.getPosition().y >= 600 - pelota.getGlobalBounds().height)
    {
        velocidadPelotaVector.y = -velocidadPelotaVector.y;
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


//Metodo Renderiza Ventada Visual
void renderizarVentana()
{
    //Declaracion en Ventana
    ventana.clear();
    ventana.draw(paleta1);
    ventana.draw(paleta2);
    ventana.draw(pelota);

    //Mostrar puntaje
    Font fuente;
    if (fuente.loadFromFile("Pixel-UniCode.ttf"))
    {
        Text textoPuntaje("Jugador 1: " + to_string(puntajeJugador1) + "   Jugador 2: " + to_string(puntajeJugador2), fuente, 20);
        textoPuntaje.setPosition(250, 30);
        ventana.draw(textoPuntaje);
    }

    ventana.display();
}

// Función para manejar el menú de inicio
int mostrarMenu()
{
    Font fuente;
    if (!fuente.loadFromFile("Pixel-UniCode.ttf")) // Cambia el nombre del archivo según la fuente que uses
    {
        // Manejo del error al cargar la fuente
        return -1;
    }

    ///Membrete
    //Titulo Proyecto Juego
    Text titulo("Proyecto Juego Final", fuente, 30);
    titulo.setPosition(ventana.getSize().x / 2 - titulo.getGlobalBounds().width / 2, 20);
    titulo.setFillColor(Color::White);

    //Titulo Grupo 2
    Text titulo1("Grupo #2", fuente, 30);
    titulo1.setPosition(ventana.getSize().x / 2 - titulo1.getGlobalBounds().width / 2, 50);
    titulo1.setFillColor(Color::White);

    //Titulo Pong
    Text titulo2("JUEGO PONG", fuente, 100);
    titulo2.setPosition(ventana.getSize().x / 2 - titulo2.getGlobalBounds().width / 2, 80);
    titulo2.setFillColor(Color::Red);

    //Boton Opcion 1 (1 VS 1)
    Text opcion1("Jugar 1 vs 1", fuente, 30);
    opcion1.setPosition(150, 300);
    opcion1.setFillColor(Color::White);

    //Boton Opcion 2 (1 VS BOT)
    Text opcion2("Jugar 1 vs BOT", fuente, 30);
    opcion2.setPosition(150, 350);
    opcion2.setFillColor(Color::White);

    //Boton Salir
    Text opcionSalir("Salir", fuente, 30);
    opcionSalir.setPosition(150, 400);
    opcionSalir.setFillColor(Color::Red);

    while (ventana.isOpen())
    {
        Event evento;
        while (ventana.pollEvent(evento))
        {
            // Se cerró la ventana, terminar la ejecución
            if (evento.type == Event::Closed)
            {
                ventana.close();
                return -1;
            }

            ///Opciones de Juego con mouse
            else if (evento.type == Event::MouseButtonPressed)
            {
                Vector2i posicionMouse = Mouse::getPosition(ventana);

                //Opcion 1 seleccionada
                if(opcion1.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    return 1;
                }

                //Opcion 2 seleccionada
                else if(opcion2.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    return 2;
                }

                //Opcion Salir seleccionada
                else if(opcionSalir.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    return -1;
                }
            }
        }

        ventana.clear();

        ventana.draw(titulo);
        ventana.draw(titulo1);
        ventana.draw(titulo2);

        ventana.draw(opcion1);
        ventana.draw(opcion2);
        ventana.draw(opcionSalir);

        ventana.display();
    }
    return -1; // Se incluye para evitar advertencias del compilador
}

//Metodo Principal(Ejecutar)
int main()
{
    int eleccionMenu = mostrarMenu();

    //Jugar 1 vs 1
    if (eleccionMenu == 1)
    {
        paleta1.setPosition(50, 300);
        paleta2.setPosition(750, 300);

        while (ventana.isOpen())
        {
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
    }

    //Jugar 1 vs BOT
    else if (eleccionMenu == 2)
    {
        paleta1.setPosition(50, 300);
        paleta2.setPosition(750, 300);

        while (ventana.isOpen())
        {
            Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                    ventana.close();
            }

            // Mover la paleta del jugador
            moverPaletas();

            // Mover la paleta del BOT (lógica simple, sigue la pelota)
            if (pelota.getPosition().y < paleta2.getPosition().y && paleta2.getPosition().y > 0)
            {
                paleta2.move(0, -0.5);
            }
            else if (pelota.getPosition().y > paleta2.getPosition().y && paleta2.getPosition().y < 600 - paleta2.getSize().y)
            {
                paleta2.move(0, 0.5);
            }

            // Mover la pelota y renderizar la ventana
            moverPelota();
            renderizarVentana();
        }
    }

    return 0;
}
