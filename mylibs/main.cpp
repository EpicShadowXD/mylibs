#include <iostream>
#include <vector>
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
    matrix<int> myMatrix(3, 3);

    myMatrix[0][0] = 1; myMatrix[0][1] = 2; myMatrix[0][2] = 7;
    myMatrix[1][0] = 3; myMatrix[1][1] = 4; myMatrix[1][2] = 8;
    myMatrix[2][0] = 5; myMatrix[2][1] = 6; myMatrix[2][2] = 9;
    
    matrix<int>::iterator it = nullptr;

    for (int i = 0; i < myMatrix.col_size(); ++i)
    {
        it = myMatrix.row_begin(i);
        output(it, myMatrix.row_size());
    }
}
