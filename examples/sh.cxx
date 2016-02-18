#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ccommand.h>

class Command {
public:
    Command(const std::string& name)
        : cmd{}
    {
        auto ret = ccommand_init(&cmd, name.c_str());
        if (ret < 0)
            throw std::runtime_error{ "cannot instantiate command" };
    }

    ~Command()
    {
        ccommand_cleanup(&cmd);
    }

    void addArg(const std::string& arg)
    {
        auto ret = ccommand_add_arg(&cmd, arg.c_str());
        if (ret < 0)
            throw std::runtime_error{ "cannot add argument" };
    }

    void exec()
    {
        if (ccommand_exec(&cmd) < 0)
            throw std::runtime_error{ "execution error" };
    }

private:
    ccommand cmd;
};

// system()-like function
void execute_command(const std::string& s)
{
    std::string name;
    std::stringstream iss(s);
    iss >> name;

    try {
        Command command{ name };
        for (std::string arg; iss >> arg;)
            command.addArg(arg);
        command.exec();
    }
    catch (std::runtime_error& e) {
        std::cerr << "failed to execute '" << s << "': " << e.what() << '\n';
    }
}

// Dumb shell
int main()
{
    const std::string prompt{ "$ " };
    const std::string exit{ "exit" };

    std::cout << prompt;
    for (std::string s; std::getline(std::cin, s);) {
        if (s == exit)
            break;
        execute_command(s);
        std::cout << prompt;
    }
    std::cout << exit << std::endl;
}
