/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#8
*WordFrequency.cpp
****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <functional> 
#include <algorithm>  
#include "Dictionary.h"

#define MAX_LEN 300

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
    string line;
    string word;
    //make a dictionary
    Dictionary D;
    size_t begin, end, len;
  	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";


    while(getline(in, line)){
        //get the length of line
        len = line.length();
        //get word for each line
        begin = min(line.find_first_not_of(delim, 0),len);
        end = min(line.find_first_of(delim,begin),len);
        word = line.substr(begin, end-begin);

        while(word!= ""){ //we have a word
            //use the transfrom to get the lowercase word
            	transform(word.begin(),word.end(),word.begin(), ::tolower);

            //increment word count if its already there, else add it to dictionary
        if(D.contains(word)){
        	D.getValue(word) += 1;
        }else{
        	D.setValue(word,1);    
       	}
        //get next word
        begin = min(line.find_first_not_of(delim, end+1),len);
        end = min(line.find_first_of(delim,begin),len);
        word = line.substr(begin, end-begin);
    	}
    }
    out << D << endl;//print the dictionary
    //close files
    in.close();
    out.close();
    return(EXIT_SUCCESS);
}
