# ccommand
C library to launch external commands

### Cloning and building

    git clone https://github.com/JIghtuse/ccommand.git /path/to/ccommand
    mkdir /path/to/ccommand
    mkdir build && cd build
    cmake .. && make

### Examples

Examples can be found in examples/ directory. You can found build instructions
in following section and in root CMakeLists.txt file.

### Usage

Following example can be saved to file ping.c and then built and run like this:

    CFLAGS=-I/path/to/ccommand/include LDFLAGS="-L/path/to/ccommand/build -lccommand" make ping
    LD_LIBRARY_PATH=/path/to/ccommand/build ./ping

ping.c contents:

    /* ping.c */
    #include <stdio.h>
    #include "include/ccommand.h"

    int main()
    {
        struct ccommand cmd;
        const char* host = "ya.ru";
        const int ntries = 3;
        int ret;

        ccommand_init(&cmd, "ping");
        ccommand_add_arg(&cmd, host);
        ccommand_add_arg(&cmd, "-c%d", ntries);
        ret = ccommand_exec(&cmd);
        ccommand_cleanup(&cmd);

        printf("host %s is %s\n", host, ret == 0 ? "available" : "unavailable");

        return 0;
    }
