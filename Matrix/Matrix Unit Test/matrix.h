#pragma once
class Matrix
{
	
private:

protected:


public:	

	int rows;
	int columns;
	float** values;

	//debug
	void printMatrix();

	//Constructors
	Matrix();
	Matrix(const Matrix& matrix);
	Matrix(int r, int c);

	//Destructor
	~Matrix();

	//assign a specific element at a specified place
	void setElement(int r, int c, float value);

	//make a diagonal matrix  -- Rename maindiangonal ???
	void eye();

	//overload addition for matrices
	
	Matrix& operator = (const Matrix& matrix);

	Matrix& operator += (const Matrix& m);
	friend const Matrix operator + (const Matrix& first_operand, const Matrix& second_operand);

	Matrix& operator -= (const Matrix& m);
	friend const Matrix operator - (const Matrix& first_op, const Matrix& second_op);

	Matrix& operator*= (const Matrix& m);
	friend const Matrix operator * (const Matrix& first_op, const Matrix& second_op);
	//Rewrite to make params pass by reference ???
	//Matrix& operator * (Matrix& m);									//Matrix * Matrix
	Matrix& operator * (float scalar);								//Matrix * Scalar
	friend Matrix operator * (const float scalar, const Matrix& m); //Scalar * Matrix




	//overload = Next
	

};


//Scalar * Matrix
