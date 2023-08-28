#include <iostream>
#include <map>

#include "decorator.h"
#include "proxy.h"


int main()
{
    StartTextDecorator();

    std::cout << std::endl;

    DB();
}