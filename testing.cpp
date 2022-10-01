#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//global variables 
std::fstream inFile;
std::fstream outFile;

int main(int argc, char **argv) {
    string m_strGridName;
    int GridNum;
    unsigned char gridElement[9][9] = {0}; 
    outFile.open ("Lab2prob2.txt", std::fstream::out);
    gridElement[0][0] = 5; 
    int num = (int) gridElement[0][0];
    cout << " The number is " << num << endl; 
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

        //input 
        inFile >> m_strGridName;
        inFile >> GridNum;
        //getline(inFile, m_strGridName, ' '); 
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                inFile >> gridElement[i][j];
            }
        }


        //output 
        outFile << m_strGridName  << " " << GridNum << endl;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                outFile << gridElement[i][j] << endl;
            }
        }

		outFile << "Solve results" << endl;
		inFile.close();
	} else {
		cout << "Invalid Input File!" << endl;
	}
	outFile.close();
	return 0;

}