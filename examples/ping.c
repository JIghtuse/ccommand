#include <stdbool.h>
#include <stdio.h>
#include <ccommand.h>

bool available(const char *host)
{
    const int ntries = 3;

    struct ccommand cmd;
    ccommand_init(&cmd, "ping");
    ccommand_add_arg(&cmd, host);
    ccommand_add_arg(&cmd, "-c%d", ntries);
    int ret = ccommand_exec(&cmd);
    ccommand_cleanup(&cmd);

    return ret != -1;
}

int main()
{
    const char* host = "ya.ru";

    printf("host %s is %s\n", host, available(host) ? "available" : "unavailable");

    return 0;
}
