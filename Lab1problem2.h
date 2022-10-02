#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//global variables 
std::fstream inFile;
std::fstream outFile;


//Sudoku grid class 

/// @brief          Sudokugrid class that keeps track of all
///                 the information about a Sudoku grid 
class SudokuGrid 
{
    private:
    string m_strGridName;
    int GridNum;
    unsigned char gridElement[9][9] = {0};
    
    public:
        //int row = 0;
        //int col = 0;
    	friend fstream& operator>>(fstream& os, SudokuGrid & gridIn);
    	friend fstream& operator<<(fstream& os, const SudokuGrid & gridIn);
		bool solve(void);
		bool isPresentInCol(int col, int num);
		bool isPresentInRow(int row, int num);
		bool isPresentInBox(int boxStartRow, int boxStartCol, int num);
        bool findEmptyPlace(int* row, int* col);
        bool isValidPlace(int row, int col, int num);
        int get_gridElement(int row, int col);
        void set_gridElement(int row, int col, int num);
};

/// @brief Friend of class to input in grid elements 
/// @param os  file input is being read from
/// @param gridIn grid class 
/// @return file grid is being read from 
fstream& operator>>(fstream& os, SudokuGrid & gridIn) {
	os >> gridIn.m_strGridName;
    os >> gridIn.GridNum;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			os >> gridIn.gridElement[i][j];
		}
	}
    return os;
}


/// @brief Friend of class to input in grid elements 
/// @param os  file input is being read from
/// @param gridIn grid class 
/// @return file grid is being read from 
fstream& operator<<(fstream& os, const SudokuGrid & gridIn) {
	os << gridIn.m_strGridName << " " << gridIn.GridNum << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			os << gridIn.gridElement[i][j];
		}
		os << endl;
	}
    return os;
}


/// @brief          Checks whether a number is present in column or not
/// @param col      The column index of sudoku grid 
/// @param num      The number to check for 
/// @return         true if the number is present in the column
bool SudokuGrid::isPresentInCol(int col, int num) {
    for (int row = 0; row < 9; row++)
        if (get_gridElement(row, col) == num)
            return true;
    return false;
}


/// @brief              Checks whether a number is present in row or not
/// @param row          The row index of sudoku grid 
/// @param num          The number to check for 
/// @return             true if the number is present in the row 
bool SudokuGrid::isPresentInRow(int row, int num) {
    for (int col = 0; col < 9; col++)
        if (get_gridElement(row, col) == num)
            return true;
    return false;
}


/// @brief                  Checks whether a number is present in 3x3 box or not
/// @param boxStartRow      The starting row index of sudoku grid 
/// @param boxStartCol      The starting column index of sudoku grid
/// @param num              The number to check for 
/// @return                 true if the number is present in the 3 X 3 box 
bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (get_gridElement(row+boxStartRow, col+boxStartCol) == num)
                return true;
    return false;
}


/// @brief          Gets empty location and update row and column
/// @param row      The row index of sudoku grid 
/// @param col      The column index of sudoku grid
/// @return         true if a zero(unfilled) index is found
bool SudokuGrid::findEmptyPlace(int* row, int* col) {
    for (*row = 0; *row < 9; (*row)++)
        for (*col = 0; *col < 9; (*col)++)
            if (get_gridElement(*row, *col) == 0) //marked with 0 is empty
                return true;
    return false;
}


/// @brief          Searches for a number in in columnt, row and current 3x3 box
/// @param row      The row index of sudoku grid 
/// @param col      The column index of sudoku grid 
/// @param num      The number to check for the in the grid 
/// @return         true if the number is found in rol, colum and box 
bool SudokuGrid::isValidPlace(int row, int col, int num) {
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,col - col%3, num);
}


/// @brief      solve the Sudoku grid 
/// @param  
/// @return     true if the grid is solved 
bool SudokuGrid::solve(void) {
	int row, col;
    if (!findEmptyPlace(&row, &col))  {
        return true; //when all places are filled
	}
    for (int num = 1; num <= 9; num++) { //valid numbers are 1 - 9
        if (isValidPlace(row, col, num))    { //check validation, if yes, put the number in the grid
            set_gridElement(row, col, 48 + num);
            if (solve()) //recursively go for other rooms in the grid
                return true;
			//turn to unassigned space when conditions are not satisfied
            set_gridElement(row, col, 48 + 0);
        }
    }
   return false;
}


/// @brief          Gets the character at a particular row and column
/// @param row      The row index of sudoku grid 
/// @param col      The column index of sudoku grid 
/// @return         The number at the row and column index of the grid 
int SudokuGrid:: get_gridElement(int row, int col) {
	int x = (int)gridElement[row][col] - (int)48;
    return x;
}
