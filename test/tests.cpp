#include <gtest/gtest.h>

#include "SparseMatrix.hpp"

TEST(SparseMatrixTest, SizeTest) 
{
    SparseMatrix<int, 0> matrix;
    EXPECT_EQ(matrix.size(), 0);

    matrix[0][0] = 5;
    EXPECT_EQ(matrix.size(), 1);

    matrix[1][1] = 10;
    EXPECT_EQ(matrix.size(), 2);
}

TEST(SparseMatrixTest, AccessTest) 
{
    SparseMatrix<int, 0> matrix;
    matrix[0][0] = 5;
    matrix[1][1] = 10;

    EXPECT_EQ(matrix[0][0], 5);
    EXPECT_EQ(matrix[1][1], 10);
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
