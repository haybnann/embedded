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

	void setElement(int r, int c, float value);
	void eye();// Rename maindiangonal ???

	/***Operator Overload //***/
	Matrix& operator =  (const Matrix& matrix);
	Matrix& operator += (const Matrix& matrix);
	Matrix& operator -= (const Matrix& matrix);
	Matrix& operator *= (const Matrix& matrix);

	friend const Matrix operator + (const Matrix& first_op, const Matrix& second_op);
	friend const Matrix operator - (const Matrix& first_op, const Matrix& second_op);
	friend const Matrix operator * (const Matrix& first_op, const Matrix& second_op);

	//Rewrite to make params pass by reference ???

	Matrix& operator * (float scalar);								//Matrix * Scalar
	friend Matrix operator * (const float scalar, const Matrix& m); //Scalar * Matrix




	//overload = Next
	

};



