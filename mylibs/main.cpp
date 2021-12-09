#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

int main()
{

    matrix<int> myMatrix(2, 2);

    myMatrix[0][0] = 2; myMatrix[0][1] = 3;
    myMatrix[1][0] = 4; myMatrix[1][1] = 5;

    matrix<int>::iterator it = myMatrix.row_end(0);
    std::cout << *it << ' ';
    it -= 1;
    std::cout << *it;
}