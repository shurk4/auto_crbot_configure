#include <iostream>
#include <stdio.h>
#include <string>

#include "config.h"

bool mainMenu(Config &cfg);
void convertParamMenu(Config &cfg);
void showConfig(Config &cfg);
void showDomains(std::vector<std::string> domains);
void showConvertParam(Config &cfg);

bool mainMenu(Config &cfg)
{
    std::string input;
    std::cout << "Select a menu item\n"
              << "1 - Certbot certificates dir(Default: /etc/letsencrypt/archive)\n"
              << "2 - Set e-mail\n"
              << "3 - Add domain\n"
              << "4 - Set unix user password\n"
              << "5 - Copy the certificate to the directory\n"
              << "    If no directory is specified, the certificate will be placed in the default directory /etc/letsencrypt\n"
              << "6 - Convert the certificate\n"
              << "r - Remove domain\n"
              << "c - Clear config\n"
              << "s - Save config\n"
              << "q - quit\n";

    std::cin >> input;
    std::cout << std::endl;
    if(input == "1")
    {
        std::cout << "Enter the path to the certbot certificate storage directory\n";
        std::cin >> input;

        if(!input.empty())
        {
            if(input[input.size() - 1] == '/')
            {
                input.pop_back();
            }
            cfg.setCertDir(input);
        }
    }
    else if(input == "2")
    {
        std::cout << "Enter e-mail: ";
        std::cin >> input;

        if(!input.empty())
        {
            cfg.setEmail(input);
        }
    }
    else if(input == "3")
    {
        std::cout << "Enter domain: ";
        std::cin >> input;

        if(!input.empty())
        {
            cfg.addDomain(input);
        }
    }
    else if(input == "4")
    {
        std::cout << "Enter user password: ";
        std::cin >> input;

        if(!input.empty())
        {
            cfg.setUserPass(input);
        }
    }
    else if(input == "5")
    {
        std::cout << "Enter the target directory to copy the certificate to:\n";
        std::cin >> input;

        if(!input.empty())
        {
            cfg.setTargetDir(input);
        }
    }
    else if(input == "6")
    {
        convertParamMenu(cfg);
    }
    else if(input == "r")
    {
        int domainsNum = cfg.getDomainsNum();
        if(domainsNum == 0)
        {
            std::cout << "Domains are not specified\n";
        }
        else if(domainsNum == 1)
        {
            cfg.removeDomain(0);
        }
        else
        {

            int num;

            do {
                std::cout << "Enter the domain number: ";
                std::cin >> input;
                num = std::stoi(input);
                if(num >= 0 && num < domainsNum)
                {
                    cfg.removeDomain(num);
                }
                else
                {
                    std::cout << "Incorrect input!";
                }
            } while(num < 0 || num >= domainsNum);
        }
    }
    else if(input == "c")
    {
        cfg.clearConfig();
    }
    else if(input == "s")
    {
        cfg.writeConfig();
    }
    else if(input == "q" || input == "Q")
    {
        return false;
    }
    else
    {
        std::cout << "Incorrect input!\n";
    }
    return true;
}

void convertParamMenu(Config &cfg)
{
    std::string input = "";
    do{
        showConvertParam(cfg);

        std::cout << "Convert to:\n";
        std::cout << "1 - *.key\n"
                  << "2 - *.crt\n"
                  << "3 - Set the certificate name\n"
                  << "n - Do not convert\n"
                  << "b - Return to the main menu\n";

        std::cin >> input;
        std::cout << std::endl;

        if(input == "1")
        {
            cfg.addCertConvertParam(KEY);
        }
        else if(input == "2")
        {
            cfg.addCertConvertParam(CRT);
        }
        else if(input == "3")
        {
            std::cout << "Enter the certificate name: ";
            std::cin >> input;
            if(!input.empty())
            {
                cfg.setCertName(input);
            }
        }
        else if(input == "n")
        {
            cfg.clearCertConvertParam();
        }
        else
        {
            std::cout << "Incorrect input!\n";
        }
    }while(input != "b");
}

void showConfig(Config &cfg)
{
//    system("clear");
    std::cout << "\n-------------------------------------\n" << "\tCurrent configuration:\n";
    std::cout << "Path to the certbot certificates dir: " << cfg.getCertDir() << "\n";
    std::cout << "Your e-mail: " << cfg.getEmail() << "\n";

    showDomains(cfg.getDomains());

    std::cout << "Target certificates dir: " << cfg.getTargetDir() << "\n";

    showConvertParam(cfg);

    std::cout << "User password: ";
    if(cfg.haveUserPassword())
    {
        std::cout << "specified\n";
    }
    else
    {
        std::cout << "Not specified\n";
    }

    std::cout << "\n-------------------------------------\n" << std::endl;
}

void showDomains(std::vector<std::string> domains)
{
    std::cout << "Your domains:\n";
    if(domains.empty())
    {
        std::cout << "Not specified\n";
    }
    else
    {
        for(int i = 0; i < domains.size(); i++)
        {
            std::cout << i << ") " << domains[i] << "\n";
        }
    }
    std::cout << std::endl;
}

void showConvertParam(Config &cfg)
{
    std::cout << "Current convert parameters:\n";
    int param = cfg.getCertConvertParam();
    if(param & KEY)
    {
        std::cout << "*.key\n";
    }
    if(param & CRT)
    {
        std::cout << "*.crt\n";
    }
    if(param & NO || param == 0)
    {
        std::cout << "Do not convert\n";
    }

    std::cout << "Target certificate name: " << cfg.getCertName() << "\n";

    std::cout << std::endl;
}
