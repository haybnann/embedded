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
	Matrix();
	Matrix(int r, int c);

	//Destructor
	~Matrix();

	//assign a specific element at a specified place
	void setElement(int r, int c, float value);

	//make a diagonal matrix  -- Rename maindiangonal ???
	void eye();

	//overload addition for matrices
	Matrix& operator + (const Matrix& m);

	Matrix operator - (Matrix m);


	//Rewrite to make params pass by reference ???
	Matrix operator * (Matrix m);									//Matrix * Matrix
	Matrix operator * (float scalar);								//Matrix * Scalar
	friend Matrix operator * (const float scalar, const Matrix m); //Scalar * Matrix


	Matrix& operator = (const Matrix& matrix);
	//overload = Next
	

};


//Scalar * Matrix
