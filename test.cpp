#include <iostream>

int main()
{
    std::string pass = "magic1";



    std::cout << "Please enter pin code!: " << std::endl;
    std::cout << "pin: " << std::endl;
    std::string  x;
    std::cin >> x;

    if (x == pass)
    {
        std::cout << "Welcome user!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Wrong!" << std::endl;
        return 0;
    }
}
