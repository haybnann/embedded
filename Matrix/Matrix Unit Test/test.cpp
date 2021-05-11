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