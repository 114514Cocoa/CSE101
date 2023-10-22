/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#5
*Shuffle.cpp
****************************************************************************/
#include "List.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

//use this funciton shuffle the deck
void shuffle(List& D){
    int l = D.length(); //the length of whole list
    int h = D.length()/2; //the length of half of the list
    List a; //make two list to store of half of the list
    List b;
    int num, nums,x,y;
    //cout << "D = " << D << endl;
    while(D.position() < h){
        num = D.moveNext(); //get the numbers
        a.insertBefore(num); //insert the numbers to the list
    }
    //cout <<"A is "<< a << endl;
    while(D.position() <l){
        nums = D.moveNext(); //get the last numbers
        b.insertBefore(nums); //insert the last numbers to the list
    }
    //cout <<"B is "<< b << endl;


    a.moveFront();
    b.moveFront();
    D.clear(); //clear the list

    while(b.position()<b.length()){
        x = b.moveNext();
        D.insertBefore(x);
        if(a.position() < a.length()){
            y = a.moveNext();
            D.insertBefore(y);
        }
    }
    //cout << D <<endl;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        throw std::invalid_argument("Usage:wrong,please enter the number!");
        return(EXIT_FAILURE);
    }
    int x = atoi(argv[1]);
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    List L;
    for(int i = 1; i <= x; i++){
        int j = 0;
        L.insertBefore(i); //inesrt the data to list
        //cout << j << endl;
        List A(L); //make a copy of L
        // L.moveFront();
        //shuffle(L);

        do{
            L.moveFront();
            shuffle(L); //shuffle the list
            j++;
        }while(!(A==L));

        cout << i << "\t\t" << j << endl;
    }   


    return(EXIT_SUCCESS);

}