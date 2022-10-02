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
#include <chrono>
#include <ctime>
#include "Lab1problem2.h"
using namespace std;
using namespace chrono;

//global variables 
std::mutex outFileMutex;
std::mutex inFileMutex;

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
	unsigned long numThreads = thread::hardware_concurrency();
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
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		//spawn threads 
		for (unsigned long ii = 0 ; ii < numThreads-1 ; ii++) {
			threadObjects.push_back(std::thread(solveSudokuPuzzles));
		}

		//join threads 
		for (auto& th: threadObjects) {
			if (th.joinable())
				th.join();
		}
		
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time_span);
		cout << "The time taken for calculating the number of paths in grid took " << microseconds.count() << " microseconds.\n";
		inFile.close();
		outFile.close();
	} else {
		cout << "Invalid Input or Output File!" << endl;
	}
	return 0;
}
