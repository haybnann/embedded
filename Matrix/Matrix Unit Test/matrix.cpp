#include "pch.h"
#include "matrix.h"

//Constructor & Destructor
Matrix::Matrix() {
	this->rows = 0;
	this->columns = 0;

	this->values = new float* [rows];
}
Matrix::Matrix(const Matrix& matrix) {

	this->rows = matrix.rows;
	this->columns = matrix.columns;

	this->values = new float* [rows];

	for (int ii = 0; ii < rows; ii++) {

		values[ii] = new float[columns];

		for (int jj = 0; jj < columns; jj++) {
			values[ii][jj] = matrix.values[ii][jj];
		}
	}
}
Matrix::Matrix(int r, int c) {

	this->rows = r;
	this->columns = c;

	this->values = new float* [r];

	//Create Matrix
	for (int ii = 0; ii < r; ii++) {

		values[ii] = new float[c];

		for (int jj = 0; jj < c; jj++) {//Initialize to Zero
			values[ii][jj] = 0;
		}
	}

}
Matrix::~Matrix() {

	for (int ii = 0; ii < this->rows; ii++) {
		delete[] values[ii];
	}

	delete[] values;  //memory leak ???
}

//*** Overloaded Functions***/
Matrix& Matrix::operator =  (const Matrix& m) {

	if (this != &m) {
		
		this->~Matrix();
		new (this) Matrix(m.rows,m.columns);

		for (int ii = 0; ii < m.rows; ii++) {
			for (int jj = 0; jj < m.columns; jj++) {
				this->values[ii][jj] = m.values[ii][jj];
			}
		}

	}

	return *this;
}
Matrix& Matrix::operator += (const Matrix& m) {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->columns; jj++) {
			this->values[ii][jj] += m.values[ii][jj];
		}
	}

	return *this;
}
Matrix& Matrix::operator -= (const Matrix& m) {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->columns; jj++) {
			this->values[ii][jj] -= m.values[ii][jj];
		}
	}

	return *this;
}
Matrix& Matrix::operator *= (const Matrix& m) {
	assert(this->columns == m.rows);

	Matrix temporary = Matrix(this->rows,m.columns);

	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < m.columns; jj++) {

			float sum = 0;

			for (int kk = 0; kk < m.rows; kk++) {
				sum += (this->values[ii][kk] * m.values[kk][jj]);
			}

			temporary.values[ii][jj] = sum;
		}
	}

	*this = Matrix(temporary);
	return *this;
}

const Matrix operator + (const Matrix& first_operand, const Matrix& second_operand) {

	Matrix result(first_operand);//error
	result += second_operand;
	return result;
}
const Matrix operator - (const Matrix& first_operand, const Matrix& second_operand) {

	Matrix result(first_operand);//error
	result -= second_operand;
	return result;
}
const Matrix operator * (const Matrix& first_operand, const Matrix& second_operand) {

	Matrix result(first_operand);//error
	result *= second_operand;
	return result;
}

Matrix& Matrix::operator * (float scalar) {

	Matrix* newMatrix = new Matrix(this->rows, this->columns);


	for (int ii = 0; ii < this->rows; ii++) {

		for (int jj = 0; jj < this->columns; jj++) {

			newMatrix->values[ii][jj] = scalar * this->values[ii][jj];
		}
	}
	return *newMatrix;
}
Matrix operator * (const float scalar, const Matrix& m) {

	Matrix* newMatrix = new Matrix(m.rows, m.columns);


	for (int ii = 0; ii < m.rows; ii++) {
		for (int jj = 0; jj < m.columns; jj++) {

			newMatrix->values[ii][jj] = scalar * m.values[ii][jj];
		}
	}
	return *newMatrix;
}


void Matrix::Transpose() {
	Matrix temp = *this;
	//this->~Matrix();
	*this = Matrix(temp.columns, temp.rows);

	for (int ii = 0; ii < rows; ii++) {
		for (int jj = 0; jj < columns; jj++) {
			values[ii][jj] = temp.values[jj][ii];
		}
	}
}

//This is very inefficient -- needs improvement
void Matrix::Inverse() {
	assert(rows == columns);
	Matrix newMatrix = Matrix(rows, columns * 2);
	int dims = rows;

	float temp;


	//append I matrix 
	for (int ii = 0; ii < dims;ii++) {
		for (int jj = 0; jj < (2* dims); jj++) {
			if (jj == (ii + dims)) {
				newMatrix.values[ii][jj] = 1;
			}
			if ((ii < dims) && (jj < dims)) {
				newMatrix.values[ii][jj] = values[ii][jj];
			}
		}
	}

	//swap rows
	for (int ii = dims - 1;ii > 0;ii--) {
		if (newMatrix.values[ii - 1][0] < newMatrix.values[ii][0]) {
			float* temp = newMatrix.values[ii];
			newMatrix.values[ii] = newMatrix.values[ii - 1];
			newMatrix.values[ii - 1] = temp;
		}
	}

	
	//elimination
	for (int ii = 0; ii < dims; ii++) {
		for (int jj = 0; jj < dims; jj++) {
			if (jj != ii) {
				temp = newMatrix.values[jj][ii] / newMatrix.values[ii][ii];
				for (int kk = 0; kk < 2*dims; kk++) {
					newMatrix.values[jj][kk] -= newMatrix.values[ii][kk] * temp;
				}
			}
		}
	}


	for (int ii = 0; ii < dims; ii++) {
		temp = newMatrix.values[ii][ii];
		for (int jj = 0; jj < 2*dims; jj++) {
			newMatrix.values[ii][jj] = newMatrix.values[ii][jj] / temp;
		}
	}

	//Copy into old matrix
	for (int ii = 0; ii < dims; ii++) {
		for (int jj = 0; jj < dims; jj++) {
			values[ii][jj] = newMatrix.values[ii][jj + dims];
		}
	}
}

void Matrix::Identity() {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj <= ii; jj++) {
			if (ii == jj) {
				this->values[ii][jj] = 1;
			}
		}
	}
}

//change this to use better formatting
void Matrix::printMatrix() {
	for (int ii = 0; ii < this->rows; ii++) {
		printf("[");
		for (int jj = 0; jj < this->columns; jj++) {
			printf(" %.2f ", this->values[ii][jj]);
		}
		printf("]\n");
	}
	printf("\n");
}
