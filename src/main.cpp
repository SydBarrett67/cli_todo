#include <iostream>

#include "commands.h"

int main(int argc, char* argv[]) {

    // Check if at least a command has been entered
    if (argc > 1) {
        Commands::execute(Commands::parse(argc, argv));
    }
    else {
        std::cout << 
            "todo [cmd] [arguments] [-flags]\n\n"                           <<
            "Commands  |  Desc\n\n"                                         <<
            "new       |  Creates new \"todo\" file in working directory\n" <<
            "add       |  Adds an [arg] specified line in \"todo\" file\n"  <<
            "check     |  Checks (deletes) an index-specified entry.\n"     <<
            "read      |  Prints the \"todo\" file contents to console.\n"  <<
            "delete    |  Deletes \"todo\" file\n";
    }
    
}