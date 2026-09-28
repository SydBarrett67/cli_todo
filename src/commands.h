#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

enum class Command {
    NEW,
    ADD,
    CHECK,
    DELETE,
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

    // Helper for recognizing commands
    static Command parseCommand(const std::string& token) {
        if (token == "new")
            return Command::NEW;

        if (token == "add")
            return Command::ADD;

        if (token == "check")
            return Command::CHECK;

        if (token == "delete")
            return Command::DELETE;

        if (token == "read")
            return Command::READ;

        return Command::UNKNOWN;
    }

public:

    // Parse raw command into CmdInfo struct
    static CmdInfo parse(int argc, char* argv[]) {
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

    // Execute parsed commands
    static void execute(const CmdInfo& info) {

        // Get file path based on argument
        std::filesystem::path filePath =
            std::filesystem::current_path() / "todo.txt";

        switch (info.command) {
            case Command::NEW: {

                // Create file
                std::fstream file(filePath, std::ios::out);

                file << "TODO:\n";

                std::cout << "\nCreated \"todo\" file.\n";

                file.close();

                break;
            }

            case Command::ADD: {
                
                if (info.arguments.empty()) {
                    std::cout << "\nMissing argument\n";
                    break;
                }

                // Open file
                std::fstream file(filePath, std::ios::in | std::ios::out);

                int index = 0;
                std::string line;
                while (std::getline(file, line)) {
                    if (line == "TODO:") continue;

                    if (!line.empty()) {
                        size_t space = line.find(' ');
                        if (space != std::string::npos)
                            index = std::stoi(line.substr(0, space));
                    }
                }
                index++;

                file.clear();
                file.seekp(0, std::ios::end);

                file << index << " - " << info.arguments[0] << "\n";

                std::cout << "\nAdded \"" << info.arguments[0] << "\" in todo file.\n";

                file.close();

                break;
            }

            case Command::CHECK: {
                if (info.arguments.empty()) {
                    std::cout << "\nMissing index\n";
                    break;
                }

                int index_to_delete = 0;

                try {
                    index_to_delete = std::stoi(info.arguments[0]);
                }
                catch (const std::invalid_argument&) {
                    std::cout << "\nInvalid index\n";
                    break;
                }

                std::string result = "";

                std::fstream file(filePath, std::ios::in);

                bool deleted = false;
                std::string line;

                while (std::getline(file, line)) {

                    if (line == "TODO:") {
                        result += line + "\n";
                        continue;
                    }

                    size_t space = line.find(' ');

                    if (space == std::string::npos)
                        continue;

                    int index = std::stoi(line.substr(0, space));

                    if (index == index_to_delete) {
                        deleted = true;
                        continue;
                    }

                    if (deleted) {
                        line.replace(0, space, std::to_string(index - 1));
                    }

                    result += line + "\n";
                }

                file.close();

                std::fstream output(filePath, std::ios::out | std::ios::trunc);
                output << result;

                break;
            }

            case Command::DELETE: {
                
                std::filesystem::remove(filePath);

                break;
            }

            case Command::READ: {

                std::string result = "";

                // Open file
                std::fstream file(filePath, std::ios::in);

                std::string line = "";
                while (std::getline(file, line)) {
                    result += line + "\n";
                }

                std::cout << result << "\n";

                break;
            }

            case Command::UNKNOWN:
                std::cout << "\nUnknown command\n";
                break;
        }
    }
};