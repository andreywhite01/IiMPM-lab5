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

// ��������� �������
struct Matrix {
	// ������������ �������� �� ������/�������
	VECTOR_F max(unsigned short axis = 0) const;
	// ����������� �������� �� ������/�������
	VECTOR_F min(unsigned short axis = 0) const;
	// ������� �������� �� ������/�������
	VECTOR_F mean(unsigned short axis = 0) const;
	MATRIX_F m;
};
// ������� ��� ����������� ������ ������ �� ������
VECTOR_F getFloatVecFromLine(string line);

// ����� ������� ������ �� ������� ���������
Matrix getMatrixOfRisks(const Matrix& matrix, char type);

// ����� ������
int metVald(const Matrix& matrix, VECTOR_F& scores, char type);
// ����� �������
int metSavidge(const Matrix& matrix, VECTOR_F& scores);
// ����� �������� (�� ������������ � ������ ������)
int metLaplasse(const Matrix& matrix, VECTOR_F& scores, char type);
// ����� �������
int metGurvic(const Matrix& matrix, VECTOR_F& scores, char type, float alpha = 0.5);

// ����� ���������� � �������
void print(const Matrix& matrix);
void print(const VECTOR_F& scores, int bestVar);