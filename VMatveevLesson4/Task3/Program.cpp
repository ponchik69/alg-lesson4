/*
* Выполнил: Владимир Матвеев
*
* Задача:
* Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу.
*
* Задача решена методом рекурсии с возвратом.

* Решение проверялось на доске 5x5.

* Из википедии: 
* Для неквадратных досок незамкнутый обход конём существует только при выполнении следующих условий: 
  если одна сторона доски равна 3, то другая должна быть либо 4, либо не меньше 7; 
* если же обе стороны больше 3, то обход коня возможен на всех досках, кроме 4 × 4. В частности, незамкнутые маршруты существуют на квадратных досках n × n для всех n>=5.
* 
* В то же время, на любой доске, наличие или отсутствие решения зависит от начального положения фигуры. Например, на доске 5x5 при начальных координатах [3,4],[4,3],[1,4],[4,1] решения не существует.
* 
* Пример координат полей на доске размером 5 на 5.
*
*  | 0 | 1 | 2 | 3 | 4 |
* ----------------------
* 0| + | + | + | + | + |
* ----------------------
* 1| + | + | + | + | + |
* ----------------------
* 2| + | + | + | + | + |
* ----------------------
* 3| + | + | + | + | + |
* ----------------------
* 4| + | + | + | + | + |
* ----------------------
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;


const unsigned int boardSizeX = 5; // Размер доски по оси x
const unsigned int boardSizeY = 5; // Размер доски по оси y
const unsigned int maxMovesOptions = 8; // Максимальное возможное кол-во ходов фигуры (Конь максимально имеет 8 ходов относительно своего положения) 

// Массив изменения координат относительно текущего положения
//|---------| [-1, 2]   |---------| [ 1, 2] |---------|
//
//| [-2, 1] | --------- |---------|---------| [ 2, 1] |
//
//|---------| --------- |----x----|---------|---------|
//
//| [-2,-1] | --------- |---------|---------| [ 2,-1] |
//
//|---------| [-1,-2]   |---------| [1, -2] |---------|
int movesOptions[maxMovesOptions][2] = {
	{1, 2}, {2, 1}, {2, -1}, {1, -2},
    {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
};

int board[boardSizeX][boardSizeY]; // Доска
int infoMass[boardSizeX * boardSizeY]; // Массив с информаций о ходах. Для infoMass[i]: i - номер хода, infoMass[i] - кол-во попыток установки данного хода 
int maxMovesCount = boardSizeX * boardSizeY - 1; // Кол-во клеток, которые нужно обойти

int cheackMove(int x, int y); //Функция проверки возможности встать на клетку с координатами [x,y]
int findMove(int curX, int curY, int moveNumber); //Основная функция перебора вариантов установки фигуры
void printBoard(); // Функция печати доски

int main()
{
	setlocale(LC_ALL, "rus");

	int beginY, beginX;

	cout << "Введите координаты начальной позиции фигуры. Отчет координат начинается с 0:" << endl;
	cout << "X: "; cin >> beginX;
	cout << "Y: "; cin >> beginY;

	if (beginX < 0 || beginX > boardSizeX || beginY < 0 || beginY > boardSizeY)
	{
		cout << endl;
		cout << "Введены некорректные координаты. Будут использованны X=0, Y=0." << endl;
		beginX = 0;
		beginY = 0;
	}

	for (int i = 0; i < boardSizeX; ++i)
	{
		for (int j = 0; j < boardSizeY; ++j)
			board[i][j] = 0;
	}

	if (findMove(beginY, beginX, 1))
	{
		cout << endl;
		cout << "Итоговая доска" << endl;
		printBoard();
	}
	else
	{
		cout << endl;
		cout << "Нет решения" << endl;
	}

	cout << endl;
	int resultIter = 0;

	for (int i = 2; i < boardSizeX*boardSizeY + 1; ++i)
	{
		resultIter = resultIter + infoMass[i];
		cout << "На ход " << i << " потредовалось попыток: " << infoMass[i] << endl;
	}

	cout << "Всего сделано попыток: " << resultIter << endl;
	_getch();
	return 0;
}

int cheackMove(int x, int y)
{
	if (x >= 0 && y >= 0 && x < boardSizeX && y < boardSizeY && board[x][y] == 0)
		return 1;
	else
		return 0;
}

int findMove(int curX, int curY, int moveNumber)
{
	int nextX = 0;
	int nextY = 0;
	board[curX][curY] = moveNumber;
	infoMass[moveNumber]++;

	if (moveNumber > maxMovesCount)
		return 1;

	for (int i = 0; i < maxMovesOptions; i++)
	{
		nextX = curX + movesOptions[i][0];
		nextY = curY + movesOptions[i][1];
		if (cheackMove(nextX, nextY) && findMove(nextX, nextY, moveNumber + 1))
			return 1;
	}

	board[curX][curY] = 0;
	moveNumber++;
	return 0;
}

void printBoard()
{
	for (int i = 0; i < boardSizeX; ++i)
	{
		cout << endl;
		for (int j = 0; j < boardSizeY; ++j)
			cout << board[i][j] << "\t";

		cout << endl;
	}
}