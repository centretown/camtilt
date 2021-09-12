// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include <unity.h>
#include <stdio.h>

void test_helloWorld(void)
{
    printf("hello world\n");
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_helloWorld);
    // RUN_TEST(test_function_calculator_subtraction);
    // RUN_TEST(test_function_calculator_multiplication);
    // RUN_TEST(test_function_calculator_division);
    UNITY_END();

    return 0;
}
