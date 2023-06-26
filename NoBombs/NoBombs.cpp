#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<time.h>

using namespace sf;

void check(int m1[11][11], int m2[11][11]) {
    
};

int main()
    {
    int grid[11][11];
    int sgrid[11][11];
    int w = 32;
    RenderWindow window(VideoMode(400, 400), "NoBOMBS!");

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++) {
            sgrid[i][j] = 10;

            if (rand() % 5 == 0) grid[i][j] = 9;
            else grid[i][j] = 0;
        }

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++) {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;

            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;

            grid[i][j] = n;
        }

    while (window.isOpen())
    {
        Vector2i position = Mouse::getPosition(window);
        int x = position.x / w;
        int y = position.y / w;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
             if (event.type == Event::MouseButtonPressed)
            if (event.key.code == Mouse::Left) sgrid[x][y] = grid[x][y];
            else if (event.key.code == Mouse::Right) sgrid[x][y] = 11;

        }

        window.clear(Color::White);
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++) {

                if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
                else if (sgrid[x][y] == 0) check(grid, sgrid);

                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                window.draw(s);
            }
        window.display();
    }

    return 0;
}