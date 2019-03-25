#include "Calc.h"
#include <iostream>
#include <cassert>

void TestAdd()
{

    int fails_count = 0;
    ASSERT_EQUAL(Add(2, 3), 5);
    ASSERT_EQUAL(Add(-4, -9), -13);
    ASSERT_EQUAL(Add(8, 0), 8);

    if (fails_count == 0)
    {
        std::cerr << "TestAdd: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestAdd fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestSub()
{
    int fails_count = 0;
    ASSERT_EQUAL(Sub(2, 3), -1);
    ASSERT_EQUAL(Sub(-4, -9), 5);
    ASSERT_EQUAL(Sub(8, 0), 8);

    if (fails_count == 0)
    {
        std::cerr << "TestSub: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestSub fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestDiv()
{
    int fails_count = 0;
    ASSERT_EQUAL(Div(5, 2), 2);
    ASSERT_EQUAL(Div(1, 5), 0);
    ASSERT_EQUAL(Div(-12, 5), -2);

    if (fails_count == 0)
    {
        std::cerr << "TestDiv: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestDiv fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestMultiply()
{
    int fails_count = 0;
    ASSERT_EQUAL(Multiply(2, 3), 6);
    ASSERT_EQUAL(Multiply(-4, -9), 36);
    ASSERT_EQUAL(Multiply(8, 0), 0);
    ASSERT_EQUAL(Multiply(8, 1), 8);
    ASSERT_EQUAL(Multiply(-24, 2), -48);

    if (fails_count == 0)
    {
        std::cerr << "TestMultiply: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestMultiply fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestExpon()
{
    int fails_count = 0;
    ASSERT_EQUAL(Expon(2, 3), 8);
    ASSERT_EQUAL(Expon(2, -1), 0.5);
    ASSERT_EQUAL(Expon(8, 0), 1);

    if (fails_count == 0)
    {
        std::cerr << "TestExpon: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestExpon fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestSign()
{
    int fails_count = 0;
    ASSERT_EQUAL(Sign(50000, 50000), 1);
    ASSERT_EQUAL(Sign(50000, -50000), 0);

    if (fails_count == 0)
    {
        std::cerr << "TestSign: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestSign fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestGetGCD()
{
    int fails_count = 0;
    ASSERT_EQUAL(GetGCD(15, 1), 1);
    ASSERT_EQUAL(GetGCD(125, 50), 25);
    ASSERT_EQUAL(GetGCD(-231, -140), 7);

    if (fails_count == 0)
    {
        std::cerr << "TestGetGCD: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestGetGCD fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}

void TestGetLCM()
{
    int fails_count = 0;
    ASSERT_EQUAL(GetLCM(50000, 50000), 50000);
    ASSERT_EQUAL(GetLCM(-145, -45), 1305);
    ASSERT_EQUAL(GetLCM(125, 50), 250);

    if (fails_count == 0)
    {
        std::cerr << "TestGetLCM: Ok" << std::endl;
    }
    else
    {
        std::cerr << "TestGetLCM fails. fails count: " << fails_count << std::endl;
    }
    std::cerr << "---------------" << std::endl;
}


int main()
{
    TestAdd();
    TestSub();
    TestDiv();
    TestMultiply();
    TestExpon();
    TestSign();
    TestGetGCD();
    TestGetLCM();
    return 0;
}