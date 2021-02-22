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
    std::string passwd;

    passwd = "1234";
    return passwd;
}

bool solved(std::string output)
{

    if (output != vars.whenSolved){
        return true;
    }
    return false;
}

// TODO: Make this multithreaded.
void brute()
{
    std::string passwd = passGen();

    subprocess::popen process(vars.binary, {});
    process.stdin() << passwd << std::endl;


    process.close();
    
    // Figure out how to turn stdout to a string...
    std::string output;

    // output = process.stdout().rdbuf();
    

    vars.isSolved = solved(output);

    if (vars.isSolved)
    {
        std::cout << "######################################" << std::endl;
        std::cout << "PASSWORD FOUND: " << passwd << std::endl;
        std::cout << "######################################" << std::endl;
    }

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


    do
    {
        brute();
    } while (!vars.isSolved);

    return 0;
}
