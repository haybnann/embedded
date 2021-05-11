#pragma once
class Matrix
{
	
private:

protected:


public:	

	int rows;
	int columns;
	float** values;

	//Constructor
	Matrix matrix(int r, int c) {

		this->rows = r;
		this->columns = c;

		values = new float*[r];

		//Create Matrix
		for (int ii = 0; ii < r; ii++) {
			values[ii] = new float[c];

			//Initialize to Zero
			for (int jj = 0; jj < c; jj++) {
				values[ii][jj] = 0;
			}
		}
		return *this;
	}

	//assign a specific element at a specified place
	void setElement(int r, int c, float value) {
		this->values[r-1][c-1] = value;
	}

	//make a diagonal matrix
	void eye() {
		for (int ii = 0; ii < this->rows; ii++) {
			for (int jj = 0; jj <= ii; jj++) {
				if (ii == jj) {
					this->values[ii][jj] = 1;
				}
			}
		}
	}

	//overload addition for matrices
	Matrix& operator + (Matrix& m) {

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


	//overload = Next


};
