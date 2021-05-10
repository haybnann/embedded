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




};

