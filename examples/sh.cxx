#include <iostream>
#include <sstream>
#include <string>
#include <ccommand.h>

using namespace std;

// system()-like function
void system_ccommand(const string& s)
{
    int ret;
    stringstream iss(s);

    string name;
    iss >> name;

    struct ccommand cmd;

    ret = ccommand_init(&cmd, name.c_str());
    if (ret < 0) goto out;

    for (string arg; iss >> arg;) {
        ret = ccommand_add_arg(&cmd, arg.c_str());
        if (ret < 0) goto out;
    }

    if (ccommand_exec(&cmd) < 0)
        cerr << "error: failed to execute '" << s << "'\n";

out:
    ccommand_cleanup(&cmd);
}

// Dumb shell
int main()
{
    const string prompt{"$ "};
    const string exit{"exit"};

    cout << prompt;
    for (string s; getline(cin, s);) {
        if (s == exit)
            break;
        system_ccommand(s);
        cout << prompt;
    }
}
