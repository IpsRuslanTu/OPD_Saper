#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "constSaper.h"
#include "saperFunc.h"

using namespace sf;
using namespace std;
using namespace constSaper;

void gameOver(Event event);

bool startGame()
{
    // Объявление вектора на n строк по m элементов
    vector<vector<int>> gridView(MAX_SIZE_FIELD, vector<int>(MAX_SIZE_FIELD));
    vector<vector<int>> gridLogic(MAX_SIZE_FIELD, vector<int>(MAX_SIZE_FIELD));

    RenderWindow window(VideoMode(WIDTH_WINDOW, HEIGTH_WINDOW), "Saper", Style::Titlebar);

    bool isLife = true; // Игрок жив
    bool isWin = false; // Победа

    int counterNumbers = 0;
    int guessedNumbers = 0;

    // Создание времени
    Clock clock;
    Clock gameTimeClock;
    int gameTime = 0;

    // Создание шрифта
    Font font;
    font.loadFromFile("fonts/arial.ttf");
    Text textGameEnd("", font, 100);
    textGameEnd.setStyle(Text::Bold);
    textGameEnd.setPosition(150, 330);

    Text textTime("Game time", font, 30);
    textTime.setFillColor(Color::White);
    textTime.setStyle(Text::Bold);

    Text info("Esc - exit\n\nTab - new game", font, 25);
    info.setFillColor(Color::White);
    info.setStyle(Text::Bold);
    info.setPosition(800, 330);

    // Загрузка текстуры и создание спрайта
    Texture texture;
    texture.loadFromFile("images/sprite.jpg");
    Sprite sprite(texture);

    placeMines(gridLogic, gridView, MIN_SIZE_FIELD, MAX_SIZE_FIELD, EMPTY_CELL, MINE_CELL, UNOPENED_CELL, DIFFICULTY_GAME);
    setNumbersOfMines(gridLogic, counterNumbers, MIN_SIZE_FIELD, MAX_SIZE_FIELD, MINE_CELL);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Tab)) //если таб, то перезагружаем игру
            return true;
        if (Keyboard::isKeyPressed(Keyboard::Escape)) //если эскейп, то выходим из игры
            return false;

        Vector2i pos = Mouse::getPosition(window);
        int x = (pos.x - OFFSET_FIELD.x) / WIDTH_CELL;
        int y = (pos.y - OFFSET_FIELD.y) / WIDTH_CELL;

        if (isLife && !isWin)
            gameTime = gameTimeClock.getElapsedTime().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (isLife && !isWin)
            {
                if ((event.type == Event::MouseButtonPressed) && (x >= MIN_SIZE_FIELD) &&
                    (x < MAX_SIZE_FIELD) && (y >= MIN_SIZE_FIELD) && (y < MAX_SIZE_FIELD))
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        if (gridLogic[x][y] == MINE_CELL)
                        {
                            gridView[x][y] = gridLogic[x][y];
                            isLife = false;
                        }
                        else if (gridLogic[x][y] == EMPTY_CELL)
                        {
                            {
                                gridView[x][y] = gridLogic[x][y];
                                openEmpty(gridLogic, gridView, x, y, MIN_SIZE_FIELD, MAX_SIZE_FIELD, EMPTY_CELL);
                                openNumberAroundEmpty(gridLogic, gridView, MIN_SIZE_FIELD, MAX_SIZE_FIELD);
                            }
                        }
                        else
                        {
                            gridView[x][y] = gridLogic[x][y];
                            guessedNumbers = 0;
                            for (int i = MIN_SIZE_FIELD; i < MAX_SIZE_FIELD; i++)
                                for (int j = MIN_SIZE_FIELD; j < MAX_SIZE_FIELD; j++)
                                {
                                    if (gridView[i][j] >= 1 && gridView[i][j] <= 8)
                                        guessedNumbers++;
                                }
                            if (guessedNumbers == counterNumbers)
                                isWin = true;
                        }
                    }
                    else if (event.mouseButton.button == Mouse::Right)
                    {
                        if (gridView[x][y] == UNOPENED_CELL)
                        {
                            gridView[x][y] = FLAG_CELL;
                        }
                        else if (gridView[x][y] == FLAG_CELL)
                            gridView[x][y] = UNOPENED_CELL;
                    }
                }
            }
        }

        window.clear(Color(60, 60, 60));

        for (int i = MIN_SIZE_FIELD; i < MAX_SIZE_FIELD; i++)
            for (int j = MIN_SIZE_FIELD; j < MAX_SIZE_FIELD; j++)
            {
                sprite.setTextureRect(IntRect(gridView[i][j] * WIDTH_CELL, 0, WIDTH_CELL, WIDTH_CELL));
                sprite.setPosition(OFFSET_FIELD.x + i * WIDTH_CELL, OFFSET_FIELD.y + j * WIDTH_CELL);
                window.draw(sprite);
            }

        if (!isLife)
        {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(600, 200));
            rectangle.setFillColor(sf::Color(0, 0, 0, 150));
            rectangle.setPosition(100, 300);

            textGameEnd.setFillColor(Color::Red);
            textGameEnd.setString("Game Over!");
            window.draw(rectangle);
            window.draw(textGameEnd);
        }

        if (isWin)
        {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(600, 200));
            rectangle.setFillColor(sf::Color(0, 0, 0, 150));
            rectangle.setPosition(100, 300);

            textGameEnd.setFillColor(Color::Green);
            textGameEnd.setString("You winner!");
            window.draw(rectangle);
            window.draw(textGameEnd);
        }

        std::ostringstream gameTimeString;
        gameTimeString << gameTime;
        textTime.setString("Game time: " + gameTimeString.str());
        textTime.setPosition(800, 100);
        window.draw(textTime);

        window.draw(info);

        window.display();
    }
}

void gameRunning()
{
    if (startGame())
    {
        gameRunning();
    }
}

int main()
{
    gameRunning();
    return 0;
}