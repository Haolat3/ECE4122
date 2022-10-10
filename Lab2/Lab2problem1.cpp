/*
Author:  Haolat Adebayo
Date last modified: 10/10/2022
Organization: ECE4122_6122 Class

Description:

Code that shows the use of omp 
for matrix multiplication 
*/

#include <iostream>
#include <fstream>
#include <omp.h>
#include <vector>
using namespace std;

//Input and Output files 
std::fstream inFile;
std::fstream outFile;

//Vector to hold the two matrixes and the 
//result of multiplication  
vector<vector<double>> matrix1;
vector<vector<double>> matrix2;
vector<vector<double>> result;
double resulting; 

//The number of rows and columns in the two matrixes 
int row_num_1, col_num_1;
int row_num_2, col_num_2;

//Function to read in the two matrixes from a file 
void readMatrix(); 

//Function to write the resut of multiplication to a file 
void outputMatrix();



int main(int argc, char **argv) 
{

	if (argc == 2) 
    {
		inFile.open(argv[1], std::fstream::in);
		outFile.open ("MatrixOut.txt", std::fstream::out);
		if (!inFile.is_open()) 
        {
			cout << "Could not open input file" << endl;
			return 0;
		} 
		if (!outFile.is_open()) 
        {
			cout << "Could not open output file" << endl;
			return 0;
		} 
        
        readMatrix();

        //parallel region 
        //multipltying matrix 
        //#pragma omp parallel for collapse(2)
        #pragma omp parallel for reduction(+:resulting)
        for(int i = 0; i < row_num_1; ++i) 
        {
            for(int j = 0; j < col_num_2; ++j)
            {
                resulting = 0; 
                for(int k = 0; k < col_num_1; ++k)
                {
                    resulting += matrix1[i][k] * matrix2[k][j];
                    result[i][j] = resulting;
                }
            }
        }
		
        outputMatrix();
		inFile.close();
		outFile.close();
	} 
    else 
    {
		cout << "Invalid Input or Output File!" << endl;
	}
	return 0;
}

/// @brief          Function to read in the two input 
///                 matrixes from the apporpriate file 
void readMatrix() 
{
    //reading in first matrix 
    inFile >> row_num_1;
    inFile >> col_num_1;
    matrix1.resize(row_num_1, vector<double>(col_num_1, 0));
	for (int i = 0; i < row_num_1; i++)
    {
		for (int j = 0; j < col_num_1; j++) 
        {
			inFile >> matrix1[i][j];
        }
	}

    //reading in second matrix
    inFile >> row_num_2;
    inFile >> col_num_2;
    matrix2.resize(row_num_2, vector<double>(col_num_2, 0));
	for (int i = 0; i < row_num_2; i++) 
    {
		for (int j = 0; j < col_num_2; j++) 
        {
			inFile >> matrix2[i][j];
        } 
	}

    //setting size of output matrix 
    result.resize(row_num_1, vector<double>(col_num_2, 0));
}

/// @brief          Function  to write the output matrix
///                 to the apporpriate file 
void outputMatrix() 
{
    outFile << std::fixed;
    outFile.precision(15); 
    outFile << row_num_1 << " " << col_num_2 << endl; 

    //writing the result of multiplcation to file
	for (int i = 0; i < row_num_1; i++) 
    {
		for (int j = 0; j < col_num_2; j++) 
        {
			outFile << result[i][j] << " ";
		}
        outFile << endl; 
	}
}
