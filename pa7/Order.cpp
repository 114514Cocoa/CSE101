/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#7
*Order.cpp
****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Dictionary.h"

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

    string a; //make a line
    Dictionary b;//make a dictionary

    for(int i = 1; getline(in, a); i++){
        b.setValue(a,i); //set the value for the dictionary
    }

    out<<b.to_string()<<endl; //output the to_string to file
    out<<b.pre_string()<<endl; //output thr pre_string to file

    //close the file
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}