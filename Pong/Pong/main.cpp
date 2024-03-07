#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
/*#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>*/

using namespace sf;
using namespace std;

//Declaracion Objetos Visuales
RenderWindow ventana(VideoMode(1200, 750), "Pong");
RectangleShape paleta1(Vector2f(15, 100));
RectangleShape paleta2(Vector2f(15, 100));
CircleShape pelota(10);

RectangleShape recuadro(Vector2f(ventana.getSize().x - 100, ventana.getSize().y - 140));


//velocidad y direccion de pelota
float velocidadPelota = 0.60f;
Vector2f velocidadPelotaVector(velocidadPelota, velocidadPelota);

//puntuacion de cada jugador
int puntajeJugador1 = 0;
int puntajeJugador2 = 0;

/*// Declaración de la música de fondo
Music musicaFondo;*/

//Variable para controlar la pausa
bool pausado = false;

//Metodo Movimiento Paletas
void moverPaletas()
{
    if (Keyboard::isKeyPressed(Keyboard::W) && paleta1.getPosition().y > recuadro.getPosition().y + 1)
    {
        paleta1.move(0, -1.0);
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && paleta1.getPosition().y + paleta1.getSize().y < recuadro.getPosition().y + recuadro.getSize().y - 1)
    {
        paleta1.move(0, 1.0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && paleta2.getPosition().y > recuadro.getPosition().y + 1)
    {
        paleta2.move(0, -1.0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) && paleta2.getPosition().y + paleta2.getSize().y < recuadro.getPosition().y + recuadro.getSize().y - 1)
    {
        paleta2.move(0, 1.0);
    }
}


//Metodo Resetear Pelota
void resetearPelota()
{
    float posX = recuadro.getPosition().x + recuadro.getSize().x / 2 - pelota.getRadius();
    float posY = recuadro.getPosition().y + recuadro.getSize().y / 2 - pelota.getRadius();

    pelota.setPosition(posX, posY);
    velocidadPelotaVector.x = velocidadPelota;
    velocidadPelotaVector.y = velocidadPelota;
}

//Metodo Movimiento Pelota
void moverPelota()
{
    pelota.move(velocidadPelotaVector);

    // Colisiones con las paredes
    if (pelota.getPosition().y <= recuadro.getPosition().y + 1 || pelota.getPosition().y >= recuadro.getPosition().y + recuadro.getSize().y - pelota.getGlobalBounds().height - 1)
    {
        velocidadPelotaVector.y = -velocidadPelotaVector.y;
    }

    // Colisión con paletas y limitación al recuadro
    if (pelota.getPosition().x >= recuadro.getPosition().x &&
            pelota.getPosition().x <= recuadro.getPosition().x + recuadro.getSize().x - pelota.getGlobalBounds().width)
    {
        if (pelota.getGlobalBounds().intersects(paleta1.getGlobalBounds()) ||
                pelota.getGlobalBounds().intersects(paleta2.getGlobalBounds()))
        {
            velocidadPelotaVector.x = -velocidadPelotaVector.x;
        }
    }
    else
    {
        // Puntuacion y reseteo de pelota
        if (pelota.getPosition().x <= recuadro.getPosition().x)
        {
            // Jugador 2
            puntajeJugador2++;
            resetearPelota();
        }

        if (pelota.getPosition().x >= recuadro.getPosition().x + recuadro.getSize().x - pelota.getGlobalBounds().width)
        {
            // Jugador 1
            puntajeJugador1++;
            resetearPelota();
        }
    }
}

void pausarJuego()
{
    //Crear texto para los botones
    Font fuente;
    if(fuente.loadFromFile("Pixel-UniCode.ttf"))
    {
        Text reanudarText("Reanudar", fuente, 30);
        Text salirText("Salir", fuente, 30);
        Text reiniciarText("Reiniciar", fuente, 30);
    }
    Text reanudarText("Reanudar", fuente, 30);
    Text salirText("Salir", fuente, 30);
    Text reiniciarText("Reiniciar", fuente, 30);

    //Posicion de los botones en la ventana
    reanudarText.setPosition(ventana.getSize().x / 2 -50, 200);
    salirText.setPosition(ventana.getSize().x / 2 -50, 200);
    reiniciarText.setPosition(ventana.getSize().x / 2 -50, 200);

}


//Metodo Renderiza Ventada Visual
void renderizarVentana()
{
    //Declaracion en Ventana
    ventana.clear();

    //Dibujar recuadro global
    //RectangleShape recuadro(Vector2f(ventana.getSize().x - 100, ventana.getSize().y - 140));
    recuadro.setPosition(50, 70);
    recuadro.setOutlineThickness(1);
    recuadro.setOutlineColor(Color::White);
    recuadro.setFillColor(Color::Transparent);
    ventana.draw(recuadro);

    // Ajustar posición de paletas dentro del recuadro
    paleta1.setPosition(50, max(70.0f, min(ventana.getSize().y - 170.0f, paleta1.getPosition().y)));
    paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, max(70.0f, min(ventana.getSize().y - 170.0f, paleta2.getPosition().y)));

    // Ajustar posición de pelota dentro del recuadro
    pelota.setPosition(max(50.0f, min(ventana.getSize().x - 50.0f, pelota.getPosition().x)),
                       max(70.0f, min(ventana.getSize().y - 70.0f, pelota.getPosition().y)));


    ventana.draw(paleta1);
    ventana.draw(paleta2);
    ventana.draw(pelota);

    //Mostrar puntaje
    Font fuente;
    if (fuente.loadFromFile("Pixel-UniCode.ttf"))
    {
        //Puntaje Jugador 1
        Text textoPuntaje1(to_string(puntajeJugador1), fuente, 50);
        textoPuntaje1.setPosition(ventana.getSize().x / 4 - 25, 5);
        ventana.draw(textoPuntaje1);

        //Puntaje Jugador
        Text textoPuntaje2(to_string(puntajeJugador2), fuente, 50);
        textoPuntaje2.setPosition(3 * ventana.getSize().x / 4 - 25, 5);
        ventana.draw(textoPuntaje2);
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

    /*// Cargar música de fondo
    if (!musicaFondo.openFromFile("Musica_Fondo.ogg"))
    {
        // Manejo del error al cargar la música
        return -1;
    }

    musicaFondo.setLoop(true); // Reproducir en bucle*/

    //Membrete
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
        paleta1.setPosition(50, ventana.getSize().y / 2 - paleta1.getSize().y / 2);
        paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, ventana.getSize().y / 2 - paleta2.getSize().y / 2);

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
        paleta1.setPosition(50, ventana.getSize().y / 2 - paleta1.getSize().y / 2);
        paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, ventana.getSize().y / 2 - paleta2.getSize().y / 2);

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
            else if (pelota.getPosition().y > paleta2.getPosition().y && paleta2.getPosition().y < ventana.getSize().y - paleta2.getSize().y)
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
