#include <iostream>

#include "matrix.cpp"

void exit()
{
    std::cout << std::endl;
    std::cout << "End of program.";
    std::cin.get();
}

int main()
{
    matrix<int> myMatrix(3, 3);

    myMatrix[0][0] = 1; myMatrix[0][1] = 4; myMatrix[0][2] = 7;
    myMatrix[1][0] = 2; myMatrix[1][1] = 5; myMatrix[1][2] = 8;
    myMatrix[2][0] = 3; myMatrix[2][1] = 6; myMatrix[2][2] = 9;

    std::cout << myMatrix;

    exit();
}
