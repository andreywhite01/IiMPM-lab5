#include "utils.h"


int main() {
	setlocale(LC_ALL, "rus");

	Matrix matrix;
	VECTOR_F lambda;
	VECTOR_F toMaximize;

	// ��������� ����
	ifstream fin;
	fin.open("C:/Users/Andrey/source/repos/lab5/data.txt");
	if (!fin.is_open()) {
		cout << "�� ������� ������� ����" << endl;
		return 1;
	}

	string line;
	char type;

	// ������ ������, ������������ ��� ������� l - ������� ������, w - ������� ���������
	getline(fin, line, '\r');
	type = line[0];

	// ����� ������ �������
	while (getline(fin, line, '\r')) {
		matrix.m.push_back(getFloatVecFromLine(line));
	}

	// ��������� ����
	fin.close();

	// ������� ������� � �������
	if (type == 'w')
		cout << "������� ��������\n";
	if (type == 'l')
		cout << "������� ������\n";

	print(matrix);

	int theBestVariante = 0;
	float theBestScore = 0;

	VECTOR_F scores;

	cout << "�������� ������\n";
	scores = {};
	int bestVald = metVald(matrix, scores, type);
	print(scores, bestVald);

	//cout << "�������� �������\n";
	//scores = {};
	//int bestLaplasse = metLaplasse(matrix, scores, type);
	//print(scores, bestLaplasse);

	cout << "������� ������\n";
	Matrix riskMatrix = getMatrixOfRisks(matrix, type);
	print(riskMatrix);

	cout << "����� �������\n";
	scores = {};
	int bestSavidge = metSavidge(riskMatrix, scores);
	print(scores, bestSavidge);

	cout << "�������� �������\n";
	for (auto alpha : { 0.1, 0.3, 0.5, 0.7, 0.1 }) {
		cout << "��� ���������� ������� " << alpha << endl;
		scores = {};
		int bestGurvic = metGurvic(matrix, scores, type, alpha);
		print(scores, bestGurvic);
		cout << endl;
	}
	return 0;
}


