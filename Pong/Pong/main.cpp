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
float velocidadPelota = 0.45f;
Vector2f velocidadPelotaVector(velocidadPelota, velocidadPelota);

//puntuacion de cada jugador
int puntajeJugador1 = 0;
int puntajeJugador2 = 0;

//Metodo Movimiento Paletas
void moverPaletas()
{
    if (Keyboard::isKeyPressed(Keyboard::W) && paleta1.getPosition().y > 0)
    {
        paleta1.move(0, -0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && paleta1.getPosition().y < 600 - paleta1.getSize().y)
    {
        paleta1.move(0, 0.5);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && paleta2.getPosition().y > 0)
    {
        paleta2.move(0, -0.5);
    }

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
    pelota.move(velocidadPelotaVector);

    //Colision con paredes
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
    if (fuente.loadFromFile("Arial.ttf"))
    {
        Text textoPuntaje("Jugador 1: " + to_string(puntajeJugador1) + "   Jugador 2: " + to_string(puntajeJugador2), fuente, 20);
        textoPuntaje.setPosition(250, 30);
        ventana.draw(textoPuntaje);
    }

    ventana.display();
}

//Metodo Manejar Menu de Inicio
int mostrarMenu()
{
    //Se encargara de mostrar MENU, donde cuente con dos opciones de 1 vs 1 y 1 vs BOT

    //Implementar fuente ARIAL, archivo ya puesto en la carpeta del proyecto
}

//Metodo Principal(Ejecutar)
int main()
{
    int eleccionMenu = mostrarMenu();

    if (eleccionMenu == 1)
    {
        //Jugar 1 vs 1
        paleta1.setPosition(50, 300);
        paleta1.setPosition(750, 300);

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
    else if (eleccionMenu == 2)
    {
        //Jugar 1 vs BOT
        //Implementar Logica con IA
    }

    return 0;
}
