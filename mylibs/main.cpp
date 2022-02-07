#include <iostream>
#include "matrix.cpp"

using namespace std;

void outputUp(matrix<int>::iterator it, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << *it  << ' ';
        it++;
    } std::cout << std::endl;
}

void outputDown(matrix<int>::iterator it, int n)
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
    matrix<int> myMatrix(3, 3);
    matrix<int>::iterator it = nullptr;

    myMatrix[0][0] = 1; myMatrix[0][1] = 2; myMatrix[0][2] = 7;
    myMatrix[1][0] = 3; myMatrix[1][1] = 4; myMatrix[1][2] = 8;
    myMatrix[2][0] = 5; myMatrix[2][1] = 6; myMatrix[2][2] = 9;

    matrix<int> copy(myMatrix);

    //std::cout << copy << std::endl;
    // Error at resize
    //copy.resize(10, 10);
    //std::cout << copy[5][5];

    //it = copy.colBegin(1);

    //std::cout << **(copy.columnVector + 0) << ' ' << **(copy.columnVector + 1) << ' ' << **(copy.columnVector + 2) << '\n';
    //std::cout << *copy.columnVector[0] << ' ' << *copy.columnVector[1] << ' ' << *copy.columnVector[2] << '\n';

    //outputUp(it, 3);

    //copy[0][0] = 10;
    //copy[1][0] = 11;
    //copy[2][0] = 12;

    //std::cout << copy << std::endl;

    //outputUp(it, 3);

    //std::cout << **(copy.columnVector + 2) << ' ' << **(copy.columnVector + 1) << ' ' << **(copy.columnVector + 0) << '\n';
    //std::cout << *copy.columnVector[2] << ' ' << *copy.columnVector[1] << ' ' << *copy.columnVector[0] << '\n';
}
