/*
Author:  Haolat Adebayo
Date last modified: 9/25/2022
Organization: ECE4122_6122 Class

Description:

Simple program to get the number of rows and colums of a maze 
and print the number of unique paths from the top of the maze
to the bottom of the maze into a file 
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace chrono;

uint64_t numberGridPaths(unsigned int nRows, unsigned int nCols);

int main(int argc, char **argv) {
	unsigned int num_row, num_col;
	ofstream out_file;
	out_file.open ("NumberPaths.txt");
	if (argc == 2) {
		num_row = (unsigned int) argv[0];
		num_col = (unsigned int) argv[1];
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		uint64_t num_path = numberGridPaths(num_row, num_col);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time_span);
		cout << "The time taken for calculating the number of paths in grid took " << microseconds.count() << " microseconds.\n";
		out_file << "Total Number Paths:" << num_path << endl;
	} else {
		out_file << "Invalid Input!\n";
	}
	out_file.close();
	return 0;
}
