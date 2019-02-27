#pragma once

#include <iostream>
#include <vector>
#include <istream>
#include <ostream>



class Calculator
{
public:
    //Matrix(const size_t height, const size_t width);
    int Add(const int lhs, const int rhs);
    int Sub(const int lhs, const int rhs);
    int Div(const int lhs, const int rhs);
    int Multiply(const int lhs, const int rhs);
    int Expon(const int lhs, const int rhs);
    int Sign(const int lhs, const int rhs);
    int NOD(const int lhs, const int rhs);
    int NOK(const int lhs, const int rhs);
};