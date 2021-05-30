#pragma once

//TO DO: Add Accessors foir testing ... or use namespace.. idk find what works best

class Matrix
{
	
private:

protected:

public:	

	int rows;
	int columns;
	float** values;


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

	void Identity();// Rename maindiangonal ???

	//debug
	void printMatrix();
};



