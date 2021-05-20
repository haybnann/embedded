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
/*
float determinant(Matrix& matrix) {
	//do stuff
	return 0;
}
*/

//Reduced Row Echelon Form

void Matrix::PartialPivot(Matrix& m) {

	uint8_t largest = 0;
	for (int ii = 0; ii < m.rows; ii++) {
		if (m.values[ii][0] > m.values[largest][0]) {
			largest = ii;
		}
	}
	float* temp = m.values[0];
	m.values[0] = m.values[largest];
	m.values[largest] = temp;

}



//FUCKKKKK wheres my mistake
void Matrix::rref() {

	int ii = 0, jj = 0, kk = 0, cc = 0;

	for (ii = 0; ii < rows; ii++) {
		if ((values[ii][ii] <0.01) && (values[ii][ii] > -0.01 )) {
			cc = 1;
			while (((ii + cc) < rows) && ((values[ii+cc][ii] < 0.01) && (values[ii+cc][ii] > -0.01))) {
				cc++;
			}
			if ((ii + cc) == rows) {
				break;
			}
			//swap
			for (jj = ii, kk = 0; kk < rows; kk++) {

				float temp = values[jj][kk];
				values[jj][kk] = values[jj + cc][kk];
				values[jj + cc][kk] = temp;
			}
				
		}

		for (jj = 0; jj < rows; jj++) {
			if (ii != jj) {
				float pro = values[jj][ii] / values[ii][ii];

				for (kk = 0; kk < columns;kk++) {
					values[jj][kk] = values[jj][kk] - values[ii][kk] * pro;
				}

			}
		}

	}
}




	/*int lead = 0;

	while (lead < this->rows) {
		float d, m;

		for (int r = 0; r < this->rows; r++) { // for each row ...
			//calculate divisor and multiplier 
			d = values[lead][lead];
			m = values[r][lead] / values[lead][lead];
			if ((d > 0.001) || (d < -0.001) && (m > 0.001) || (m < -0.001)) {
				for (int c = 0; c < this->columns; c++) { // for each column ...
					if (r == lead)
						values[r][c] /= d;               // make pivot = 1
					else
						values[r][c] -= values[lead][c] * m;  // make other = 0
				}
			}
			
		}

		lead++;
	}*/


	/**
	int lead = 0;

	for (int rr = 0; rr < this->rows; rr++) {
		if (lead >= this->columns ) {
			return;
		}
		int ii = rr;
		while ((this->values[ii][lead] < 0.01) && (this->values[ii][lead] > -0.01)) {//------------FIX  Float comparison
			ii++;
			if (this->rows == ii) {
				ii = rr;
				lead++;
				if (this->columns == lead) {
					return;
				}
			}
		}

		if (ii != rr) {
			//for (int mm = 0; mm < this->columns; mm++) {
				//float temp = this->values[ii][mm];
				//this->values[ii][mm] = this->values[rr][mm];
				//this->values[rr][mm] = temp;
			//}
			float* temp = this->values[ii];
			this->values[ii] = this->values[rr];
			this->values[rr] = temp;
		}
		//Normalize row  rr lead
		for (int kk = 0; kk < this->columns; kk++) {//divide row rr by M[rr,lead]
			this->values[rr][kk]  /= this->values[rr][lead];
		}

		for (int ii = 0; ii < this->rows; ii++) {
			if (ii != rr) {
				float lv = this->values[ii][lead];
				for (int mm = 0;mm < this->columns; mm++) {
					this->values[ii][mm] += (-lv) * this->values[rr][mm];
				}
			}
		}
		lead++;
	}*/
//}

//Row Echelon Form
//Matrix ref(Matrix m) {
	/*
function ToRowEchelonForm(Matrix M) is
    nr := number of rows in M
    nc := number of columns in M
    
    for 0 ≤ r < nr do
        allZeros := true
        for 0 ≤ c < nc do
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
            for 1 ≤ r < (nr - p) do 
                if M[p + r, p] != 0 then
                    x := -M[p + r, p] / M[p, p]
                    for p ≤ c < nc do
                        M[p + r, c] := M[p , c] * x + M[p + r, c]
                    end for
                end if
            end for
            p := p + 1
    end while
end function
	*/
//}

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
	printf("\n");
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

