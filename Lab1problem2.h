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