/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#7
*DictionaryTest.cpp
****************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

    string s;
    int x;
    string S[] =   {"pen","pencil","book","ruler","caster","bag"}; //make a word list

    //make the two dictionary
    Dictionary A;
    Dictionary B;

    cout << endl;

    for(int i=0; i<6; i++){
        A.setValue(S[i], i+1); //insert the word to dictionary
    }
    
    // call operator=()
    B = A;

    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << "B.size() = " << B.size() << endl  << B << endl;

    B.setValue("pen", 11);
    B.setValue("ruler", 20);


    // call copy constructor
    Dictionary C = B;

    cout << "B.size() = " << B.size() << endl  << B << endl;
    cout << "C.size() = " << C.size() << endl  << C << endl;

    // check operator==()
    cout << "A==B is " << (A==B?"true":"false") << endl;
    cout << "B==C is " << (B==C?"true":"false") << endl;
    cout << "C==A is " << (C==A?"true":"false") << endl << endl;

    // perform alterations on A
    cout << A.getValue("pencil") << endl;
    A.getValue("pencil") *= 10; // change the value associated with "hemiolia"
    cout << A.getValue("pencil") << endl << endl;

    // check state of A
    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << A.pre_string() << endl;

    A.remove("pen");
    A.remove("pencil");
    // check state of A
    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << A.pre_string() << endl;

    // do forward iteration on A
    for(A.begin(); A.hasCurrent(); A.next()){
        s = A.currentKey();
        x = A.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl << endl;

    // do reverse iteration on B
    for(B.end(); B.hasCurrent(); B.prev()){
        s = B.currentKey();
        x = B.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl << endl;
    
    // check exceptions
    try{
        A.getValue("blah");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.remove("blah");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentKey();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentVal();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }  
    try{
        A.next();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.prev();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    cout << endl;  

    return( EXIT_SUCCESS );
}