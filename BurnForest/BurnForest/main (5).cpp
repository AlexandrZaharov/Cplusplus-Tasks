#include <iostream>
#include <vector>
#include "forest.h"


int main()
{

    Forest forest(7, 7);
    forest.SetValue(4, 4, 10, 1, 1);

    while (true)
    {
        std::cout << forest;
        forest.Update();
    }

    return 0;
}