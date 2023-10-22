/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#6
*BigInteger.cpp
****************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "List.h"
#include "BigInteger.h"

using namespace std;

//base constants
const ListElement base = 1000000000; //10^9
const int power = 9;

void negateList(List& L){
    L.moveFront();
    //iterate through the list of L
    for(int i = 0; i < L.length(); i++){
        ListElement x = L.moveNext();
        //if x is 0 then continue
        if(x == 0){
            continue;
        }
        L.eraseBefore(); //delete the element
        L.insertBefore(x*-1); //insert the negate x to the list
    }
    
}

void sumList(List& S, List A, List B, int sgn){
    ListElement x,y;
    A.moveFront();
    B.moveFront();
    S.clear(); //clear the list s
    //iterate through the two lists
    while(A.position() < A.length() && B.position() < B.length()){ 
        x = A.peekNext();
        y = B.peekNext();
        S.insertBefore(x + y*sgn); //insert the result of sum
        A.moveNext();
        B.moveNext();
    }
    //iterate through the list A
    while(A.position() < A.length()){
        x = A.peekNext();
        S.insertBefore(x);
        A.moveNext();
    }
    //iterate through the list B
    while(B.position() < B.length()){
        y = B.peekNext();
        S.insertBefore(y*sgn);
        B.moveNext();
    }

}

int noramlizeList(List& L){
    int sgn;
    ListElement q,r,u;
    ListElement carryIn, curCol, carryOut = 0;

    L.moveFront();
    while(L.position() < L.length()){
        carryIn = carryOut;
        curCol = L.moveNext();
        curCol += carryIn;
        q = curCol/base; //quotient
        r = curCol%base; //remainder
        if(r < 0){
            u = 1;
        }
        else{
            r = 0;
        }
        curCol = r + (u * base);
        carryOut = (q - r);
        L.eraseBefore(); //erase the last element
        L.insertAfter(curCol);

        if(L.position() == L.length()){
            if(carryOut > 0){
                L.insertAfter(0); //insert a 0 after the cursor
            }
            else if(carryOut < 0){
                L.insertAfter(carryOut); //insert the carryOut after the cursor
            }
        }
    }
    L.moveFront();
    while(L.position() < L.length()){
        if(L.peekNext() == 0){
            L.eraseAfter();
        }
    }
    if(L.length() > 0){
        L.moveBack(); //move bake of the list
        if(L.front() > 0){
            sgn = 1; //set the sign to positive
        }
        else if(L.front() < 0){
            sgn = -1; //set the sign to negative
            negateList(L); //change sign of all digits
            noramlizeList(L); 
        }
        else{
            sgn = 0; //set the sgn to zero
        }
    }
    return sgn;
}

void shiftList(List& L, int p){
    L.moveFront(); //move to the front of L
    for(int i = 0; i< L.length(); i++){
        L.insertAfter(0); //insert 0's after the cursor on L
    }
}

void scalarMultList(List& L, ListElement m){
    if(m != 1){
        L.moveFront();
        while(L.position() < L.length()){
            ListElement x = L.moveNext();
            if(x == 0){
                continue;
            }
            L.clear(); //clear the element
            L.insertBefore(x*m); //insert the x8M
        }
    }
}

BigInteger::BigInteger(){
    signum = 0; //set the signum to 0
    digits = List(); //create the list
}

BigInteger::BigInteger(std::string s){
    ListElement x; //make the list
    int n = s.length(); //get the length of the string
    int p = power,r,i;
    if(n == 0){
        throw std::invalid_argument("length is zero in biginterger");
    }
    if(s[0] == '-'){
        signum = -1;
        digits.clear();
        n--; //decreament
    }
    if(s[0] == '+'){
        signum = -1;
        digits.clear();
        n--; //decreament
    }
    else{
        signum = 1; //set sign to 1 anyway
    }

    if(s.length() > 1 && s[0] == 0){
        digits.clear();
        n--;
    }
    else{
        signum = 0; //set sign to 0
    }

    if(s.length() == 0 || s.find_first_not_of("0123456789")!= std::string::npos){
        throw::std::runtime_error("non - numeric characters error");
    }
    digits.clear(); //make a empty digits list
    if(s[0] != '0'){
        r = s.length()%p; //set "r" to the modulo of the length of "s" by power
        for(i = s.length()-p; i>=0; i-=p){
            x = std::stoi(s.substr(i,p));
            digits.insertBefore(x); //insert x in to the list
        }
        if(r > 0){
            x = std::stoi(s.substr(0,r));
            digits.insertBefore(x); //insert x into the digits list
        }
    }
}

BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum; //set the signum to N's signum
    digits = N.digits; //set the digits to N's digits
}

int BigInteger::sign() const{
    return signum; //return the signum
}

int BigInteger::compare(const BigInteger& N) const{
    int ret = 0; //set the ret for -1, 0 ,1
    List L = this->digits; //make the list for digits
    List R = N.digits; //make the list for N's digits
    
    if(signum > N.signum){
        ret = 1;
    }
    if(signum < N.signum){
        ret = -1;
    }
    if(L.length() > R.length()){
        ret = 1;
    }
    if(L.length() < R.length()){
        ret = -1;
    }
    if(L.length() > R.length()){
        ret = 1;
    }
    //compare the element for the two list
    L.moveFront();
    R.moveFront();
    for(int i = 0; i<L.length(); i++){
        int a = L.moveNext();
        int b = R.moveNext();
        if(a > b){
            ret = 1;
        }
        if(a < b){
            ret = -1;
        }
    }
    return ret;
}

void BigInteger::makeZero(){
    signum = 0; //make the signum to zero
    digits.clear(); //clear the digits
}

void BigInteger::negate(){
    signum *= -1; //make the signum to -1
}

BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger Sum;
    int sgn;
    List A = this->digits;
    List B = N.digits;
    List& s = Sum.digits;

    if(A->signum == B->signum){
        sumList(s,A,B,1);
        noramlizeList(s);
        sign(sum) = sign(A);
    }
    else{
        sumList(s,A,B,-1);
        noramlizeList(s);
    
    }
    return Sum;


}

BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger A = BigInteger(N);
    List L = A.digits;
    negateList(L); //negate "A"
    A.digits = L;
    return this->add(A); //call and return the add function on A
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    int col = 0; //column number
    BigInteger Prod;
    List A = this->digits;
    List B = N.digits;
    List C;

    List& P = Prod.digits;
    B.moveFront();
    while(B.position() < B.length()){
        C = A; //set C to A
        ListElement x = B.peekNext(); //get the data of the next element of B
        scalarMultList(C,x);
        shiftList(C,col);
        noramlizeList(P);
        col++; //increment the column number
    }

    return Prod;

}

std::string BigInteger::to_string(){
    ListElement x;
    std::string s;

    //if sign is -1
    if(signum == -1){
        s += "-";
    }
    //if sign is 0
    if(signum == 0){
        s += "0";
        return s;
    }
    else{
        digits.moveBack(); //digits move to the back
        x = digits.movePrev(); //set x to the previous value
    
        while(digits.position() < digits.length()){
            x = digits.movePrev();
            std::ostringstream ss;
            ss << std::setw(power) << std::setfill('0') <<x;
            s += ss.str();//cast "ss" to string and append it to s 
        }
    }
    return s;
}

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
   return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1){
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A < B || A == B){
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1){
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A > B || A == B){
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
   return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator()
// Returns the product AB. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator=()
// Overwrites A with the product AB. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}