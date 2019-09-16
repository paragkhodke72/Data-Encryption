/*
 *Programming Final Assignment                                           EncryDemo.cpp
 * Author: parag khodke
 * Version: Created on May 15th, 2019, last updated on May 16,2019.
 * Copyright: Best practices for programmers based on industry
 * and education standards. This is for educational purposes only.
 * All rights reserved.
 
 * use of Bitwise Operations '&' , '|' -> Encryption od data ->use Vectors
 * we took input from input file and performing encryption [char string]
 * first we will define the masks as follows.
 * then we will read all the characters from a file using Fgets and add into newVector
 * For even position :- Encryption as Follows
 we will Swapping 1 and 4 would result in 01101100
 and the result of that is l in letter.
 For even numberposition the 8 bits are divided into 4,1,2,1 which is A,B,C,D parts respectively
 after shifting the positions will be A,D,C,B
 step 1: Masking the bit for each part, then-> shifting the positions -then-> 'OR' function
 For position 3: Character is l --> binary is --> 01101100
 For odd number position ->we are Swapping 2 and 3 bit and get values in binary ---> 01101010 and -->letter j
 For odd numbers the 8 bits--> divided into 5,1,1,1 which is A,B,C,D parts resp.
 after shift the  A,C,B,D --> Masking the bit for each part --> position shift --> OR function .
 * for odd position --> encryption as follows
 we are Swapping 2 and 3 bit and get values in binary ---> 01101010 and -->letter j
 For odd numbers the 8 bits--> divided into 5,1,1,1 which is A,B,C,D parts resp.
 after shift the  A,C,B,D --> Masking the bit for each part --> position shift --> OR function .
 there are whitepsaces --> we add into vector char W is not changed
 as its in odd position and swaping 2 & 3rd will give same W -->binary--> 01110111
 For whitepsaces --> we add into vector char W is not changed --> binary 01110111
 * After all encrypted data is pushed into another vector and stored in a file
 * print to console output
 */
#include<iostream>
#include<fstream> // file stream
#include<iomanip>
#include<vector> // vector class
#include<string> // string

using namespace std;

#define INF "input.txt" // input file
#define OUTF "output.txt" // output file
//-- Hexadecimal Values as follows:-
#define AF 0xF0     //1111 0000
#define BF 0x08     //0000 1000
#define CF 0x06     //0000 0110
#define DF 0x01     //0000 0001
#define AE 0xF8     //1111 1000
#define BE 0x04     //0000 0100
#define CE 0x02     //0000 0010
#define DE 0x01     //0000 0001

int main()
{
    vector<char> newVector; // create char vector --> 'new vector'
    int count;// count
    FILE* FileP;
    FileP = fopen("input.txt", "r");// open file in R mode
    if (FileP) // checking for input FileP
    {
        while (feof(FileP) == 0) // checking if file is at endOfFile
        {
            count = fgetc(FileP);// to get all charecter
            newVector.push_back(count);// add to endline of vector
        }
    } else
        cerr << "File opening failed"; // print error message
    fclose(FileP);//closing the File
    
    unsigned long x; // take unsigned int
    for (int i = 0; i < newVector.size(); i++) // from i=0 to till length of vector loop
    { // this block is for switching the bits for odd place
        x = (int) newVector[i]; // vector[i] -> copied into x
        if ((char) x == ' ') // if whitespace, do nothing
        {
        } else if (i % 2 == 0)// switching the bits for odd place
        {
            unsigned long a,b,c,d;
            a=(x & AE); // and Operations
            b=(x & BE) >> 1; // and operations right shift to one
            c=(x & CE) << 1; // and operations and left shift to one
            d=(x & DE); //. and Operations
            
            x=c|a|d|b;
            x = c | a | d | b; // OR for swaping
            newVector[i] = (char) x; // copy into vector of char
        }
        else// switching the bits for even place
            
        {  unsigned long num1, num2, num3, num4;
            num1 = (x & AF); // and Operations
            num2 = (x & BF)>> 3; // and operations and right shift to one
            num3 = (x & CF); // and operations
            num4 = (x & DF)<< 3; // left three shift
            x = num3 | num1 | num4 | num2 ; // OR function for swaping
            cout << flush; // flush
            newVector[i] = (char) x ; // copy into vector of char
        }
    }
    ofstream outfile(OUTF); // output file stream open to add into vectors
    if (outfile.is_open()) // checking the output file is open
    {
        cout <<"Encrypted code as follows:-" <<endl;
        for (int i = 0; i < newVector.size(); i++)
        {
            outfile.put(newVector[i]);// into the output file
            cout << flush; // flush
            cout << newVector[i];//print to vector
        }
    }
    cout << endl <<endl;
    cout << flush ;
    return 0;
}

