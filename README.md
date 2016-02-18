# ccommand
C library to launch external commands

### Cloning and building

    git clone https://github.com/JIghtuse/ccommand.git /path/to/ccommand
    mkdir /path/to/ccommand
    cd /path/to/ccommand
    mkdir build && cd build
    cmake .. && make

### Examples

Usage examples live in [examples](./examples/) directory:

* [ping](./examples/ping.c) - simple example showing library initialization,
usage, and cleanup.
* [sh](./examples/sh.cxx) - stupid shell written on C++ using ccommand.

Build instructions can be found in the following section and in the root
[CMakeLists.txt](./CMakeLists.txt) file.

### Usage

[ping.c](./examples/ping.c) can be downloaded, built and run like this:

    $ mkdir /tmp/ping_example
    $ cd /tmp/ping_example
    $ curl -O https://raw.githubusercontent.com/JIghtuse/ccommand/master/examples/ping.c
    $ CFLAGS=-I<path_to_ccommand>/include LDFLAGS="-L<path_to_ccommand>/build -lccommand" make ping
    $ LD_LIBRARY_PATH=<path_to_ccommand>/build ./ping

Where `<path_to_ccommand>` is the same path as in
[Cloning and building](#cloning-and-building) section.
