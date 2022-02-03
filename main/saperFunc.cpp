#include "saperFunc.h"
#include <vector>
#include <time.h>
#include <cstdlib>

void placeMines(std::vector<std::vector<int>> &arrLogic, std::vector<std::vector<int>> &arrView,
                int minSize, int maxSize, int signEmpty, int signMine, int signUnopen, int difficultyGame)
{
    std::srand(time(0));
    for (int i = minSize; i < maxSize; i++)
        for (int j = minSize; j < maxSize; j++)
        {
            arrView[i][j] = signUnopen;
            if (std::rand() % difficultyGame == 0)
                arrLogic[i][j] = signMine;
            else
                arrLogic[i][j] = signEmpty;
        }
}

void setNumbersOfMines(std::vector<std::vector<int>> &arr, int &counterNums, int minSize, int maxSize, int keyMine)
{

    int minPossibleNumberMines = 1;
    int maxPossibleNumberMines = 8;

    for (int i = minSize; i < maxSize; i++)
        for (int j = minSize; j < maxSize; j++)
        {
            int numberOfMines = 0;

            if (arr[i][j] == keyMine)
                continue;
            if ((i > minSize) && (arr[i - 1][j] == keyMine))
                numberOfMines++;
            if ((j > minSize) && (arr[i][j - 1] == keyMine))
                numberOfMines++;
            if ((i + 1 < maxSize) && (arr[i + 1][j] == keyMine))
                numberOfMines++;
            if ((j + 1 < maxSize) && (arr[i][j + 1] == keyMine))
                numberOfMines++;
            if ((i + 1 < maxSize) && (j + 1 < maxSize) && (arr[i + 1][j + 1] == keyMine))
                numberOfMines++;
            if ((i > minSize) && (j > minSize) && (arr[i - 1][j - 1] == keyMine))
                numberOfMines++;
            if ((i > minSize) && (j + 1 < maxSize) && (arr[i - 1][j + 1] == keyMine))
                numberOfMines++;
            if ((i + 1 < maxSize) && (j > minSize) && (arr[i + 1][j - 1] == keyMine))
                numberOfMines++;

            arr[i][j] = numberOfMines;

            if (numberOfMines >= minPossibleNumberMines && numberOfMines <= maxPossibleNumberMines)
                counterNums++;
        }
}

void openEmpty(std::vector<std::vector<int>> &arrLogic, std::vector<std::vector<int>> &arrView,
               int x, int y, int minSize, int maxSize, int logicEmpty)
{
    if ((arrLogic[x][y] == logicEmpty) && (x < maxSize) && (x >= minSize) && (y < maxSize) && (y >= minSize))
    {
        int newEmptyCell = 12;
        arrLogic[x][y] = newEmptyCell;
        arrView[x][y] = logicEmpty;

        if ((x < maxSize) && (x >= minSize) && (y - 1 < maxSize) && (y - 1 >= minSize) && (arrLogic[x][y - 1] == logicEmpty))
            openEmpty(arrLogic, arrView, x, y - 1, minSize, maxSize, logicEmpty);

        if ((x < maxSize) && (x >= minSize) && (y + 1 < maxSize) && (y + 1 >= minSize) && (arrLogic[x][y + 1] == logicEmpty))
            openEmpty(arrLogic, arrView, x, y + 1, minSize, maxSize, logicEmpty);

        if ((x - 1 < maxSize) && (x - 1 >= minSize) && (y < maxSize) && (y >= minSize) && (arrLogic[x - 1][y] == logicEmpty))
            openEmpty(arrLogic, arrView, x - 1, y, minSize, maxSize, logicEmpty);

        if ((x + 1 < maxSize) && (x + 1 >= minSize) && (y < maxSize) && (y >= minSize) && (arrLogic[x + 1][y] == logicEmpty))
            openEmpty(arrLogic, arrView, x + 1, y, minSize, maxSize, logicEmpty);

        if ((x + 1 < maxSize) && (x + 1 >= minSize) && (y + 1 < maxSize) && (y + 1 >= minSize) && (arrLogic[x + 1][y + 1] == logicEmpty))
            openEmpty(arrLogic, arrView, x + 1, y + 1, minSize, maxSize, logicEmpty);

        if ((x + 1 < maxSize) && (x + 1 >= minSize) && (y - 1 < maxSize) && (y - 1 >= minSize) && (arrLogic[x + 1][y - 1] == logicEmpty))
            openEmpty(arrLogic, arrView, x + 1, y - 1, minSize, maxSize, logicEmpty);

        if ((x - 1 < maxSize) && (x - 1 >= minSize) && (y - 1 < maxSize) && (y - 1 >= minSize) && (arrLogic[x - 1][y - 1] == logicEmpty))
            openEmpty(arrLogic, arrView, x - 1, y - 1, minSize, maxSize, logicEmpty);

        if ((x - 1 < maxSize) && (x - 1 >= minSize) && (y + 1 < maxSize) && (y + 1 >= minSize) && (arrLogic[x - 1][y + 1] == logicEmpty))
            openEmpty(arrLogic, arrView, x - 1, y + 1, minSize, maxSize, logicEmpty);
    }
}

void openNumberAroundEmpty(std::vector<std::vector<int>> &arrLogic, std::vector<std::vector<int>> &arrView,
                           int minSize, int maxSize)
{
    for (int i = minSize; i < maxSize; i++)
        for (int j = minSize; j < maxSize; j++)
        {
            if (arrView[i][j] == 0 || arrView[i][j] == 12)
            {
                if (i + 1 < maxSize)
                    arrView[i + 1][j] = arrLogic[i + 1][j];
                if (j + 1 < maxSize)
                    arrView[i][j + 1] = arrLogic[i][j + 1];
                if (i + 1 < maxSize && j + 1 < maxSize)
                    arrView[i + 1][j + 1] = arrLogic[i + 1][j + 1];
                if (i - 1 >= minSize && j - 1 >= minSize)
                    arrView[i - 1][j - 1] = arrLogic[i - 1][j - 1];
                if (i - 1 >= minSize)
                    arrView[i - 1][j] = arrLogic[i - 1][j];
                if (j - 1 >= minSize)
                    arrView[i][j - 1] = arrLogic[i][j - 1];
                if (i - 1 >= minSize && j + 1 < maxSize)
                    arrView[i - 1][j + 1] = arrLogic[i - 1][j + 1];
                if (i + 1 < maxSize && j - 1 >= minSize)
                    arrView[i + 1][j - 1] = arrLogic[i + 1][j - 1];
            }
        }
}