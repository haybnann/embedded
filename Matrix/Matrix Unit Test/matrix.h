#pragma once
class Matrix
{
	
private:

protected:


public:	

	int rows;
	int columns;
	float** values;


	void printMatrix();
	//Constructor
	Matrix matrix(int r, int c);

	//Destructor
	void freeMatrix();

	//assign a specific element at a specified place
	void setElement(int r, int c, float value);

	//make a diagonal matrix  -- Rename maindiangonal ???
	void eye();

	//overload addition for matrices
	Matrix& operator + (Matrix& m);

	Matrix& operator - (Matrix& m);

	Matrix& operator * (Matrix& m);									//Matrix * Matrix
	Matrix& operator * (float scalar);								//Matrix * Scalar
	friend Matrix& operator * (const float scalar, const Matrix m); //Scalar * Matrix

	//overload = Next
	

};


//Scalar * Matrix
