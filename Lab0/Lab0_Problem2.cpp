/*
Author:  Haolat Adebayo
Date last modified: 9/12/2022
Organization: ECE4122_6122 Class

Description:

Simple function to determine the number of times 1 is added to
an input number to be dividible by 7 and eventually get 1 as the 
last number 
    
*/

#include <iostream>
using namespace std;
int numadded;

/**
*  \Function to recurively determine number of 
*  \1s added to be completly divide by 7 
*  \brief Fibonacci Series using Recursion
* 
* \param[in]      n       Index of number to calculate.
* 
* \return                 number of 1s addeded for given index n.
*/
int oneMoreOne(int n)
{
	if ( n == 1)
	{
		return numadded;
	}	
	else 
	{
		if (n % 7 == 0)
		{
			n = n/7;
		}	
		else
		{
			n += 1;
			numadded++;
		}
		return oneMoreOne(n);	
	} 
	
}


int main()
{
	int n; 
	while (1) {
		cout << "Please enter the starting number n: ";
		cin >> n;
		cout << endl;
		if (n == -1)
		{
			cout << "Invalid input!! Please try again." << endl << endl;
			continue; 
		}
		if (n == 0)
		{
			break;
		}
		numadded = 0;	
		cout << "The sequence had " << oneMoreOne(n) << " instances of the number 1 being added" << endl << endl;
	}
    
}


