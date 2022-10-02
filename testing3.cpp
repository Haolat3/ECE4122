#include <iostream>
using namespace std;

int main () {
    unsigned char arry[1] = {5}; 
    int aab = (int) arry[0];
    int num2 = 5;
    if ( aab == num2) {
        cout << "Unsigned char and int comparism Successful" << endl;
        cout <<"The Unsigned char value is " << arry[0] << endl;
        cout << "The char casted to int is " << aab << endl; 
        cout << "The int is " << num2 << endl;
    }
    int num = 8; 
    unsigned char bbb = (unsigned char) num; 
    cout << "Changing int value 8 to unsigned char is " << (int) bbb << endl;
}