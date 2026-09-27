#include <iostream>
#include <string>
#include <vector>

enum class Command {
    ADD,
    REMOVE,
    READ,
    UNKNOWN
};

struct CmdInfo {
    Command command;
    std::vector<std::string> flags;
    std::vector<std::string> arguments;
};

class Commands
{
private:
    static Command parseCommand(const std::string& token)
    {
        if (token == "add")
            return Command::ADD;

        if (token == "remove")
            return Command::REMOVE;

        if (token == "read")
            return Command::READ;

        return Command::UNKNOWN;
    }

public:
    static CmdInfo parse(int argc, char* argv[])
    {
        CmdInfo info {
            Command::UNKNOWN,
            {},
            {}
        };

        for (int i=1;i<argc;i++) {
            std::string token = argv[i];

            if (token.empty())
                continue;

            // Flag
            if (token[0] == '-') {
                info.flags.push_back(token);
                continue;
            }

            // Command
            if (info.command == Command::UNKNOWN) {
                Command command = parseCommand(token);

                if (command != Command::UNKNOWN) {
                    info.command = command;
                    continue;
                }
            }

            // Argument
            info.arguments.push_back(token);
        }

        return info;
    }

    static void execute(const CmdInfo& info)
    {
        switch (info.command) {
            case Command::ADD:
                std::cout << "Executing ADD\n";
                break;

            case Command::REMOVE:
                std::cout << "Executing REMOVE\n";
                break;

            case Command::READ:
                std::cout << "Executing READ\n";
                break;

            case Command::UNKNOWN:
                std::cout << "Unknown command\n";
                break;
        }

        std::cout << "\nFlags:\n";

        for (const auto& flag : info.flags)
            std::cout << "  " << flag << '\n';

        std::cout << "\nArguments:\n";

        for (const auto& argument : info.arguments)
            std::cout << "  " << argument << '\n';
    }
};