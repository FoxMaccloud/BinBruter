#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>



void helpMenu()
{
    std::cout << "\nBinBrute version 0.1" << std::endl;
    std::cout << "use:" << std::endl;
    std::cout << "./binbrute binary condition args" << std::endl;
    std::cout << "--help help menu" << std::endl;
    std::cout << "" << std::endl;
}

void brute(std::string binary, std::string test)
{
    std::string command = test + " " + binary;
    
    



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

    const std::string binary = (const std::string) argv[1];
    const std::string whenSolved = (const std::string) argv[2];


    const std::string testString = "asdf";

    //brute(binary, testString);
    


    return 0;
}
