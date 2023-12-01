#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#define MATRIX_F vector<vector<float>>
#define VECTOR_F vector<float>

using namespace std;

// Структура матрицы
struct Matrix {
	// Максимальное значение по строке/столбцу
	VECTOR_F max(unsigned short axis = 0) const;
	// Минимальное значение по строке/столбцу
	VECTOR_F min(unsigned short axis = 0) const;
	// Среднее значение по строке/столбцу
	VECTOR_F mean(unsigned short axis = 0) const;
	MATRIX_F m;
};
// Функция для корректного чтения данных из потока
VECTOR_F getFloatVecFromLine(string line);

// Поиск матрицы рисков из матрицы выигрышей
Matrix getMatrixOfRisks(const Matrix& matrix, char type);

// Метод Вальда
int metVald(const Matrix& matrix, VECTOR_F& scores, char type);
// Метод Сэвиджа
int metSavidge(const Matrix& matrix, VECTOR_F& scores);
// Метод Лапласса (Не используется в данной задаче)
int metLaplasse(const Matrix& matrix, VECTOR_F& scores, char type);
// Метод Гурвица
int metGurvic(const Matrix& matrix, VECTOR_F& scores, char type, float alpha = 0.5);

// Вывод резульатов в консоль
void print(const Matrix& matrix);
void print(const VECTOR_F& scores, int bestVar);