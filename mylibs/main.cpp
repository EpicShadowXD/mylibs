#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    matrix<int> test(2, 2);
    test.data[0][0];
    std::cout << test.data[0][0];
}