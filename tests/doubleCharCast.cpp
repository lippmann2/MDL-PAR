#include <iostream>

int main()
{
    double bob = 256;//255.999999; //256
    unsigned char fred; //= 2;
    fred = static_cast<unsigned char>(bob);
    unsigned int joe = fred;
    std::cout << joe << std::endl;
}
