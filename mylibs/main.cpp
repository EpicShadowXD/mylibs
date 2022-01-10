#include <iostream>
#include "matrix.cpp"

using namespace std;

void outputUp(matrix<int>::iterator& it, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << *it  << ' ';
        it++;
    } std::cout << std::endl;
}

void outputDown(matrix<int>::iterator& it, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << *it << ' ';
        it--;
    } std::cout << std::endl;
}

int main()
{
    // matrix<Type> name(numberOfColumns, numberOfRows)
    matrix<int> myMatrix(3, 3), copy(3, 3);
    matrix<int>::iterator it = nullptr;

    myMatrix[0][0] = 1; myMatrix[0][1] = 2; myMatrix[0][2] = 7;
    myMatrix[1][0] = 3; myMatrix[1][1] = 4; myMatrix[1][2] = 8;
    myMatrix[2][0] = 5; myMatrix[2][1] = 6; myMatrix[2][2] = 9;

    copy = myMatrix;
    std::cout << copy << std::endl;
    // Error at resize
    //copy.resize(2, 2);

    it = copy.colBegin(0);
    std::cout << "Forwards\n";
    outputUp(it, copy.getColSize());

    // Silent runtime error
    // columnIterator has old values, not references
    copy[0][0] = 10;
    copy[1][0] = 11;
    copy[2][0] = 12;

    it--;
    std::cout << "Backwards\n";
    outputDown(it, copy.getColSize());
}
