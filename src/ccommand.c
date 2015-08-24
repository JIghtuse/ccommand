#include <ccommand.h>

#include <stdlib.h>

int ccommand_exec(const char *cmd)
{
    system(cmd);
    return 0;
}
