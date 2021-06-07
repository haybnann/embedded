#include "pch.h"
#include <stdlib.h>


//Ugly trick to access private variables... Don't do this in anything other than tests
#define private public
#include "matrix.h"
#undef private //end ugly trick

TEST(MatrixTest, Default_Constructor) {

	Matrix default_matrix = Matrix();

	EXPECT_EQ(0, default_matrix.rows);
	EXPECT_EQ(0, default_matrix.columns);

	//EXPECT_EQ(true, false);//Note tp Fix test
	//EXPECT_EQ(NULL, values)
}


TEST(MatrixTest, Parameterized_Constructor) {

	int row = 4, col = 5;

	Matrix pc_matrix = Matrix(row, col);

	EXPECT_EQ(row, pc_matrix.rows);
	EXPECT_EQ(col, pc_matrix.columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			EXPECT_FLOAT_EQ(0, pc_matrix.values[ii][jj]);
		}
	}

}


TEST(MatrixTest, Copy_Constructor) {

	int row = 4, col = 5;

	Matrix original = Matrix(row, col);
	Matrix copy = Matrix(original);

	EXPECT_EQ(row, copy.rows);
	EXPECT_EQ(col, copy.columns);

	for (int ii = 0; ii < row; ii++) {
		for (int jj = 0; jj < col; jj++) {
			EXPECT_FLOAT_EQ(0, copy.values[ii][jj]);
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

	///EXPECT_EQ(false, true);//NOTE: find out how to test for destruction
}


TEST(MatrixTest, Equals_Overload) {

	int row = 4, col = 4;

	Matrix a = Matrix(row, col);
	Matrix b;

	a.Identity();
	b = a;

	//I think I'm checking to make sure these aren't pointing to the same location
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


TEST(MatrixTest, Addition_Overload) {
	
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


TEST(MatrixTest, Subtraction_Overload) {

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


TEST(MatrixTest, Multiplication_Overload) {

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


TEST(MatrixTest, Matrix_Scalar_Multiplication_Overload) {

	Matrix a = Matrix(2, 3);
	a.Identity();

	Matrix b = a * (float)5.3;

	EXPECT_EQ(2, b.rows);
	EXPECT_EQ(3, b.columns);

	for (int ii = 0; ii < b.rows; ii++) {
		for (int jj = 0; jj < b.columns; jj++) {
			if (ii == jj) {
				EXPECT_FLOAT_EQ(5.3f, b.values[ii][jj]);
			}
			else {
				EXPECT_FLOAT_EQ(0, b.values[ii][jj]);
			}
		}
	}

}


TEST(MatrixTest, Scalar_Matrix_Multiplication_Overload) {

	Matrix a = Matrix(2, 3);
	a.Identity();

	float v5_3 = 5.3f;

	Matrix b = v5_3 * a  ;

	EXPECT_EQ(2, b.rows);
	EXPECT_EQ(3, b.columns);

	for (int ii = 0; ii < b.rows; ii++) {
		for (int jj = 0; jj < b.columns; jj++) {
			if (ii == jj) {
				EXPECT_FLOAT_EQ(v5_3, b.values[ii][jj]);
			}
			else {
				EXPECT_FLOAT_EQ(0, b.values[ii][jj]);
			}
		}
	}

}


TEST(MatrixTest, Order_of_Operations) {
	///EXPECT_EQ(true, false);
}


TEST(MatrixTest, Transpose) {
	Matrix a = Matrix(3, 4);
	
	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = float(ii + jj + 1);
		}
	}
	a.Transpose();


	//EXPECT_TRUE(0);
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


TEST(MatrixTest, Inverse) {
	Matrix a;
	a = Matrix(5, 5);

	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = float(rand() % 10);
		}
	}
	a.Inverse();

	//EXPECT_TRUE(0);
	//TODO: write out test assertions
}


TEST(MatrixTest, PrintMatrix) {
	Matrix a = Matrix(3, 4);

	for (int ii = 0; ii < a.rows; ii++) {
		for (int jj = 0; jj < a.columns; jj++) {
			a.values[ii][jj] = float(ii + jj + 1);
		}

	}

	//a.printMatrix();
}
