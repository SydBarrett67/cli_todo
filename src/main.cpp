#include <iostream>

#include "commands.h"

int main(int argc, char* argv[]) {

    // Check if at least a command has been entered
    if (argc >= 1) {
        Commands::execute(argv);
    }
    
}