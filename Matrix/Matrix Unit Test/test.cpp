#include "pch.h"
#include "matrix.h"


TEST(MatrixTest, Constructor) {

	Matrix mat;
	int row = 4, col = 5;

	mat.matrix(row, col);

	EXPECT_EQ(row, mat.rows);
	EXPECT_EQ(col, mat.columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			EXPECT_EQ(0, mat.values[ii][jj]);
		}
	}
}


TEST(MatrixTest, setElement) {

	Matrix mat;
	int row = 4, col = 4;

	mat.matrix(row, col);
	mat.setElement(1, 3, 2.3);

	EXPECT_FLOAT_EQ(2.3, mat.values[0][2]);
}


TEST(MatrixTest, eye) {

	Matrix mat;
	int row = 4, col = 4;

	mat.matrix(row, col).eye();

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


TEST(MatrixTest, MatrixAdditionOverload) {

	Matrix a, b, c;
	int row = 4, col = 4;

	a.matrix(row, col).eye();
	b.matrix(row, col).eye();

	//this shouldn't work right.. right???
	c = a + b;

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
TEST(MatrixTest, MatrixMultiplicationOverload) {

	Matrix a, b, c;


	a.matrix(1, 3).eye();
	b.matrix(3, 4).eye();

	//this shouldn't work right.. right???
	c = a * b;
	c.printMatrix();
	EXPECT_EQ(1, c.rows);
	EXPECT_EQ(4, c.columns);
/*
	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			if (ii == jj) {
				EXPECT_EQ(2, c.values[ii][jj]);
			}
			else {
				EXPECT_EQ(0, c.values[ii][jj]);
			}

		}
	}*/
}

TEST(MatrixTest, PrintMatrix) {
	Matrix a;
	a.matrix(3, 4).eye();

	a.printMatrix();
}