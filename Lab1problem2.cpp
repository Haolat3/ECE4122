/*
Author:  Haolat Adebayo
Date last modified: 9/25/2022
Organization: ECE4122_6122 Class

Description:
program to solve a sudoku problem 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include "Lab1problem2.h"
using namespace std;

//global variables 
std::mutex outFileMutex;
std::mutex inFileMutex;


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

/// @brief          Sets the character at a particular row and column
/// @param row      The row index of sudoku grid 
/// @param col      The column index of sudoku grid 
/// @param num      The number that is written to the row and column index of the grid 
void SudokuGrid:: set_gridElement(int row, int col, int num) {
    gridElement[row][col] = (unsigned char)  num; 
}


/// @brief Thread function to read in sudoku grid, solve the puzzle, and output the sudoku solution
/// @param  
void solveSudokuPuzzles(void) {
	SudokuGrid suduk;
	bool isSolved = false;
	do {
		inFileMutex.lock();
		if (inFile.eof()) {
			break;
		} else {
			inFile >> suduk;
		}
		inFileMutex.unlock();
		isSolved = suduk.solve();
		if (isSolved) {
			outFileMutex.lock();
			outFile << suduk;
			outFileMutex.unlock();
		}
	} while(true);
	inFileMutex.unlock();
}

/// @brief  		Main function to get command line arguments for input and output
///					file, spawn threads, join and connect the threads 
/// @param argc 	Number of arguments from command line
/// @param argv 	The characters gotten from the command line
/// @return 		zero
int main(int argc, char **argv) {
	std::vector<std::thread> threadObjects;
	int numThreads = 20;
	SudokuGrid suduk;
	bool isSolved = false;
	if (argc == 3) {
		inFile.open(argv[1], std::fstream::in);
		outFile.open (argv[2], std::fstream::out);
		if (!inFile.is_open()) {
			cout << "Could not open input file" << endl;
			return 0;
		} 
		if (!outFile.is_open()) {
			cout << "Could not open output file" << endl;
			return 0;
		}  

		//setting a value to 5
		//suduk.set_gridElement(1, 0, 48 + 5);
		//getting the value of a place 
		//cast the char to int then subtract 48 from it 

		//spawn threads 
		for (int ii = 0 ; ii < numThreads-1 ; ii++) {
			threadObjects.push_back(std::thread(solveSudokuPuzzles));
		}

		//join threads 
		for (auto& th: threadObjects) {
			if (th.joinable())
				th.join();
		}
		

		inFile.close();
		outFile.close();
	} else {
		cout << "Invalid Input or Output File!" << endl;
	}
	return 0;
}
