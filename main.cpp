#include "config.h"
#include "func.hpp"

int main()
{
    std::cout << "\n\tWelcome to the configuration programm for the certbot auto updater.\n";
    Config config;
    config.readConfig();

    std::string input;
    do{
        showConfig(config);
    }while (mainMenu(config));

    return 0;
}
