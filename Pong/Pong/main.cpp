#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

// Declaraciones Globales
RenderWindow ventana(VideoMode(1200, 750), "Pong");
RectangleShape paleta1(Vector2f(15, 100));
RectangleShape paleta2(Vector2f(15, 100));
CircleShape pelota(10);

RectangleShape recuadro(Vector2f(ventana.getSize().x - 100, ventana.getSize().y - 140));
vector<RectangleShape> lineaPunteada;

int eleccionMenu;

// Puntuacion de cada jugador
int puntajeJugador1 = 0;
int puntajeJugador2 = 0;

// Velocidad y direccion de la pelota
float velocidadPelota = 0.6f;
Vector2f velocidadPelotaVector(velocidadPelota, -velocidadPelota);

// Sonidos
SoundBuffer bufferPong;
SoundBuffer bufferPunto;
SoundBuffer bufferGanar;
Sound sonidoPong;
Sound sonidoPunto;
Sound sonidoGanar;

bool pausaJuego1 = false;
///

// Metodo Movimiento Paletas
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

// Metodo Resetear Pelota
void resetearPelota()
{
    float posX = recuadro.getPosition().x + recuadro.getSize().x / 2 - pelota.getRadius();
    float posY = recuadro.getPosition().y + recuadro.getSize().y / 2 - pelota.getRadius();

    pelota.setPosition(posX, posY);

    velocidadPelotaVector.x = velocidadPelota;
    velocidadPelotaVector.y = -velocidadPelota;
}


// Método mostrarCreditos
void mostrarCreditos()
{
    // Crear ventana de créditos
    RenderWindow creditosVentana(VideoMode(400, 250), "Créditos", Style::Close);

    // Texto de créditos
    string mensajeCreditos = "Autores:\nALVAREZ JOSE\nANAHY HERRERA\nLOJAN SEBASTIAN\nLUZURIAGA ANDRES";

    Font fuenteCreditos;
    if (!fuenteCreditos.loadFromFile("Pixel-UniCode.ttf"))
    {
        // Manejar el error de carga de fuente
        return;
    }

    Text textoCreditos(mensajeCreditos, fuenteCreditos, 40);
    textoCreditos.setPosition(creditosVentana.getSize().x / 2 - textoCreditos.getGlobalBounds().width / 2,
                              creditosVentana.getSize().y / 2 - textoCreditos.getGlobalBounds().height / 2);
    textoCreditos.setFillColor(Color::White);

    while (creditosVentana.isOpen())
    {
        Event eventoCreditos;
        while (creditosVentana.pollEvent(eventoCreditos))
        {
            if (eventoCreditos.type == Event::Closed)
                creditosVentana.close();
            else if (eventoCreditos.type == Event::MouseButtonPressed)
                creditosVentana.close(); // Cerrar la ventana al hacer clic
        }

        creditosVentana.clear();
        creditosVentana.draw(textoCreditos);
        creditosVentana.display();
    }
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

    // Membrete
    // Titulo Proyecto Juego
    Text titulo("Proyecto Juego Final", fuente, 30);
    titulo.setPosition(ventana.getSize().x / 2 - titulo.getGlobalBounds().width / 2, 50);
    titulo.setFillColor(Color::White);

    // Titulo Grupo 2
    Text titulo1("Grupo #2", fuente, 30);
    titulo1.setPosition(ventana.getSize().x / 2 - titulo1.getGlobalBounds().width / 2, 70);
    titulo1.setFillColor(Color::White);

    // Titulo Pong
    Text titulo2("JUEGO PONG", fuente, 150);
    titulo2.setPosition(ventana.getSize().x / 2 - titulo2.getGlobalBounds().width / 2, 80);
    titulo2.setFillColor(Color::Red);

    // Boton Opcion 1 (1 VS 1)
    Text opcion1("Jugar   1 vs 1", fuente, 50);
    opcion1.setPosition(ventana.getSize().x / 2 - titulo2.getGlobalBounds().width / 2, 350);
    opcion1.setFillColor(Color::White);

    // Boton Salir
    Text opcionSalir("Salir", fuente, 45);
    opcionSalir.setPosition(ventana.getSize().x / 2 - titulo2.getGlobalBounds().width / 2, 400);
    opcionSalir.setFillColor(Color::Red);

    // Boton Creditos
    Text opcionCreditos("Créditos", fuente, 45);
    opcionCreditos.setPosition(ventana.getSize().x / 2 - opcionCreditos.getGlobalBounds().width / 2, 550);
    opcionCreditos.setFillColor(Color::Green);


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

            // Opciones de Juego con mouse
            else if (evento.type == Event::MouseButtonPressed)
            {
                Vector2i posicionMouse = Mouse::getPosition(ventana);

                // Opcion 1 seleccionada
                if (opcion1.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                {
                    puntajeJugador1 = 0;
                    puntajeJugador2 = 0;
                    return 1;
                }

                // Opcion Salir seleccionada
                else if (opcionSalir.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                {
                    ventana.close();
                    return -1;
                }

                // Opcion Creditos seleccionada
                else if (evento.type == Event::MouseButtonPressed)
                {
                    Vector2i posicionMouse = Mouse::getPosition(ventana);

                    if (opcionCreditos.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                    {
                        mostrarCreditos();
                    }
                }
            }
        }

        ventana.clear();

        ventana.draw(titulo);
        ventana.draw(titulo1);
        ventana.draw(titulo2);

        ventana.draw(opcion1);
        ventana.draw(opcionSalir);
        ventana.draw(opcionCreditos);


        ventana.display();
    }
    return eleccionMenu; // Se incluye para evitar advertencias del compilador
}

//Metodo de Pausa
void manejarPausa()
{
    Font fuente;

    if (fuente.loadFromFile("Pixel-UniCode.ttf"))
    {
        Text pausaTexto("PAUSA", fuente, 150);
        pausaTexto.setPosition(ventana.getSize().x / 2 - pausaTexto.getGlobalBounds().width / 2, ventana.getSize().y / 2 - pausaTexto.getGlobalBounds().height / 2 - 300);
        pausaTexto.setFillColor(Color::Yellow);

        Text reanudarTexto("1. Reanudar", fuente, 50);
        reanudarTexto.setPosition(ventana.getSize().x / 2 - reanudarTexto.getGlobalBounds().width / 2, ventana.getSize().y / 2 - 90);
        reanudarTexto.setFillColor(Color::White);

        Text reiniciarTexto("2. Reiniciar", fuente, 50);
        reiniciarTexto.setPosition(ventana.getSize().x / 2 - reiniciarTexto.getGlobalBounds().width / 2, ventana.getSize().y / 2 - 60);
        reiniciarTexto.setFillColor(Color::White);

        Text salirMenuTexto("3. Salir a Menú", fuente, 50);
        salirMenuTexto.setPosition(ventana.getSize().x / 2 - salirMenuTexto.getGlobalBounds().width / 2, ventana.getSize().y / 2 - 30);
        salirMenuTexto.setFillColor(Color::Red);

        while (ventana.isOpen() && (pausaJuego1))
        {
            Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                    ventana.close();

                // Manejar opciones de pausa con el mouse
                else if (evento.type == Event::MouseButtonPressed)
                {
                    Vector2i posicionMouse = Mouse::getPosition(ventana);

                    if (reanudarTexto.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                    {
                        pausaJuego1 = false; // Reanudar juego 1
                        return;
                    }
                    else if (reiniciarTexto.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                    {
                        // Reiniciar juego 1
                        puntajeJugador1 = 0;
                        puntajeJugador2 = 0;
                        resetearPelota();
                        pausaJuego1 = false;
                        return;
                    }
                    else if (salirMenuTexto.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
                    {
                        // Salir a menú desde juego 1
                        pausaJuego1 = false;
                        eleccionMenu = mostrarMenu();
                        return;  // Salir del bucle al salir al menú
                    }
                }
            }

            ventana.clear();
            ventana.draw(pausaTexto);
            ventana.draw(reanudarTexto);
            ventana.draw(reiniciarTexto);
            ventana.draw(salirMenuTexto);
            ventana.display();
        }
    }
}


// Metodo Movimiento Pelota
void moverPelota()
{
    // Movimiento de la pelota y detección de colisiones
    pelota.move(velocidadPelotaVector);

    // Colisiones con las paredes superior e inferior
    if (pelota.getPosition().y <= recuadro.getPosition().y + 1 || pelota.getPosition().y >= recuadro.getPosition().y + recuadro.getSize().y - pelota.getGlobalBounds().height - 1)
    {
        velocidadPelotaVector.y = -velocidadPelotaVector.y;
        sonidoPong.play(); // Reproducir sonido "pong"
    }

    // Colisión con las paletas
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
        // Puntuación y reseteo de la pelota
        if (pelota.getPosition().x <= recuadro.getPosition().x)
        {
            puntajeJugador2++;
            resetearPelota();
            sonidoPunto.play(); // Reproducir sonido "punto"
        }

        if (pelota.getPosition().x >= recuadro.getPosition().x + recuadro.getSize().x - pelota.getGlobalBounds().width)
        {
            puntajeJugador1++;
            resetearPelota();
            sonidoPunto.play(); // Reproducir sonido "punto"
        }
    }

    // Verificar si algún jugador ha llegado a 5 puntos
    if (puntajeJugador1 == 5 || puntajeJugador2 == 5)
    {
        sonidoGanar.play();

        // Mostrar resultado en una ventana emergente
        RenderWindow resultadoVentana(VideoMode(400, 200), "Resultado", Style::Close);

        string mensajeResultado;
        if (puntajeJugador1 == 5)
            mensajeResultado = "¡El jugador 1  ha ganado!";
        else
            mensajeResultado = "¡El jugador 2  ha ganado!";

        Font fuenteResultado;
        if (!fuenteResultado.loadFromFile("Pixel-UniCode.ttf"))
        {
            // Manejar el error de carga de fuente
            return;
        }

        Text textoResultado(mensajeResultado, fuenteResultado, 40);
        textoResultado.setPosition(50, 50);
        textoResultado.setFillColor(Color::White);

        while (resultadoVentana.isOpen())
        {
            Event eventoResultado;
            while (resultadoVentana.pollEvent(eventoResultado))
            {
                if (eventoResultado.type == Event::Closed)
                    resultadoVentana.close();
                else if (eventoResultado.type == Event::MouseButtonPressed)
                    resultadoVentana.close(); // Cerrar la ventana al hacer clic
            }

            resultadoVentana.clear();
            resultadoVentana.draw(textoResultado);
            resultadoVentana.display();
        }

        // Reiniciar el juego
        eleccionMenu = mostrarMenu();
        if (eleccionMenu != -1)
        {
            puntajeJugador1 = 0;
            puntajeJugador2 = 0;
            resetearPelota();
            return;
        }
    }
}

// Metodo Renderiza Ventana Visual
void renderizarVentana()
{
    // Declaracion en Ventana
    ventana.clear();

    // Dibujar recuadro global
    recuadro.setPosition(50, 70);
    recuadro.setOutlineThickness(1);
    recuadro.setOutlineColor(Color::White);
    recuadro.setFillColor(Color::Transparent);
    ventana.draw(recuadro);

    // Dibujar linea punteada
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

    // Mostrar puntaje
    Font fuente;
    if (fuente.loadFromFile("Pixel-UniCode.ttf"))
    {
        // Puntaje Jugador 1
        Text textoPuntaje1(to_string(puntajeJugador1), fuente, 50);
        textoPuntaje1.setPosition(ventana.getSize().x / 4 - 25, 5);
        ventana.draw(textoPuntaje1);

        // Puntaje Jugador
        Text textoPuntaje2(to_string(puntajeJugador2), fuente, 50);
        textoPuntaje2.setPosition(3 * ventana.getSize().x / 4 - 25, 5);
        ventana.draw(textoPuntaje2);
    }

    ventana.display();
}

// Metodo para inicializar Linea Punteada
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

//Metodo de 1 VS 1
void jugarModo1vs1()
{
    paleta1.setPosition(50, ventana.getSize().y / 2 - paleta1.getSize().y / 2);
    paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, ventana.getSize().y / 2 - paleta2.getSize().y / 2);
    resetearPelota();

    while (ventana.isOpen())
    {
        Event evento;

        while (ventana.pollEvent(evento))
        {
            if(evento.type == Event::Closed)
                ventana.close();

            else if (evento.type == Event::KeyPressed && evento.key.code == Keyboard::P)
                pausaJuego1 = !pausaJuego1;

            else if (evento.type == Event::KeyPressed && evento.key.code == Keyboard::Escape)
            {
                eleccionMenu = mostrarMenu();

                if (eleccionMenu != 1)
                {
                    paleta1.setPosition(50, ventana.getSize().y / 2 - paleta1.getSize().y / 2);
                    paleta2.setPosition(ventana.getSize().x - 50 - paleta2.getSize().x, ventana.getSize().y / 2 - paleta2.getSize().y / 2);
                    pausaJuego1 = false;

                    return;
                }
            }
        }

        ventana.clear();

        if (!pausaJuego1)
        {
            moverPaletas();
            moverPelota();
        }

        renderizarVentana();

        if (pausaJuego1)
            manejarPausa();
    }
}

// Metodo Principal (Ejecutar)
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
    if (!bufferGanar.loadFromFile("Win.ogg"))
    {
        cerr << "Error al cargar el archivo de sonido 'Win.ogg'." << endl;
        return -1;
    }

    // Asignar buffers de sonido a sonidos
    sonidoPong.setBuffer(bufferPong);
    sonidoPunto.setBuffer(bufferPunto);
    sonidoGanar.setBuffer(bufferGanar);

    // Inicializar Linea Punteda
    inicializarLineaPunteada(lineaPunteada, ventana);

    eleccionMenu = mostrarMenu();

    if (eleccionMenu == 1)
    {
        jugarModo1vs1();
    }

    return 0;
}

