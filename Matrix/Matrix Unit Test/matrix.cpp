#include "pch.h"
#include "matrix.h"

#include "matrix.h"

//Constructor
Matrix Matrix::matrix(int r, int c) {

	this->rows = r;
	this->columns = c;

	values = new float* [r];

	//Create Matrix
	for (int ii = 0; ii < r; ii++) {

		values[ii] = new float[c];

		for (int jj = 0; jj < c; jj++) {//Initialize to Zero
			values[ii][jj] = 0;
		}
	}

	return *this;
}

//Destructor
void Matrix::freeMatrix() {

	for (int ii = 0; ii < this->rows; ii++) {
		free(this->values[ii]);
	}

	free(this->values);
}

//assign a specific element at a specified place
void Matrix::setElement(int r, int c, float value) {
	this->values[r - 1][c - 1] = value;
}

//make a diagonal matrix  -- Rename maindiangonal ???
void Matrix::eye() {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj <= ii; jj++) {
			if (ii == jj) {
				this->values[ii][jj] = 1;
			}
		}
	}
}



//*** Overloaded Functions***/
Matrix Matrix::operator + (Matrix m) {

	//Change assertions to return an error
	assert(this->columns == m.columns);
	assert(this->rows == m.rows);

	Matrix newMatrix;
	newMatrix.matrix(this->rows, this->columns);

	for (int ii = 0; ii < newMatrix.rows; ii++) {
		for (int jj = 0; jj < newMatrix.columns; jj++) {
			newMatrix.values[ii][jj] = this->values[ii][jj] + m.values[ii][jj];
		}
	}

	return newMatrix;
}


Matrix Matrix::operator - (Matrix m) {

	//Change assertions to return an error
	assert(this->columns == m.columns);
	assert(this->rows == m.rows);

	Matrix newMatrix;
	newMatrix.matrix(this->rows, this->columns);

	for (int ii = 0; ii < newMatrix.rows; ii++) {
		for (int jj = 0; jj < newMatrix.columns; jj++) {
			newMatrix.values[ii][jj] = this->values[ii][jj] - m.values[ii][jj];
		}
	}

	return newMatrix;
}


Matrix Matrix::operator * (Matrix m) {

	assert(this->columns == m.rows);


	Matrix newMatrix;
	newMatrix.matrix(this->rows, m.columns);


	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < m.columns; jj++) {

			float sum = 0;

			for (int kk = 0; kk < m.rows; kk++) {
				sum += (this->values[ii][kk] * m.values[kk][jj]);
			}

			newMatrix.values[ii][jj] = sum;
		}
	}
	return newMatrix;
}


Matrix Matrix::operator * (float scalar) {

	Matrix newMatrix;
	newMatrix.matrix(this->rows, this->columns);


	for (int ii = 0; ii < this->rows; ii++) {

		for (int jj = 0; jj < this->columns; jj++) {

			newMatrix.values[ii][jj] = scalar * this->values[ii][jj];
		}
	}
	return newMatrix;
}


Matrix operator * (const float scalar, const Matrix m) {

	Matrix newMatrix;
	newMatrix.matrix(m.rows, m.columns);


	for (int ii = 0; ii < m.rows; ii++) {

		for (int jj = 0; jj < m.columns; jj++) {

			newMatrix.values[ii][jj] = scalar * m.values[ii][jj];
		}
	}
	return newMatrix;
}



void Matrix::printMatrix() {
	for (int ii = 0; ii < this->rows; ii++) {
		printf("[");
		for (int jj = 0; jj < this->columns; jj++) {
			printf(" %.1f ", this->values[ii][jj]);
		}
		printf("]\n");
	}
}
