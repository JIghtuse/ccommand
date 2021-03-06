#include <CppUTest/TestHarness.h>

#include <ccommand.h>
#include <cmath>

TEST_GROUP(Ccommand)
{
    struct ccommand cmd;
    void teardown() {
        ccommand_cleanup(&cmd);
    }
};

TEST(Ccommand, InitOk)
{
    const char *program = "/bin/true";
    CHECK_FALSE(0 == ccommand_init(nullptr, nullptr));
    CHECK_FALSE(0 == ccommand_init(nullptr, program));
    CHECK_FALSE(0 == ccommand_init(&cmd, nullptr));

    CHECK_TRUE(0 == ccommand_init(&cmd, program));
    STRCMP_EQUAL(program, cmd.args[0]);
    CHECK_EQUAL(1, cmd.nargs);
}

TEST(Ccommand, AddArgOk)
{
    const char *program = "/bin/true";
    const char *arg = "--help";

    ccommand_init(&cmd, program);

    CHECK_FALSE(0 == ccommand_add_arg(&cmd, nullptr));

    CHECK_TRUE(0 == ccommand_add_arg(&cmd, arg));
    CHECK_EQUAL(2, cmd.nargs);
    STRCMP_EQUAL(arg, cmd.args[1]);

    CHECK_TRUE(0 == ccommand_add_arg(&cmd, "%s", arg));
    CHECK_EQUAL(3, cmd.nargs);
    STRCMP_EQUAL(arg, cmd.args[2]);

    CHECK_TRUE(0 == ccommand_add_arg(&cmd, "%d", 3));
    CHECK_EQUAL(4, cmd.nargs);
    STRCMP_EQUAL("3", cmd.args[3]);

    const int port = 8080;
    const char *hostname = "localhost";

    ccommand_add_arg(&cmd, "http://%s:%d", hostname, port);
    STRCMP_EQUAL("http://localhost:8080", cmd.args[4]);
    CHECK_EQUAL(5, cmd.nargs);
}

TEST(Ccommand, CleanUpOk)
{
    const char *program_false = "/bin/false";
    const char *program_true = "/bin/true";

    ccommand_init(&cmd, program_false);

    ccommand_cleanup(&cmd);
    CHECK_EQUAL(0, cmd.nargs);
    POINTERS_EQUAL(nullptr, cmd.args);

    ccommand_init(&cmd, program_true);
    CHECK_EQUAL(1, cmd.nargs);
    STRCMP_EQUAL(program_true, cmd.args[0]);
}

TEST(Ccommand, RunOk)
{
    const char *program_true = "/bin/true";
    const char *program_false = "/bin/false";
    const char *program_unexistent = "/bin/some_not_existing_program";

    ccommand_init(&cmd, program_true);
    CHECK_EQUAL(0, ccommand_exec(&cmd));
    ccommand_cleanup(&cmd);

    ccommand_init(&cmd, program_false);
    CHECK_EQUAL(1, ccommand_exec(&cmd));
    ccommand_cleanup(&cmd);

    ccommand_init(&cmd, program_unexistent);
    CHECK_EQUAL(-1, ccommand_exec(&cmd));
}

TEST(Ccommand, CapacityWorks)
{
    const char *program_true = "/bin/true";

    ccommand_init(&cmd, program_true);
    CHECK_EQUAL(1, cmd.capacity);
    ccommand_add_arg(&cmd, "a");
    CHECK_EQUAL(2, cmd.capacity);
    ccommand_add_arg(&cmd, "b");
    CHECK_EQUAL(4, cmd.capacity);
    ccommand_add_arg(&cmd, "c");
    CHECK_EQUAL(4, cmd.capacity);
    ccommand_add_arg(&cmd, "d");
    CHECK_EQUAL(8, cmd.capacity);
    ccommand_add_arg(&cmd, "f");
    CHECK_EQUAL(8, cmd.capacity);
    ccommand_cleanup(&cmd);
    CHECK_EQUAL(0, cmd.capacity);

    ccommand_init(&cmd, program_true);
    CHECK_EQUAL(1, cmd.capacity);
    ccommand_cleanup(&cmd);
    CHECK_EQUAL(0, cmd.capacity);
}
