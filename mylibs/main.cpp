#include <iostream>
#include <vector>
#include "matrix.cpp"

using namespace std;

void output(matrix<int>::iterator it)
{
    std::cout << *it << ' ';
    ++it;
    std::cout << *it << '\n';
}

int main()
{
    matrix<int> myMatrix(2, 2);

    myMatrix[0][0] = 1; myMatrix[0][1] = 2;
    myMatrix[1][0] = 3; myMatrix[1][1] = 4;
    
    matrix<int>::iterator it = nullptr;
    
    it = myMatrix.row_begin(0);
    output(it);

    it = myMatrix.row_begin(1);
    output(it);
}
