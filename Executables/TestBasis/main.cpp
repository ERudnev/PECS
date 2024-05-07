#include <iostream>

#include <Basis/Testing/environment.h>
#include <Basis/logger.h>

basis::Logger logger("basis_tests");

void dummy()
{
    logger.print("dummy test performed");
}

int main()
{
    basis::testing::Statistics statistics;
    TEST(dummy);
    return 0;
}