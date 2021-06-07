#pragma once

/*
* The purpose of this class is to provide a simple, easy to use matrix operations for use with Kalman Filters and other controls software.
*/



class Matrix
{
	
private:	
	int rows;
	int columns;
	float** values;
protected:

public:	


	//Constructors
	Matrix();
	Matrix(const Matrix& matrix);
	Matrix(int r, int c);

	//Destructor
	~Matrix();

	/***Operator Overload //***/
	Matrix& operator =  (const Matrix& matrix);
	Matrix& operator += (const Matrix& matrix);
	Matrix& operator -= (const Matrix& matrix);
	Matrix& operator *= (const Matrix& matrix);

	friend const Matrix operator + (const Matrix& first_op, const Matrix& second_op);
	friend const Matrix operator - (const Matrix& first_op, const Matrix& second_op);
	friend const Matrix operator * (const Matrix& first_op, const Matrix& second_op);

	Matrix& operator * (float scalar);								//Matrix * Scalar
	friend Matrix operator * (const float scalar, const Matrix& m); //Scalar * Matrix

	void Transpose();
	void Inverse();
	void Identity();

	//debug
	void printMatrix();
};



