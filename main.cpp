#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>
#include "subprocess.hpp"


struct variables
{
    std::string binary;
    std::string whenSolved;
    std::string wordlistPath;
    int threads;
    bool wordlist = false;
    bool whenSolvedC;
    bool whenSolvedD;
    bool isSolved = false;
    bool numbers = false;
    bool letters = false;
    bool special = false;
    //other vars

    bool addWords = true;
    std::vector<std::string> words;
    int iteration = 0;

}vars;

void menu()
{
    // TODO: Clean up this mess of a help menu...
    
    std::cout << "\n ▄▄▄▄    ██▓ ███▄    █     ▄▄▄▄    ██▀███   █    ██ ▄▄▄█████▓▓█████  ██▀███  " << std::endl;
    std::cout << "▓█████▄ ▓██▒ ██ ▀█   █    ▓█████▄ ▓██ ▒ ██▒ ██  ▓██▒▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒" << std::endl;
    std::cout << "▒██▒ ▄██▒██▒▓██  ▀█ ██▒   ▒██▒ ▄██▓██ ░▄█ ▒▓██  ▒██░▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒" << std::endl;
    std::cout << "▒██░█▀  ░██░▓██▒  ▐▌██▒   ▒██░█▀  ▒██▀▀█▄  ▓▓█  ░██░░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄  " << std::endl;
    std::cout << "░▓█  ▀█▓░██░▒██░   ▓██░   ░▓█  ▀█▓░██▓ ▒██▒▒▒█████▓   ▒██▒ ░ ░▒████▒░██▓ ▒██▒" << std::endl;
    std::cout << "░▒▓███▀▒░▓  ░ ▒░   ▒ ▒    ░▒▓███▀▒░ ▒▓ ░▒▓░░▒▓▒ ▒ ▒   ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░" << std::endl;
    std::cout << "▒░▒   ░  ▒ ░░ ░░   ░ ▒░   ▒░▒   ░   ░▒ ░ ▒░░░▒░ ░ ░     ░     ░ ░  ░  ░▒ ░ ▒░" << std::endl;
    std::cout << " ░    ░  ▒ ░   ░   ░ ░     ░    ░   ░░   ░  ░░░ ░ ░   ░         ░     ░░   ░ " << std::endl;
    std::cout << " ░       ░           ░     ░         ░        ░                 ░  ░   ░     " << std::endl;
    std::cout << "      ░                         ░                                            " << std::endl;
    std::cout << "version 0.1" << std::endl;
}
void helpMenu()
{
    menu();
    std::cout << "\nUsage:" << std::endl;
    std::cout << "  ./binbrute binary args" << std::endl;
    std::cout << "\nArguments:" << std::endl;
    std::cout << " -h, --help               help for binbrute"                                                              << std::endl;
    std::cout << " -d, --done               stdout string for when solved       --done \"succsess\""                        << std::endl;
    std::cout << " -c, --changed            solved when stdout changes          --changed \"wrong password\""               << std::endl;
    std::cout << " -t, --threads            How many threads to use             --threads 200"                              << std::endl;
    std::cout << " -w, --wordlist path      path to wordlist to use             --wordlist rockyou.txt"                     << std::endl;
    std::cout << " -n, --numbers            Use numbers                         0-9"                                        << std::endl;
    std::cout << " -l, --letters            Use letters                         A-Za-z"                                     << std::endl;
    std::cout << " -s, --special            Use special characters               !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"         << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "\n./binbrute binary -c \"wrong password\" -w \"rockyou.txt\""                                               << std::endl;
    std::cout << "  using a wordlist to bruteforce a binary until the output changes from \"wrong password\"."              << std::endl;
    std::cout << "\n./binbrute binary -d \"welcome \" -l"                                                                     << std::endl;
    std::cout << "  brute force binary until stdout message contains welcome."                                              << std::endl;
    std::cout << "\n./binbrute binary -c \"\" -n -l -s"                                                                       << std::endl;
    std::cout << "  using a combination of numbers, letters and special characters to bruteforce until there is an output." << std::endl;
    std::cout << "" << std::endl;
}

std::string passGen()
{
    // TODO: Make this
    std::string passwd;


    if (vars.wordlist && vars.addWords)
    {
        std::ifstream in(vars.wordlistPath);
        if (!in)
        {
            std::cout << "ERROR: couldn't get wordlist path!" << std::endl;
            exit(1);
        }
        while (std::getline(in, passwd))
        {
            if (passwd.size() > 0)
            {
                vars.words.push_back(passwd);
            }
        }
        vars.addWords = !vars.addWords;
    }
    if (vars.wordlist && !vars.addWords)
    {
        std::string tmp = vars.words[vars.iteration];
        vars.iteration++;
        return tmp;
    }
    


    passwd = "1234";
    return passwd;
}

bool solved(std::string output)
{

    if (output != vars.whenSolved && vars.whenSolvedC && !vars.whenSolvedD)
    {
        return true;
    }
    if (output == vars.whenSolved && !vars.whenSolvedC && vars.whenSolvedD)
    {
        return true;
    }
    return false;
}

// TODO: Make this multithreaded.
void brute()
{
    // Generate the next pass to try
    std::string passwd = passGen();
    // Invoke the binary and give it the pass as stdin
    subprocess::popen process(vars.binary, {});
    process.stdin() << passwd << std::endl;
    process.close();
    // Save the output of the string
    std::ostringstream tmp;
    std::string output;
    tmp <<  process.stdout().rdbuf();
    output = tmp.str();
    // TODO: Fix the check
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
    // TODO: Fix the argparseing cause it's shit!
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
        if ((arg == "-d") || (arg == "--done"))
        {
            vars.whenSolved = argv[i+1];
            vars.whenSolvedC = true;
            vars.whenSolvedD = false;
            
        }
        if ((arg == "-c") || (arg == "--changed"))
        {
            vars.whenSolved = argv[i+1];
            vars.whenSolvedC = false;
            vars.whenSolvedD = true;

        }
        // TODO: Make the path for the wordlist not a std::string
        if ((arg == "-w") || (arg == "--wordlist"))
        {
            vars.wordlistPath = argv[i+1];
            vars.wordlist = true;

        }
        if ((arg == "-t") || (arg == "--threads"))
        {
            // TODO: figure how to cast this to int.
            //vars.threads = argv[i+1];
        }
        if ((arg == "-n") || (arg == "--numbers"))
        {
            vars.numbers = true;
        }
        if ((arg == "-l") || (arg == "--letters"))
        {
            vars.letters = true;
        }
        if ((arg == "-s") || (arg == "--special"))
        {
            vars.special = true;
        }
        if (vars.whenSolvedC && vars.whenSolvedD)
        {
            std::cout << "\nConflicting arguments!" << std::endl;
            return 0;
        }
    }
    std::string path = "./";
    vars.binary = path + (std::string) argv[1];

    menu();
    
    std::cout << "Starting!" << std::endl;
    if (vars.whenSolvedC)
        std::cout << "Done when stdout changes from: " <<  vars.whenSolvedC << std::endl;
    if (vars.whenSolvedD)
        std::cout << "Done when stdout becomes: " <<  vars.whenSolvedD << std::endl;
    if (vars.wordlist)
        std::cout << "Wordlist: " << vars.wordlistPath << std::endl;
    if (vars.numbers)
        std::cout << "Numbers on!" << std::endl;
    if (vars.letters)
        std::cout << "Letters on!" << std::endl;
    if (vars.special)
        std::cout << "Special on!" << std::endl;

    do
    {
        brute();
    } while (!vars.isSolved);

    return 0;
}
