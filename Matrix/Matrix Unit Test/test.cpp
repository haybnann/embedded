#include "pch.h"
#include "matrix.h"


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


TEST(MatrixTest, setElement) {
	
	int row = 4, col = 4;

	Matrix mat = Matrix(row, col);

	mat.setElement(1, 3, 2.3);

	EXPECT_FLOAT_EQ(2.3, mat.values[0][2]);
}


TEST(MatrixTest, eye) {

	int row = 4, col = 4;
	
	Matrix mat = Matrix(row, col);
	mat.eye();

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

TEST(MatrixTest, MatrixEqualityOverload) {

	int row = 4, col = 4;

	Matrix a = Matrix(row, col);
	Matrix b;

	a.eye();

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
	
	a.eye();
	b.eye();

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

	a.eye();
	b.eye();

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

	a.eye();
	b.eye();

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
	a.eye();

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
	a.eye();

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



TEST(MatrixTest, ReducedRowEchelonForm) {
	Matrix a= Matrix(5, 5);
	
	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = ii + jj + 1;
		}
	}
	
	//a.PartialPivot(a);
	a.printMatrix();
	a.rref();
	a.printMatrix();

}


TEST(MatrixTest, PartialPivotTest) {
	Matrix a;
	a = Matrix(8, 5);

	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = ii + jj + 1;
		}
	}
	a.PartialPivot(a);
	

	//Write test to check if max num in col 1 is in row 1----- TO DO
}


TEST(MatrixTest, PrintMatrix) {
	Matrix a = Matrix(3, 4);
	
	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = ii + jj + 1;
		}
	}
	a.printMatrix();
	a.Transpose();
	a.printMatrix();


	//a.printMatrix();
}
