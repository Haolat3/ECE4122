/*
Author:  Haolat Adebayo
Date last modified: 9/25/2022
Organization: ECE4122_6122 Class

Description:

Function to calculate the number of unique paths
from the top of a maze to the buttom
*/
#include <iostream>
#include <vector>
using namespace std;


/**
* \brief Fibonacci Series using Dynamic Programming top-down approach
* 
* \param[in]      n       Index of Fibonacci number to calculate.
* \param[in, out] vecF    Vector of previously calculated Fibonacci numbers.
* 
* \return                 Fibonacci number for given index n.
*/

uint64_t fibDynamicProgrammingTopDown(unsigned int n, vector<uint64_t> & vecF)
{
    if (n < 2 || vecF[n] > 0)
    {
        return vecF[n];
    }

    vecF[n] = fibDynamicProgrammingTopDown(n - 2, vecF) + fibDynamicProgrammingTopDown(n - 1, vecF);

    return vecF[n];
}




/**
* \brief Function to calculate the number of paths from the top of a grid to the bottom
* 
* \param[in]      nRows   Number of rows in the grid.
* \param[in]      nCols   Number of columns in the grid.
* 
* \return                 Number of paths to from top of grid to bottom.
*/
uint64_t numberGridPaths(unsigned int nRows, unsigned int nCols) {
    unsigned int index = ((nCols - 1) * (nRows - 1));
    vector<uint64_t> Fibb(index + 1, -1);

    Fibb[0] = 0;
    Fibb[1] = 1;
    Fibb[2] = 1;
    if ((nCols < 1) || (nRows < 1)) {
        return 0;
    }
    uint64_t Fibb1 = fibDynamicProgrammingTopDown((nCols-1) * (nRows-1),Fibb);
    uint64_t Fibb2 = fibDynamicProgrammingTopDown(nCols-1,Fibb);
    uint64_t Fibb3 = fibDynamicProgrammingTopDown(((nCols-1) * (nRows-1)) - (nCols - 1),Fibb);
    uint64_t result = Fibb1/ (Fibb2 * Fibb3);
    return result;
}