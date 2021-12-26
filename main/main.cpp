#include <SFML/Graphics.hpp>

using namespace sf;

int gridLogic[12][12];
int gridView[12][12];

void setNumbersOfMines(int arr[12][12]);
void gameOver(Event event);
void openEmptyLeft(int x, int y);
void openEmptyRight(int x, int y);
void openEmptyDown(int x, int y);
void openEmptyUp(int x, int y);

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(1100, 750), "Saper");

    // Ширина клетки поля
    int widthSlot = 50;

    sf::Vector2i offsetField(100, 100);

    // Загрузка текстуры и создание спрайта
    Texture texture;
    texture.loadFromFile("images/sprite.jpg");
    Sprite sprite(texture);

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
        {
            gridView[i][j] = 10;
            if (rand() % 8 == 0)
                gridLogic[i][j] = 9;
            else
                gridLogic[i][j] = 0;
        }

    setNumbersOfMines(gridLogic);

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = (pos.x - offsetField.x) / widthSlot;
        int y = (pos.y - offsetField.y) / widthSlot;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {

                if (event.mouseButton.button == Mouse::Left)
                {
                    if (gridLogic[x][y] == 9)
                    {
                        gridView[x][y] = gridLogic[x][y];
                        gameOver(event);
                    }
                    else if (gridLogic[x][y] == 0)
                    {
                        gridView[x][y] = gridLogic[x][y];
                        openEmptyLeft(x, y);
                        openEmptyRight(x, y);
                        openEmptyDown(x, y);
                        openEmptyUp(x, y);
                    }
                    else
                    {
                        gridView[x][y] = gridLogic[x][y];
                    }
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    if (gridView[x][y] == 10)
                    {
                        gridView[x][y] = 11;
                    }
                    else if (gridView[x][y] == 11)
                        gridView[x][y] = 10;
                    // window.draw(sprite);
                }
            }
        }

        window.clear();

        for (int i = 0; i < 12; i++)
            for (int j = 0; j < 12; j++)
            {
                sprite.setTextureRect(IntRect(gridView[i][j] * widthSlot, 0, widthSlot, widthSlot));
                sprite.setPosition(offsetField.x + i * widthSlot, offsetField.y + j * widthSlot);
                window.draw(sprite);
            }

        window.display();
    }
    return 0;
}

void setNumbersOfMines(int arr[12][12])
{
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
        {
            int n = 0;
            if (arr[i][j] == 9)
                continue;
            if ((arr[i - 1][j] == 9) && (i > 0))
                n++;
            if ((arr[i][j - 1] == 9) && (j > 0))
                n++;
            if ((arr[i + 1][j] == 9) && (i < 11))
                n++;
            if ((arr[i][j + 1] == 9) && (j < 11))
                n++;
            if ((arr[i + 1][j + 1] == 9) && (i < 11) && (j < 11))
                n++;
            if ((arr[i - 1][j - 1] == 9) && (i > 0) && (j > 0))
                n++;
            if ((arr[i - 1][j + 1] == 9) && (i > 0) && (j < 11))
                n++;
            if ((arr[i + 1][j - 1] == 9) && (i < 11) && (j > 0))
                n++;

            arr[i][j] = n;
        }
}

void gameOver(Event event)
{
    RenderWindow endWindow;
    endWindow.create(VideoMode(300, 150), "Game Over!");
    while (endWindow.isOpen())
    {
        while (endWindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
                endWindow.close();
        }
        sf::Font myFont;
        myFont.loadFromFile("fonts/arial.ttf");
        Text text("Game Over!", myFont, 50);
        text.setFillColor(Color::Red);
        endWindow.clear();
        endWindow.draw(text);
        endWindow.display();
    }
}

void openEmptyLeft(int x, int y)
{
    if ((gridLogic[x - 1][y] >= 0) && (gridLogic[x - 1][y] <= 8))
    {
        gridView[x - 1][y] = gridLogic[x - 1][y];
        if ((x - 1 > 0) && (gridLogic[x - 1][y] == 0))
            openEmptyLeft(x - 1, y);
    }
}

void openEmptyRight(int x, int y)
{
    if ((gridLogic[x + 1][y] >= 0) && (gridLogic[x + 1][y] <= 8))
    {
        gridView[x + 1][y] = gridLogic[x + 1][y];
        if ((x + 1 < 11) && (gridLogic[x + 1][y] == 0))
            openEmptyRight(x + 1, y);
    }
}

void openEmptyDown(int x, int y)
{
    if (y < 11)
    {
        if ((gridLogic[x][y + 1] >= 0) && (gridLogic[x][y + 1] <= 8))
        {
            gridView[x][y + 1] = gridLogic[x][y + 1];
            if ((y + 1 < 11) && (gridLogic[x][y + 1] == 0))
                openEmptyDown(x, y + 1);
        }
    }
}

void openEmptyUp(int x, int y)
{
    if (y > 0)
    {
        if ((gridLogic[x][y - 1] >= 0) && (gridLogic[x][y - 1] <= 8))
        {
            gridView[x][y - 1] = gridLogic[x][y - 1];
            if ((y - 1 > 0) && (gridLogic[x][y - 1] == 0))
                openEmptyUp(x, y - 1);
        }
    }
}