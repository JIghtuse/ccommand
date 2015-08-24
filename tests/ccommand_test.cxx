#include <CppUTest/TestHarness.h>

#include <ccommand.h>

TEST_GROUP(CcommandExec)
{};

TEST(CcommandExec, TrueSuccess)
{
    ccommand_exec("/bin/true");
}
