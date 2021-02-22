#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include "subprocess.hpp"


struct variables
{
    std::string binary;
    std::string whenSolved;
    bool isSolved = false;

    //other vars


}vars;


void helpMenu()
{
    std::cout << "\nBinBrute version 0.1" << std::endl;
    std::cout << "\nUsage:" << std::endl;
    std::cout << "  ./binbrute binary whenSolvedCondition args" << std::endl;
    std::cout << "\nFlags:" << std::endl;
    std::cout << " -h, --help    help for binbrute" << std::endl;
    std::cout << "" << std::endl;
}

std::string passGen()
{
    std::string pass;

    pass = "1234";
    return pass;
}

bool solved()
{

}

void brute()
{

    subprocess::popen process(vars.binary, {});
    process.stdin() << passGen() << std::endl;


    process.close();
    //std::string output = process.stdout().rdbuf();


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

    std::string path = "./";
    vars.binary = path + (std::string) argv[1];
    vars.whenSolved = (std::string) argv[2];


/*    do
    {
        brute();
    } while (!vars.isSolved)
*/
    return 0;
}
