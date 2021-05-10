#include "pch.h"
#include "matrix.h"
TEST(MatrixConstructorTest, Testname) {

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