#include <iostream>
#include "SparseMatrix.hpp"

int main() noexcept
{
    SparseMatrix<int, 0> matrix;

    for (int i = 0; i < 10; ++i) 
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }

    for (int i = 1; i < 9; ++i) 
    {
        for (int j = 1; j < 9; ++j) 
        {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "Number of occupied cells: " << matrix.size() << std::endl;


    for (const auto& [x, y, v] : matrix)
    {
        if (v != 0)
        {
            std::cout << x << ":" << y << " = " << v << std::endl;
        }
    }

	return 0;
}
