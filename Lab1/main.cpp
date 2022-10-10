/*
Author:  Haolat Adebayo
Date last modified: 10/01/2022
Organization: ECE4122_6122 Class

Description:

Simple program to get the number of rows and colums of a grid 
and print the number of unique paths from the top of the grid
to the bottom of the grid into a file 
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace chrono;

//Function defined in numberGridPaths.cpp 
uint64_t numberGridPaths(unsigned int nRows, unsigned int nCols);


/// @brief 		Program to calculate and print the number of path from top to bottom of a grid
/// @param argc  Number of arguments from command line
/// @param argv  The characters gotten from the command line
/// @return 	zero
int main(int argc, char **argv) {
	unsigned int num_row, num_col;
	int row, col;
	ofstream out_file;
	out_file.open ("NumberPaths.txt", std::fstream::out);
	if (argc == 3) {
		char *a = argv[1];
  		num_row = atoi(a);
		row = atoi(a);
		char *b = argv[2];
  		num_col = atoi(b);
		col = atoi(b);

		if (row < 0 || col < 0) {
			out_file << "Invalid Input!\n";
			out_file.close();
			return 0;
		}

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		uint64_t num_path = numberGridPaths(num_row, num_col);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time_span);

		cout << "The time taken for calculating the number of paths in grid took " << microseconds.count() << " microseconds.\n";
		out_file << "Total Number Paths: " << num_path << endl;
	} else {
		out_file << "Invalid Input!\n";
	}
	out_file.close();
	return 0;
}
