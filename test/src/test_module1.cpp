#include "CppUTest/TestHarness.h"
#include "module1.h"
TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   goodbyeWorld();
   FAIL("Fail me!");
}