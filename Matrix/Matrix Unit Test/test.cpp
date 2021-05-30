#include "pch.h"
#include "matrix.h"
#include <stdlib.h>

//TO DO: Test Edge cases

TEST(MatrixTest, Constructor) {

	int row = 4, col = 5;

	Matrix mat = Matrix(row, col);

	EXPECT_EQ(row, mat.rows);
	EXPECT_EQ(col, mat.columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			EXPECT_FLOAT_EQ(0, mat.values[ii][jj]);
		}
	}

}


TEST(MatrixTest, Destructor) {

	int row = 4, col = 5;

	Matrix* mat;
	mat = new Matrix(row, col);

	EXPECT_EQ(row, mat->rows);
	EXPECT_EQ(col, mat->columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			EXPECT_FLOAT_EQ(0, mat->values[ii][jj]);
		}
	}
	delete mat;
}


TEST(MatrixTest, MatrixEqualityOverload) {

	int row = 4, col = 4;

	Matrix a = Matrix(row, col);
	Matrix b;

	a.Identity();

	b = a;

	EXPECT_FALSE(&a == &b);
	EXPECT_FALSE(&(a.values) == &(b.values));

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			if (ii == jj) {
				EXPECT_EQ(1, b.values[ii][jj]);
			}
			else {
				EXPECT_EQ(0, b.values[ii][jj]);
			}
		}
	}
}


TEST(MatrixTest, MatrixAdditionOverload) {
	
	int row = 4, col = 4;
	
	Matrix a = Matrix(row, col);
	Matrix b = Matrix(row, col);
	
	a.Identity();
	b.Identity();

	Matrix c;

	c = (a + b);

	EXPECT_EQ(row, c.rows);
	EXPECT_EQ(col, c.columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			if (ii == jj) {
				EXPECT_EQ(2, c.values[ii][jj]);
			}
			else {
				EXPECT_EQ(0, c.values[ii][jj]);
			}
			
		}
	}
}


TEST(MatrixTest, MatrixSubtractionOverload) {

	int row = 4, col = 4;

	Matrix a = Matrix(row, col);
	Matrix b = Matrix(row, col);

	a.Identity();
	b.Identity();

	Matrix c = a - b;

	EXPECT_EQ(row, c.rows);
	EXPECT_EQ(col, c.columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			EXPECT_EQ(0, c.values[ii][jj]);
		}
	}
}


TEST(MatrixTest, MatrixMultiplicationOverload) {

	Matrix a = Matrix(2, 3);
	Matrix b = Matrix(3, 4);

	a.Identity();
	b.Identity();

	Matrix c = a * b;

	EXPECT_EQ(2, c.rows);
	EXPECT_EQ(4, c.columns);

	for (int ii = 0; ii < c.rows; ii++) {
		for (int jj = 0; jj < c.columns; jj++) {
			if (ii == jj) {
				EXPECT_FLOAT_EQ(1, c.values[ii][jj]);
			}
			else {
				EXPECT_FLOAT_EQ(0, c.values[ii][jj]);
			}

		}
	}
}


TEST(MatrixTest, MatrixScalarMultiplicationOverload) {

	Matrix a = Matrix(2, 3);
	a.Identity();

	Matrix b = a * (float)5.3;

	EXPECT_EQ(2, b.rows);
	EXPECT_EQ(3, b.columns);

	for (int ii = 0; ii < b.rows; ii++) {
		for (int jj = 0; jj < b.columns; jj++) {
			if (ii == jj) {
				EXPECT_FLOAT_EQ(5.3, b.values[ii][jj]);
			}
			else {
				EXPECT_FLOAT_EQ(0, b.values[ii][jj]);
			}
		}
	}

}


TEST(MatrixTest, ScalarMatrixMultiplicationOverload) {

	Matrix a = Matrix(2, 3);
	a.Identity();

	Matrix b = (float)5.3 * a  ;

	EXPECT_EQ(2, b.rows);
	EXPECT_EQ(3, b.columns);

	for (int ii = 0; ii < b.rows; ii++) {
		for (int jj = 0; jj < b.columns; jj++) {
			if (ii == jj) {
				EXPECT_FLOAT_EQ(5.3, b.values[ii][jj]);
			}
			else {
				EXPECT_FLOAT_EQ(0, b.values[ii][jj]);
			}
		}
	}

}


TEST(MatrixTest, Transpose) {
	Matrix a = Matrix(3, 4);
	
	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = ii + jj + 1;
		}
	}
	//a.printMatrix();
	a.Transpose();
	//a.printMatrix();


	EXPECT_TRUE(0);
	//TODO: write out test assertions
}


TEST(MatrixTest, Identity) {

	int row = 4, col = 4;
	
	Matrix mat = Matrix(row, col);
	mat.Identity();

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			if (ii == jj) {
				EXPECT_EQ(1, mat.values[ii][jj]);
			}
			else {
				EXPECT_EQ(0, mat.values[ii][jj]);
			}
		}
	}
}

TEST(MatrixTest,InverseTest) {
	Matrix a;
	a = Matrix(5, 5);

	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = rand() % 10;
		}
	}
	a.printMatrix();
	a.Inverse();
	a.printMatrix();
	

	//EXPECT_TRUE(0);
	//TODO: write out test assertions
}


TEST(MatrixTest, PrintMatrix) {
	Matrix a = Matrix(3, 4);

	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = ii + jj + 1;
		}

	}

	//a.printMatrix();
}
