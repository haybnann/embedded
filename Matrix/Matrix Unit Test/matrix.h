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

	//Destructor
	void freeMatrix() {
		for (int ii = 0; ii < this->rows; ii++) {
			free(this->values[ii]);
		}
		free(this->values);
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

	Matrix& operator * (Matrix& m) {

		assert(this->columns == m.rows);


		Matrix newMatrix;
		newMatrix.matrix(this->rows, m.columns);


		for (int ii = 0; ii < this->rows; ii++) {

			for (int jj = 0; jj < m.columns; jj++) {

				float sum = 0;

				for (int kk = 0; kk < m.rows; kk++){
					sum += (this->values[ii][kk] * m.values[kk][jj]);
				}

				newMatrix.values[ii][jj] = sum;

			}
		}
		return newMatrix;
	}


	//overload = Next


	void printMatrix() {
		for (int ii = 0; ii < this->rows; ii++) {
			for (int jj = 0; jj < this->columns; jj++) {
				printf("%f", this->values[ii][jj]);
			}
			printf("\n");
		}
	}


};

