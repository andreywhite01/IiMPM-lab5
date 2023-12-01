#include "utils.h"

int metVald(const Matrix& matrix, VECTOR_F& scores, char type) {
	vector<float>::iterator it;
	int t;
	switch (type)
	{
	case 'l':
		scores = matrix.max(1);
		return min_element(scores.begin(), scores.end()) - scores.begin();
		break;
	case 'w':
		scores = matrix.min(1);
		return max_element(scores.begin(), scores.end()) - scores.begin();
		break;
	default:
		break;
	}
}

int metSavidge(const Matrix& matrix, VECTOR_F& scores) {
	scores = matrix.max(1);
	return min_element(scores.begin(), scores.end()) - scores.begin();
}

int metLaplasse(const Matrix& matrix, VECTOR_F& scores, char type) {
	switch (type)
	{
	case 'l':
		scores = matrix.mean(1);
		return min_element(scores.begin(), scores.end()) - scores.begin();
		break;
	case 'w':
		scores = matrix.min(1);
		return max_element(scores.begin(), scores.end()) - scores.begin();
		break;
	default:
		break;
	}
}

int metGurvic(const Matrix& matrix, VECTOR_F& scores, char type, float a) {
	VECTOR_F minValues = matrix.min(1);
	VECTOR_F maxValues = matrix.max(1);

	switch (type)
	{
	case 'l':
		for (unsigned short i = 0; i < matrix.m.size(); ++i) {
			scores.push_back(a * minValues[i] + (1 - a) * maxValues[i]);
		}
		return min_element(scores.begin(), scores.end()) - scores.begin();
		break;
	case 'w':
		for (unsigned short i = 0; i < matrix.m.size(); ++i) {
			scores.push_back(a * maxValues[i] + (1 - a) * minValues[i]);
		}
		return max_element(scores.begin(), scores.end()) - scores.begin();
		break;
	default:
		break;
	}
}

VECTOR_F getFloatVecFromLine(string line) {
	VECTOR_F vec;
	stringstream ss;
	ss << line;
	float value;
	while (ss >> value) {
		vec.push_back(value);
	}
	return vec;
}

void print(const Matrix& matrix) {
	for (unsigned short i = 0; i < matrix.m.size(); ++i) {
		for (unsigned short j = 0; j < matrix.m.begin()->size(); ++j) {
			cout << fixed << setprecision(2) << matrix.m[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void print(const VECTOR_F& scores, int bestVar) {
	int index = 1;
	for (float value : scores) {
		cout << "Вариант " << index << ": " << fixed << setprecision(2) << value << endl;
		index++;
	}
	cout << "Лучший вариант под номером " << bestVar + 1 << endl << endl;
}

Matrix getMatrixOfRisks(const Matrix& matrix, char type) {

	Matrix newMatrix;
	newMatrix.m = matrix.m;

	VECTOR_F minValues = matrix.min(0);
	VECTOR_F maxValues = matrix.max(0);

	switch (type)
	{
	case 'l':
		for (unsigned short col = 0; col < matrix.m.begin()->size(); ++col) {
			for (unsigned short row = 0; row < matrix.m.size(); ++row) {
				newMatrix.m[row][col] = matrix.m[row][col] - minValues[col];
			}
		}
		return newMatrix;
		break;
	case 'w':
		for (unsigned short col = 0; col < matrix.m.begin()->size(); ++col) {
			for (unsigned short row = 0; row < matrix.m.size(); ++row) {
				newMatrix.m[row][col] = maxValues[col] - matrix.m[row][col];
			}
		}
		return newMatrix;
		break;
	default:
		break;
	}

}

VECTOR_F Matrix::max(unsigned short axis) const {
	VECTOR_F maxValues;

	switch (axis)
	{
	case 0:
		for (unsigned short col = 0; col < m.begin()->size(); ++col) {
			maxValues.push_back({ m[0][col] });
			for (unsigned short row = 1; row < m.size(); ++row) {
				if (*prev(maxValues.end()) < m[row][col]) {
					*prev(maxValues.end()) = m[row][col];
				}
			}
		}
		break;
	case 1:
		for (unsigned short row = 0; row < m.size(); ++row) {
			maxValues.push_back({ m[row][0] });
			for (unsigned short col = 1; col < m.begin()->size(); ++col) {
				if (*prev(maxValues.end()) < m[row][col]) {
					*prev(maxValues.end()) = m[row][col];
				}
			}
		}
		break;
	default:
		break;
	}
	return maxValues;
}
VECTOR_F Matrix::min(unsigned short axis) const {
	VECTOR_F minValues;

	switch (axis)
	{
	case 0:
		for (unsigned short col = 0; col < m.begin()->size(); ++col) {
			minValues.push_back({ m[0][col] });
			for (unsigned short row = 1; row < m.size(); ++row) {
				if (*prev(minValues.end()) > m[row][col]) {
					*prev(minValues.end()) = m[row][col];
				}
			}
		}
		break;
	case 1:
		for (unsigned short row = 0; row < m.size(); ++row) {
			minValues.push_back({ m[row][0] });
			for (unsigned short col = 1; col < m.begin()->size(); ++col) {
				if (*prev(minValues.end()) > m[row][col]) {
					*prev(minValues.end()) = m[row][col];
				}
			}
		}
		break;
	default:
		break;
	}
	return minValues;
}
VECTOR_F Matrix::mean(unsigned short axis) const {
	VECTOR_F meanValues;

	switch (axis)
	{
	case 0:
		for (unsigned short col = 0; col < m.begin()->size(); ++col) {
			meanValues.push_back({ m[0][col] });
			for (unsigned short row = 1; row < m.size(); ++row) {
				meanValues[col] += m[row][col];
			}
			meanValues[col] /= m.size();
		}
		break;
	case 1:
		for (unsigned short row = 0; row < m.size(); ++row) {
			meanValues.push_back({ m[row][0] });
			for (unsigned short col = 1; col < m.begin()->size(); ++col) {
				meanValues[row] += m[row][col];
			}
			meanValues[row] /= m.begin()->size();
		}
		break;
	default:
		break;
	}
	return meanValues;
}
