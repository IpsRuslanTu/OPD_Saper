#pragma once
#include <vector>

void placeMines(std::vector<std::vector<int>> &arrLogic, std::vector<std::vector<int>> &arrView,
                int minSize, int maxSize, int signEmpty, int signMine, int signUnopen, int difficultyGame);

// Вычисление цифры, которая показывает сколько мин по соседству с данной клеткой
void setNumbersOfMines(std::vector<std::vector<int>> &arr, int &counterNums,
                       int minSize, int maxSize, int keyMine);

void openEmpty(std::vector<std::vector<int>> &arrGrid, std::vector<std::vector<int>> &arrView,
               int x, int y, int minSize, int maxSize, int logicEmpty);

void openNumberAroundEmpty(std::vector<std::vector<int>> &arrLogic, std::vector<std::vector<int>> &arrView,
                           int minSize, int maxSize);