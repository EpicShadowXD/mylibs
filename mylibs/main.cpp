#include <iostream>
#include "matrix.cpp"

using namespace std;

void output(matrix<int>::iterator& it, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << *it << ' ';
        it++;
    } std::cout << std::endl;
}

int main()
{
    matrix<int> myMatrix(3, 3), copy(3, 4);
    matrix<int>::iterator it = nullptr;

    myMatrix[0][0] = 1; myMatrix[0][1] = 2; myMatrix[0][2] = 7;
    myMatrix[1][0] = 3; myMatrix[1][1] = 4; myMatrix[1][2] = 8;
    myMatrix[2][0] = 5; myMatrix[2][1] = 6; myMatrix[2][2] = 9;

    copy = copy + myMatrix;
    std::cout << copy << std::endl;

    it = copy.colBegin(0);
    output(it, copy.getColSize());

    it = copy.rowBegin(0);
    output(it, copy.getRowSize());
}
