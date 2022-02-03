#ifndef CONSTSAPER_H
#define CONSTSAPER_H

// Определите собственное пространство имен для хранения констант
namespace constSaper
{
const int WIDTH_WINDOW = 1100;
const int HEIGTH_WINDOW = 750;
const int WIDTH_CELL = 50;

const sf::Vector2i OFFSET_FIELD(100, 100);

const int DIFFICULTY_GAME = 5;

const int MAX_SIZE_FIELD = 12;
const int MIN_SIZE_FIELD = 0;

const int EMPTY_CELL = 0;
const int MINE_CELL = 9;
const int UNOPENED_CELL = 10;
const int FLAG_CELL = 11;
}
#endif