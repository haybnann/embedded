#include "pch.h"
#include "matrix.h"

#include "matrix.h"

//Constructor

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


//Destructor
Matrix::~Matrix() {

	for (int ii = 0; ii < this->rows; ii++) {
		delete[] values[ii];
	}

	delete[] values;  //memory leak ???
}

float determinant(Matrix& matrix) {

}


//Reduced Row Echelon Form
//https://en.wikipedia.org/wiki/Row_echelon_form
Matrix rref(Matrix m) {
	
	int lead = 0;

	for (int rr = 0; rr < m.rows; rr++) {
		if (m.columns < lead) {
			break;//-----------------------FIX
		}
		int ii = rr;
		while (m.values[rr][lead] == 0) {
			ii = ii + 1;
			if (m.rows == ii) {
				ii = rr;
				lead = lead + 1;
				if (m.columns == lead) {
					break;
				}
			}
		}
		if (ii != rr) {
			//swap rows ii and rr
		}
		//divide row rr by M[rr,lead]
		//for 0<= i< rows{
		//	if (ii != rr){
		//		subtract M[i,lead] multiplied by row rr from row ii
		//	}
		//}
		lead = lead + 1;
	}
}

//Row Echelon Form
Matrix ref(Matrix m) {
	/*
function ToRowEchelonForm(Matrix M) is
    nr := number of rows in M
    nc := number of columns in M
    
    for 0 ? r < nr do
        allZeros := true
        for 0 ? c < nc do
            if M[r, c] != 0 then
                allZeros := false
                exit for
            end if
        end for
        if allZeros = true then
            In M, swap row r with row nr
            nr := nr - 1
        end if
    end for
    
    p := 0
    while p < nr and p < nc do
        label nextPivot:
            r := 1
            while M[p, p] = 0 do 
                if (p + r) <= nr then
                    p := p + 1
                    goto nextPivot
                end if
                In M, swap row p with row (p + r)
                r := r + 1
            end while
            for 1 ? r < (nr - p) do 
                if M[p + r, p] != 0 then
                    x := -M[p + r, p] / M[p, p]
                    for p ? c < nc do
                        M[p + r, c] := M[p , c] * x + M[p + r, c]
                    end for
                end if
            end for
            p := p + 1
    end while
end function
	*/
}

void Matrix::setElement(int r, int c, float value) {
	this->values[r - 1][c - 1] = value;
}


void Matrix::eye() {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj <= ii; jj++) {
			if (ii == jj) {
				this->values[ii][jj] = 1;
			}
		}
	}
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


//*** Overloaded Functions***/
Matrix& Matrix::operator+= (const Matrix& m) {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->columns; jj++) {
			this->values[ii][jj] += m.values[ii][jj];
		}
	}

	return *this;
}


const Matrix operator + (const Matrix& first_operand, const Matrix& second_operand) {

	Matrix result(first_operand);//error
	result += second_operand;
	return result;
}


Matrix& Matrix::operator-= (const Matrix& m) {
	for (int ii = 0; ii < this->rows; ii++) {
		for (int jj = 0; jj < this->columns; jj++) {
			this->values[ii][jj] -= m.values[ii][jj];
		}
	}

	return *this;
}


const Matrix operator - (const Matrix& first_operand, const Matrix& second_operand) {

	Matrix result(first_operand);//error
	result -= second_operand;
	return result;
}


Matrix& Matrix::operator*= (const Matrix& m) {
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


Matrix& Matrix::operator=(const Matrix& matrix) {

	if (this != &matrix) {
		
		this->~Matrix();
		new (this) Matrix(matrix.rows,matrix.columns);

		for (int ii = 0; ii < matrix.rows; ii++) {
			for (int jj = 0; jj < matrix.columns; jj++) {
				this->values[ii][jj] = matrix.values[ii][jj];
			}
		}

	}

	return *this;
}

