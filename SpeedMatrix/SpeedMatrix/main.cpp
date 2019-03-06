#include <iostream>
#include <vector>
#include "matrix.h"


#define ASSERT_EQUAL(x, y)                                         \
    if ((x) != (y))                                                \
    {                                                              \
        std::cerr << "Assertion failed. File: " << __FILE__        \
            << " Line: " << __LINE__ << " "                        \
            << x << " != " << y << " ("                            \
            << #x << " != " << #y << ")" << std::endl;             \
        fails_count++;                                             \
    }


void TestGetHeight()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix test_matrix1(6, 6);
    Matrix test_matrix2(2, 86);

    ASSERT_EQUAL(test_matrix1.GetHeight(), 6);
    ASSERT_EQUAL(test_matrix2.GetHeight(), 2);

    if (fails_count == 0)
    {
        std::cerr << "TestGetHeight: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestGetHeight fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestGetWidth()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix test_matrix1(9, 9);
    Matrix test_matrix2(5, 54);

    ASSERT_EQUAL(test_matrix1.GetWidth(), 9);
    ASSERT_EQUAL(test_matrix2.GetWidth(), 54);

    if (fails_count == 0)
    {
        std::cerr << "TestGetWidth: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestGetWidth fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestGetValue()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix test_matrix(2, 2);
    test_matrix.SetValue(0, 0, 1);
    test_matrix.SetValue(0, 1, 2);
    test_matrix.SetValue(1, 0, 3);
    test_matrix.SetValue(1, 1, 4);  

    ASSERT_EQUAL(test_matrix.GetValue(0, 0), 1);
    ASSERT_EQUAL(test_matrix.GetValue(0, 1), 2);
    ASSERT_EQUAL(test_matrix.GetValue(1, 0), 3);
    ASSERT_EQUAL(test_matrix.GetValue(1, 1), 4);

    if (fails_count == 0)
    {
        std::cerr << "TestGetValue: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestGetValue fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestSetValue()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix test_matrix(2, 2);
    test_matrix.SetValue(0, 0, 1);
    test_matrix.SetValue(0, 1, 2);
    test_matrix.SetValue(1, 0, 3);

    ASSERT_EQUAL(test_matrix.GetValue(0, 1), 2);
    ASSERT_EQUAL(test_matrix.GetValue(1, 1), 0);

    if (fails_count == 0)
    {
        std::cerr << "TestSetValue: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestSetValue fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestMultiple()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix test_matrix1(2, 2);
    test_matrix1.SetValue(0, 0, 1);
    test_matrix1.SetValue(0, 1, 2);
    test_matrix1.SetValue(1, 0, 3);
    test_matrix1.SetValue(1, 1, 4);

    Matrix test_matrix2(2, 2);
    test_matrix2.SetValue(0, 0, 5);
    test_matrix2.SetValue(0, 1, 6);
    test_matrix2.SetValue(1, 0, 7);
    test_matrix2.SetValue(1, 1, 8);

    Matrix new_matrix = test_matrix1 * test_matrix2;

    ASSERT_EQUAL(new_matrix.GetValue(0, 0), 19);
    ASSERT_EQUAL(new_matrix.GetValue(0, 1), 22);
    ASSERT_EQUAL(new_matrix.GetValue(1, 0), 43);
    ASSERT_EQUAL(new_matrix.GetValue(1, 1), 50);

    if (fails_count == 0)
    {
        std::cerr << "TestMultiple: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestMultiple fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}


void TestTranspose()
{
    std::cerr << "----------------------" << std::endl;
    int fails_count = 0;

    Matrix test_matrix(2, 2);
    test_matrix.SetValue(0, 0, 1);
    test_matrix.SetValue(0, 1, 2);
    test_matrix.SetValue(1, 0, 3);
    test_matrix.SetValue(1, 1, 4);

    Matrix new_matrix = test_matrix.Transpose();

    ASSERT_EQUAL(test_matrix.GetValue(0, 0), 1);
    ASSERT_EQUAL(test_matrix.GetValue(0, 1), 3);
    ASSERT_EQUAL(test_matrix.GetValue(1, 0), 2);
    ASSERT_EQUAL(test_matrix.GetValue(1, 1), 4);

    if (fails_count == 0)
    {
        std::cerr << "TestTranspose: OK" << std::endl;
    }
    else
    {
        std::cerr << "TestTranspose fails. fails_count = " << fails_count << std::endl;
    }
    std::cerr << "----------------------" << std::endl;
}

int main()
{
    TestGetHeight();
    TestGetWidth();
    TestGetValue();
    TestSetValue(); 
    TestMultiple();
    TestTranspose();

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
    }
    return 0;
}
