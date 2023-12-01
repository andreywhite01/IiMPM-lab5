#include "utils.h"


int main() {
	setlocale(LC_ALL, "rus");

	Matrix matrix;
	VECTOR_F lambda;
	VECTOR_F toMaximize;

	// открываем файл
	ifstream fin;
	fin.open("C:/Users/Andrey/source/repos/lab5/data.txt");
	if (!fin.is_open()) {
		cout << "Не удалось открыть файл" << endl;
		return 1;
	}

	string line;
	char type;

	// читаем символ, определяющий тип матрицы l - матрица потерь, w - матрицы выигрышей
	getline(fin, line, '\r');
	type = line[0];

	// чиаем строки таблицы
	while (getline(fin, line, '\r')) {
		matrix.m.push_back(getFloatVecFromLine(line));
	}

	// закрываем файл
	fin.close();

	// выводим матрицу в консоль
	if (type == 'w')
		cout << "Матрица выигрыша\n";
	if (type == 'l')
		cout << "Матрица потерь\n";

	print(matrix);

	int theBestVariante = 0;
	float theBestScore = 0;

	VECTOR_F scores;

	cout << "Критерий Вальда\n";
	scores = {};
	int bestVald = metVald(matrix, scores, type);
	print(scores, bestVald);

	//cout << "Критерий Лапласа\n";
	//scores = {};
	//int bestLaplasse = metLaplasse(matrix, scores, type);
	//print(scores, bestLaplasse);

	cout << "Матрица рисков\n";
	Matrix riskMatrix = getMatrixOfRisks(matrix, type);
	print(riskMatrix);

	cout << "Метод Сэвиджа\n";
	scores = {};
	int bestSavidge = metSavidge(riskMatrix, scores);
	print(scores, bestSavidge);

	cout << "Критерий Гурвица\n";
	for (auto alpha : { 0.1, 0.3, 0.5, 0.7, 0.1 }) {
		cout << "Для показателя Гурвица " << alpha << endl;
		scores = {};
		int bestGurvic = metGurvic(matrix, scores, type, alpha);
		print(scores, bestGurvic);
		cout << endl;
	}
	return 0;
}


