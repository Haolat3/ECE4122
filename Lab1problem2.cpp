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
			if (j==3 || j==6)
				os << " | ";
			os << gridIn.gridElement[i][j] << " ";
		}
		if (i == 2 || i ==5) {
			os << endl;
			for (int k = 0; k < 9; k++)
				os << "---";
		}
		os << endl;
	}
	os << endl;
    return os;
}

//check whether num is present in col or not
bool SudokuGrid::isPresentInCol(int col, int num) {
    for (int row = 0; row < 9; row++)
      if (((int) get_gridElements(row, col)) == num)
         return true;
   return false;
}

//check whether num is present in row or not
bool SudokuGrid::isPresentInRow(int row, int num) {
    for (int col = 0; col < 9; col++)
      if (((int) get_gridElements(row, col)) == num)
        return true;
   return false;
}

//check whether num is present in 3x3 box or not
bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (((int) get_gridElements(row+boxStartRow, col+boxStartCol)) == num)
            return true;
   return false;
}

//get empty location and update row and column
bool SudokuGrid::findEmptyPlace(int &row, int &col) {
    for (row = 0; row < 9; row++)
      for (col = 0; col < 9; col++)
        if (((int) get_gridElements(row, col)) == 0) //marked with 0 is empty
            return true;
   return false;
}


//when item not found in col, row and current 3x3 box
bool SudokuGrid::isValidPlace(int row, int col, int num) {
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,col - col%3, num);
}

//solve the Sudoku 
bool SudokuGrid::solve(void) {
	//int row, col;
    if (!findEmptyPlace(row, col)) 
        return true; //when all places are filled
    for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
        if (isValidPlace(row, col, num))    { //check validation, if yes, put the number in the grid
            set_gridElements(row, col, num);
            if (solve()) //recursively go for other rooms in the grid
                return true;
			//turn to unassigned space when conditions are not satisfied
            set_gridElements(row, col, 0);
        }
    }
   return false;
}

//
unsigned char SudokuGrid:: get_gridElements(int row, int col) {
    return gridElement[row][col]; 
}

void SudokuGrid:: set_gridElements(int row, int col, int num) {
    gridElement[row][col] = (unsigned char) num; 
}





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


int main(int argc, char **argv) {
	std::vector<std::thread> threadObjects;
	int numThreads = 20;
	outFile.open ("Lab2prob2.txt", std::fstream::out);
	if (argc > 1) {
		inFile.open(argv[1], std::fstream::in);
		if (!inFile.is_open()) {
			cout << "Could not open input file" << endl;
			return 0;
		} 
		if (!outFile.is_open()) {
			cout << "Could not open output file" << endl;
			return 0;
		}  

		outFile << "Solve results" << endl << endl;

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
	} else {
		cout << "Invalid Input File!" << endl;
	}
	outFile.close();
	return 0;
}
