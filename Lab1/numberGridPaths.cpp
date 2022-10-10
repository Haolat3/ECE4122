/*
Author:  Haolat Adebayo
Date last modified: 10/01/2022
Organization: ECE4122_6122 Class

Description:

Function to calculate the number of unique paths
from the top of a maze to the buttom
*/
#include <iostream>
#include <vector>
using namespace std;

bool first = true; 
vector<vector<uint64_t> > Path_nums;


/**
* \brief Function to calculate the number of paths from the top of a grid to the bottom
* 
* \param[in]      nRows   Number of rows in the grid.
* \param[in]      nCols   Number of columns in the grid.
* 
* \return                 Number of paths to from top of grid to bottom.
*/
uint64_t numberGridPaths(unsigned int nRows, unsigned int nCols) {

    if (first) {
        Path_nums.resize(19, vector<uint64_t>(19, -1));
        for (unsigned int i = 0; i <= 18; i++) {
            Path_nums[0][i] = 0;
            Path_nums[i][0] = 0;
        }
        Path_nums[1][1] = 1;
    }

    first = false; 
      
    //Add the number of paths  into array
    //if it is was not computed before
    if(Path_nums[nRows][nCols] == -1) {
        Path_nums[nRows][nCols] = numberGridPaths(nRows - 1, nCols) + numberGridPaths(nRows, nCols - 1);
    }
  
    return Path_nums[nRows][nCols];
}
