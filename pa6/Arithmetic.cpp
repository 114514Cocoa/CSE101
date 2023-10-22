/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#6
*Arithmetic.cpp
****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(int argc, char *argv[]){
    //check command line for correct number of arguments
    if(argc != 3){
        throw std::invalid_argument("Usage:wrong,please enter the correct file!");
        return(EXIT_FAILURE);
    }
    
    ifstream in;
    ofstream out;

    //open files for reading and writing 
    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    
    //get the data from input file
    string a;
    getline(in,a);
    BigInteger A(a);
    getline(in,a);
    getline(in,a);
    BigInteger B(a);

    in.close();//close the input file

    //output the answer
    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << A - A << endl << endl;
    out << A.mult(BigInteger("3")) - B.mult(BigInteger("2")) << endl << endl;
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << (A * A * A * A).mult(BigInteger("9")) + (B * B * B * B * B).mult(BigInteger("16")) << endl << endl;

    out.close();//close the output filt

    return(EXIT_SUCCESS);

}   