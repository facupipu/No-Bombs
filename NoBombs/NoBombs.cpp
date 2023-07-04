//includes necesarios para el funcionamiento del programa
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>

//no se que hace pero aparentemente es importante para no tener que escribir sf :: en algunas funciones
using namespace sf;

//declara las variables utilizadas en multiples funciones
const int size = 12;
int unreveled = ((size - 2) * (size - 2));
int grid[size][size];
int sgrid[size][size];

//Es la funcion encargada de mostrar los lugares
void cleaning(int x, int y) {
    //muestra la casilla
    sgrid[x][y] = grid[x][y];
    unreveled -= 1;
    //si la casilla vale 0 muestra las de al rededor y chequea si tambien son 0 para llamar nuevamente a la funcion
    if (grid[x][y] == 0) {
        if (grid[x + 1][y] == 0 && sgrid[x + 1][y] == 10) cleaning(x + 1, y);
        if (grid[x][y + 1] == 0 && sgrid[x][y + 1] == 10) cleaning(x, y + 1);
        if (grid[x - 1][y] == 0 && sgrid[x - 1][y] == 10) cleaning(x - 1, y);
        if (grid[x][y - 1] == 0 && sgrid[x][y - 1] == 10) cleaning(x, y - 1);
        if (grid[x + 1][y + 1] == 0 && sgrid[x + 1][y + 1] == 10) cleaning(x + 1, y + 1);
        if (grid[x - 1][y - 1] == 0 && sgrid[x - 1][y - 1] == 10) cleaning(x - 1, y - 1);
        if (grid[x - 1][y + 1] == 0 && sgrid[x - 1][y + 1] == 10) cleaning(x - 1, y + 1);
        if (grid[x + 1][y - 1] == 0 && sgrid[x + 1][y - 1] == 10) cleaning(x + 1, y - 1);
        if (sgrid[x + 1][y] == 10) {
            sgrid[x + 1][y] = grid[x + 1][y];
            unreveled -= 1;
        }
        if (sgrid[x - 1][y] == 10) {
            sgrid[x - 1][y] = grid[x - 1][y];
            unreveled -= 1;
        }
        if (sgrid[x][y + 1] == 10) {
            sgrid[x][y + 1] = grid[x][y + 1];
            unreveled -= 1;
        }
        if (sgrid[x][y - 1] == 10) {
            sgrid[x][y - 1] = grid[x][y - 1];
            unreveled -= 1;
        }
        if (sgrid[x + 1][y + 1] == 10) {
            sgrid[x + 1][y + 1] = grid[x + 1][y + 1];
            unreveled -= 1;
        }
        if (sgrid[x + 1][y - 1] == 10) {
            sgrid[x + 1][y - 1] = grid[x + 1][y - 1];
            unreveled -= 1;
        }
        if (sgrid[x - 1][y + 1] == 10) {
            sgrid[x - 1][y + 1] = grid[x - 1][y + 1];
            unreveled -= 1;
        }
        if (sgrid[x - 1][y - 1] == 10) {
            sgrid[x - 1][y - 1] = grid[x - 1][y - 1];
            unreveled -= 1;
        }
    }
}

//pasa todos los ocultos a banderas
void setflags() {
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            if (sgrid[i][j] == 10) sgrid[i][j] = 11;
        }
    }
}

void game_lost() {
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            sgrid[i][j] = grid[i][j];
        }
    }
}

int main()
{   
    //se declara la seed de los random y las variables principales del programa
    srand(time(NULL));
    int bomb_count;
    int flags;
    int w = 32;
    int x = 0;
    int y = 0;
    bool finish = false;
    bool counter = false;
    //se elige la cantidad de minas
    printf("Bienvenido a NoBombs, el mapa es de 10x10\n");
    printf("Elegi la cantidad de bombas:");
    scanf_s("%d", &bomb_count);
    fflush(stdin);
    printf("\n");

    //chequea que el valor ingresado sea correcto, si no es correcto entra en un loop
    while (bomb_count < 1 || bomb_count >= unreveled) {
        //se sale del loop cuando se ingresa un dato correcto
        printf("LA CANTIDAD DE MINAS ES INVALIDAD\n");
        printf("Elegi la cantidad de bombas:");
        scanf_s("%d", &bomb_count);
        fflush(stdin);
        printf("\n");
    }
    flags = bomb_count;
    system("cls");

    //se declara la ventana, la textura y el sprite
    RenderWindow window(VideoMode(((size - 2) * w) + 80, ((size - 2) * w) + 180), "NoBOMBS!", Style::Titlebar | Style::Close);
    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    //crear las fuentes
    Font ds_digital;
    ds_digital.loadFromFile("E:\\Facu\\5to\\Juego\\No-Bombs\\ds_digital\\DS-DIGI.TTF");

    //crea los textos
    Text finish_text;
    finish_text.setFont(ds_digital);
    finish_text.setFillColor(Color::Red);
    finish_text.setCharacterSize(50);
    finish_text.setPosition(100, 60);

    Text bomb_text;
    bomb_text.setFont(ds_digital);
    bomb_text.setFillColor(Color::Red);
    bomb_text.setCharacterSize(40);
    bomb_text.setPosition(325, 5);
    std::string flags_str = std::to_string(flags);
    bomb_text.setString(flags_str);

    Text timer_text;
    timer_text.setFont(ds_digital);
    timer_text.setFillColor(Color::Red);
    timer_text.setCharacterSize(40);
    timer_text.setPosition(25, 5);
    int original_timer = 201;
    int timer = original_timer - 1;
    std::string timer_str = std::to_string(timer);
    timer_text.setString(timer_str);

    //vaciando la grilla de minas y tapando la grilla mostrada
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            grid[i][j] = 0;
            sgrid[i][j] = 10;
        }
    }

    //llenando el mapa de bombas
    int bombs = 0;
    while (bombs < bomb_count) {
        //se selecciona una casilla random
        int x = rand() % (size-2) + 1;
        int y = rand() % (size-2) + 1;
        //si la casilla ya no era una bomba se agrega una bomba
        if (grid[x][y] != 9) {
            grid[x][y] = 9;
            bombs++;
        }
    }

    //todo este for es para contar cuantas minas tienen al rededor cada espacio
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            int n = 0;
            //si el espacio en si es una mina entonces la saltea
            if (grid[i][j] == 9) continue;

            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;

            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            //se le da el valor correspondiente a la cant. de minas cercanas
            grid[i][j] = n;
        }
    }

    Clock clock;

    //Se hace asi, no pregunten
    while (window.isOpen())
    {
        //tomo la posicion del mouse en la app y la divido por la medida de los cuadrados
        Vector2i position = Mouse::getPosition(window);
        int position_x = position.x / w;
        int position_y = (position.y - 100) / w;
        

        //creo los eventos
        Event event;
        while (window.pollEvent(event))
        {
            //para poder cerrar la ventana
            if (event.type == Event::Closed)
                window.close();
            //si toco un boton del mouse copio la posicion del mouse en otra variable
            if (event.type == Event::MouseButtonPressed) {
                x = position_x;
                y = position_y;

                //asegurandose que x e y tengan valores correrctos
                if (x < 1 || x > 10 || y < 1 || y > 10) {
                    x = 0;
                    y = 0;
                }

                //si toco el boton derecho chequeo, si no esta revelado y no tiene bandera revelo y resto 1 a los no revelados
                if (event.key.code == Mouse::Left) {
                    if (!counter && !finish) {
                        counter = true;
                        clock.restart();
                    }
                    if (sgrid[x][y] == 10 && !finish) {
                        //muestra la ubicacion cliqueada
                        cleaning(x, y);

                        //si la cantidad sin revelar es igual a la cantidad de bombas llama a finish con true
                        if (unreveled == bomb_count) {
                            finish = true;
                            finish_text.setString("GANASTE!");

                            //pone las banderas restantes y ajusta su contador
                            setflags();
                            flags = 0;
                            std::string flags_str = std::to_string(flags);
                            bomb_text.setString(flags_str);
                        }
                        //si el lugar revelado tiene una bomba llama a finish con false y muestra todos los lugares
                        if (sgrid[x][y] == 9 && !finish) {
                            finish = true;
                            finish_text.setString("PERDISTE!");
                            game_lost();
                        }
                    }

                }
                //si es click izquierdo pone la bandera o la saca, en caso de que ya esté
                else if (event.key.code == Mouse::Right) {
                    if (!finish) {
                        if (sgrid[x][y] == 10) {
                            flags -= 1;
                            sgrid[x][y] = 11;
                        }
                        else if (sgrid[x][y] == 11) {
                            sgrid[x][y] = 10;
                            flags += 1;
                        }
                        //cambia el numero mostrado en pantalla
                        std::string flags_str = std::to_string(flags);
                        bomb_text.setString(flags_str);
                    }

                }
            }

        }

        //contador iniciado
        if (counter) {
            Time elapsed = clock.getElapsedTime();
            timer = original_timer - elapsed.asSeconds();
            std::string timer_str = std::to_string(timer);
            timer_text.setString(timer_str);
            if (timer <= 0 || finish) {
                counter = false;
                finish = true;
                if (unreveled != bomb_count) {
                    std::string timer_str = std::to_string(timer);
                    timer_text.setString(timer_str);
                    game_lost();
                }
            }
        }

        //blanquea la pantalla
        window.clear(Color::White);
        //En loop se dibujan todos los sprites cons sus respectivos valores
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                //se pasan de parametros del spray la ubicacion en x e y, el ancho y el alto en la textura
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                //se pasan de parametros del spray la ubicacion en x e y en la ventana
                s.setPosition(i * w, j * w + 100);
                window.draw(s);
            }
        }
        window.draw(timer_text);
        window.draw(bomb_text);
        //dibuja el texto de finalización
        if (finish) {
            window.draw(finish_text);
        }
        //se dibuja la pantalla
        window.display();
    }

    return 0;
}