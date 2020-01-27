#include <iostream>
#include <assert.h>
#include "matrix.h"


int main()
{
    Matrix<int, -1> matrix;
    assert(matrix.size()==0);

    auto a = matrix(0, 0);
    assert(a==-1);
    assert(matrix.size()==0);

    matrix(100, 100)=314;
    std::cout << matrix[100][100] << std::endl;
    //assert(matrix[100][100]==314);






    return 0;
}

