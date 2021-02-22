#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include "subprocess.hpp"


struct variables
{
    std::string binary;
    std::string whenSolved;

    //other vars


}vars;


void helpMenu()
{
    std::cout << "\nBinBrute version 0.1" << std::endl;
    std::cout << "use:" << std::endl;
    std::cout << "./binbrute binary condition args" << std::endl;
    std::cout << "--help help menu" << std::endl;
    std::cout << "" << std::endl;
}

void brute()
{

    std::string test = "1234";

    subprocess::popen cmd(vars.binary, {});
    cmd.stdin() << test << std::endl;

    cmd.close();

    std::cout << cmd.stdout().rdbuf();
}

bool solved()
{

}

std::string passGen()
{


}


int main(int argc, char **argv)
{
    if (argc < 2) {
        helpMenu();
        return 0;
    }
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help"))
        {
            helpMenu();
            return 0;
        }
    }

    vars.binary = (std::string) argv[1];
    vars.whenSolved = (std::string) argv[2];

    brute();
    


    return 0;
}
