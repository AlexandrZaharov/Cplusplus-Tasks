#include <iostream>
#include <vector>

#include "matrix.h"

int main()
{
	Matrix matrix1(2, 2); 
    Matrix matrix2(2, 2);

	std::cin >> matrix1;
    std::cin >> matrix2;

	std::cout << matrix1 << "\n";
	std::cout << matrix2 << "\n";

	Matrix matrix3 = matrix1 * matrix2;
	std::cout << matrix3 << "\n";

    Matrix matrix4 = matrix3.Transpose();
    std::cout << matrix4 << "\n";

    return 0;
}

