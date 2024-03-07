#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

//Declaraciones Globales
RenderWindow ventana(VideoMode(1200, 750), "Pong");
RectangleShape paleta1(Vector2f(15, 100));
RectangleShape paleta2(Vector2f(15, 100));
CircleShape pelota(10);

RectangleShape recuadro(Vector2f(ventana.getSize().x - 100, ventana.getSize().y - 140));
vector<RectangleShape> lineaPunteada;

int eleccionMenu;

//puntuacion de cada jugador
int puntajeJugador1 = 0;
int puntajeJugador2 = 0;

//velocidad y direccion de pelota
float velocidadPelota = 0.60f;
Vector2f velocidadPelotaVector(velocidadPelota, -velocidadPelota);

//Variable para controlar la pausa
bool pausado = false;

// Sonidos
SoundBuffer bufferPong;
SoundBuffer bufferPunto;
Sound sonidoPong;
Sound sonidoPunto;

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
    velocidadPelotaVector.y = -velocidadPelota;
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
        pausado = false;

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
                    puntajeJugador1 = 0;
                    puntajeJugador2 = 0;
                    return 1;
                }

                //Opcion 2 seleccionada
                else if(opcion2.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    puntajeJugador1 = 0;
                    puntajeJugador2 = 0;
                    return 2;
                }

                //Opcion Salir seleccionada
                else if(opcionSalir.getGlobalBounds().contains(posicionMouse.x,posicionMouse.y))
                {
                    ventana.close();
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
    return eleccionMenu; // Se incluye para evitar advertencias del compilador
}

//Metodo Movimiento Pelota
void moverPelota()
{
    pelota.move(velocidadPelotaVector);

    // Colisiones con las paredes
    if (pelota.getPosition().y <= recuadro.getPosition().y + 1 || pelota.getPosition().y >= recuadro.getPosition().y + recuadro.getSize().y - pelota.getGlobalBounds().height - 1)
    {
        velocidadPelotaVector.y = -velocidadPelotaVector.y;
        sonidoPong.play(); // Reproducir sonido "pong"
    }

    // Colisión con paletas y limitación al recuadro
    if (pelota.getPosition().x >= recuadro.getPosition().x &&
            pelota.getPosition().x <= recuadro.getPosition().x + recuadro.getSize().x - pelota.getGlobalBounds().width)
    {
        if (pelota.getGlobalBounds().intersects(paleta1.getGlobalBounds()) ||
                pelota.getGlobalBounds().intersects(paleta2.getGlobalBounds()))
        {
            velocidadPelotaVector.x = -velocidadPelotaVector.x;
            sonidoPong.play(); // Reproducir sonido "pong"
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
            sonidoPunto.play(); // Reproducir sonido "punto"


            if (puntajeJugador2 >= 5)
            {
                // Reiniciar juego y mostrar menú
                puntajeJugador1 = 0;
                puntajeJugador2 = 0;
                eleccionMenu = mostrarMenu();
                resetearPelota();
            }

        }

        if (pelota.getPosition().x >= recuadro.getPosition().x + recuadro.getSize().x - pelota.getGlobalBounds().width)
        {
            // Jugador 1
            puntajeJugador1++;
            resetearPelota();
            sonidoPunto.play(); // Reproducir sonido "punto"


            if (puntajeJugador1 >= 5)
            {
                // Reiniciar juego y mostrar menú
                puntajeJugador1 = 0;
                puntajeJugador2 = 0;
                eleccionMenu = mostrarMenu();
                resetearPelota();
            }

        }
    }
}



//Metodo Entrada Pausa
void entradaPausa()
{
    Event evento;
    while(ventana.pollEvent(evento))
    {
        if(evento.type == Event::Closed)
            ventana.close();

        //Pulsar P para pausar
        if(evento.type == Event::KeyPressed && evento.key.code == Keyboard::P)
        {
            pausado = !pausado;
        }
    }
}

//Metodo Pausar Juego
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
    salirText.setPosition(ventana.getSize().x / 2 -50, 250);
    reiniciarText.setPosition(ventana.getSize().x / 2 -50, 300);

    //Mostrar los botones en la ventana
    ventana.draw(reanudarText);
    ventana.draw(salirText);
    ventana.draw(reiniciarText);

    //Detectar clics en los botones
    Vector2i mousePos = Mouse::getPosition(ventana);
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        //reanudar
        if(reanudarText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            pausado = false;
        }
        //salir
        else if (salirText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            //ventana.close();
            pausado = false;
            eleccionMenu = mostrarMenu();

        }
        //reiniciar
        else if(reiniciarText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            //logica de reinicio
            puntajeJugador1 = 0;
            puntajeJugador2 = 0;
            resetearPelota();
        }
    }

}

//Metodo Renderiza Ventada Visual
void renderizarVentana()
{
    //Declaracion en Ventana
    ventana.clear();

    //Dibujar recuadro global
    recuadro.setPosition(50, 70);
    recuadro.setOutlineThickness(1);
    recuadro.setOutlineColor(Color::White);
    recuadro.setFillColor(Color::Transparent);
    ventana.draw(recuadro);

    //Dibujar linea punteada
    for (auto& rect : lineaPunteada)
    {
        ventana.draw(rect);
    }

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
    if(pausado)
    {
        pausarJuego();
    }

    ventana.display();
}

//Metodo para inicalizar Linea Punteada
void inicializarLineaPunteada(vector<RectangleShape>& lineaPunteada, const RenderWindow& ventana)
{
    for (int i = 0; i <= (ventana.getSize().y - 140) / 20; i++)
    {
        RectangleShape rect(Vector2f(2, 10));
        rect.setPosition(ventana.getSize().x / 2, 70 + i * 20);
        rect.setFillColor(Color::White);
        lineaPunteada.push_back(rect);
    }
}

int pantallaGanador(int jugadorGanador)
{
    Font fuente;
    if (!fuente.loadFromFile("Pixel-UniCode.ttf"))
    {
        // Manejo del error al cargar la fuente
        return -1;
    }

    Text ganadorText("GANO JUGADOR " + to_string(jugadorGanador), fuente, 40);
    ganadorText.setPosition(ventana.getSize().x / 2 - ganadorText.getGlobalBounds().width / 2, 200);
    ganadorText.setFillColor(Color::White);

    Text menuText("MENU", fuente, 30);
    menuText.setPosition(ventana.getSize().x / 2 - 50, 300);
    menuText.setFillColor(Color::White);

    Text salirText("SALIR", fuente, 30);
    salirText.setPosition(ventana.getSize().x / 2 - 50, 350);
    salirText.setFillColor(Color::Red);

    while (ventana.isOpen())
    {
        Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
            {
                ventana.close();
                return -1;
            }

            // Opciones de menú con mouse
            else if (evento.type == Event::MouseButtonPressed)
            {
                Vector2i posicionMouse = Mouse::getPosition(ventana);

                // Regresar al menú
                if (menuText.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                {
                    // Restablecer variables
                    puntajeJugador1 = 0;
                    puntajeJugador2 = 0;
                    eleccionMenu = mostrarMenu();
                    resetearPelota();
                    return eleccionMenu;
                }

                // Salir del juego
                else if (salirText.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                {
                    ventana.close();
                    return -1;
                }
            }
        }

        ventana.clear();
        ventana.draw(ganadorText);
        ventana.draw(menuText);
        ventana.draw(salirText);
        ventana.display();
    }

    // Reset game state before returning
    puntajeJugador1 = 0;
    puntajeJugador2 = 0;
    resetearPelota();

    return -1; // Se incluye para evitar advertencias del compilador
}


//Metodo Principal(Ejecutar)
int main()
{
    Music musicaFondo;
    // Cargar la música de fondo
    if (!musicaFondo.openFromFile("Musica_Fondo.ogg"))
    {
        cerr << "Error al cargar el archivo de música." << endl;
        return -1;
    }

    musicaFondo.setVolume(5);
    musicaFondo.setLoop(true); // Reproducir en bucle
    musicaFondo.play();

    // Cargar sonidos
    if (!bufferPong.loadFromFile("SonidoPelota.ogg"))
    {
        cerr << "Error al cargar el archivo de sonido 'SonidoPelota.ogg'." << endl;
        return -1;
    }
    if (!bufferPunto.loadFromFile("SonidoPunto.ogg"))
    {
        cerr << "Error al cargar el archivo de sonido 'SonidoPunto.ogg'." << endl;
        return -1;
    }

    // Asignar buffers de sonido a sonidos
    sonidoPong.setBuffer(bufferPong);
    sonidoPunto.setBuffer(bufferPunto);

    //Inicializar Linea Punteda
    inicializarLineaPunteada(lineaPunteada, ventana);

    eleccionMenu = mostrarMenu();

    //Jugar 1 vs 1
    if (eleccionMenu == 1)
    {
        paleta1.setPosition(50, ventana.getSize().y / 2 - paleta1.getSize().y / 2);
        paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, ventana.getSize().y / 2 - paleta2.getSize().y / 2);
        resetearPelota();

        while (ventana.isOpen())
        {
            Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                    ventana.close();

                //P para pausar
                if (evento.type == Event::KeyPressed && evento.key.code == Keyboard::P)
                {
                    pausado = !pausado;
                }
            }

            ventana.clear();


            if (!pausado)
            {
                moverPaletas();
                moverPelota();
            }


            renderizarVentana();


            if (puntajeJugador1 >= 5 || puntajeJugador2 >= 5)
            {
                eleccionMenu = pantallaGanador((puntajeJugador1 >= 5) ? 1 : 2);

                if (eleccionMenu != -1)
                {
                    puntajeJugador1 = 0;
                    puntajeJugador2 = 0;
                    resetearPelota();
                }
            }
        }
    }

    //Jugar 1 vs BOT
    else if (eleccionMenu == 2)
    {
        paleta1.setPosition(50, ventana.getSize().y / 2 - paleta1.getSize().y / 2);
        paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, ventana.getSize().y / 2 - paleta2.getSize().y / 2);
        resetearPelota();

        while (ventana.isOpen())
        {
            Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                    ventana.close();

                //P para pausar
                if (evento.type == Event::KeyPressed && evento.key.code == Keyboard::P)
                {
                    pausado = !pausado;
                }
            }

            ventana.clear();
            if (!pausado)
            {
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
            }

            renderizarVentana();


            if (puntajeJugador1 >= 5 || puntajeJugador2 >= 5)
            {
                eleccionMenu = pantallaGanador((puntajeJugador1 >= 5) ? 1 : 2);

                if (eleccionMenu != -1)
                {
                    puntajeJugador1 = 0;
                    puntajeJugador2 = 0;
                    resetearPelota();
                }
            }

        }
    }

    return 0;
}
