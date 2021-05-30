#pragma once
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

	//Rewrite to make params pass by reference ???

	Matrix& operator * (float scalar);								//Matrix * Scalar
	friend Matrix operator * (const float scalar, const Matrix& m); //Scalar * Matrix

	void Transpose();
	void Inverse();

	void eye();// Rename maindiangonal ???

	//debug
	void printMatrix();
};



