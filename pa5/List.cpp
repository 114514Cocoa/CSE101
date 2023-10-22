/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#5
*List.cpp
****************************************************************************/
#include<iostream>
#include<string>
#include<sstream>
#include"List.h"

using namespace std;

//constructors
List::Node::Node(ListElement x){
    data = x;
    prev = nullptr;
    next = nullptr;
}

//create a list
List::List(){
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0; //the pos cursor in the list
    num_elements = 0; //the number of list
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

List::List(const List& L){
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
    num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }
    moveFront();
    while(this->pos_cursor != L.pos_cursor){
        this->moveNext();
    }
}

//Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const{
    return this->num_elements; //return the length of list
}

ListElement List::front() const{
    //error report
    if(length() < 0){
        throw std::length_error("There was a error in front()");
    }

    return this->frontDummy->next->data; //return the front element
}

ListElement List::back() const{
    //error report
    if(length() < 0){
        throw std::length_error("There was a error in back()");
    }

    return this->backDummy->prev->data; //return the back element
}

int List::position() const{
    //error report
    if(length() < 0){
        throw std::length_error("There was a error in position()");
    }

    return this->pos_cursor; //return the position of the cursor
}

ListElement List::peekNext() const{
    //error report
    if(length() <= position()){
        throw std::length_error("There was a error in peekNext()");
    }
    return this->afterCursor->data; //return the element after cursor
}

ListElement List::peekPrev() const{
    //error report
    if(position() <= 0){
        throw std::length_error("There was a error in peekPrev()");
    }
    return this->beforeCursor->data; //return the element before cursor
}

void List::clear(){ //clear the list
    Node* N = frontDummy->next;
    while(N != backDummy){
        Node* A = N->next;
        delete N;
        N = A;
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront(){
    //use while loop to itelatry the list
    while(position() != 0){
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        this->pos_cursor--; //decrease the position
    }
}

void List::moveBack(){
    //use while loop to itelatry the list
    while(position() != length()){
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        this->pos_cursor++;
    }
}

ListElement List::moveNext(){
    //error report
    if(position() >= length()){
        throw std::length_error("There was a error in moveNext()");
    }
    this->pos_cursor ++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;

    return beforeCursor->data;
}

ListElement List::movePrev(){
    //error report
    if(position() <= 0){
        throw std::length_error("There was a error in movePrev()");
    }
        
    this->pos_cursor --;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;

    return afterCursor->data;
}

void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    if (length() == 0){ //if the list is empty
        frontDummy->next = N; //connect each other of n
        backDummy->prev = N;
        N->prev = frontDummy;
        N->next = backDummy;
        afterCursor = N;
        beforeCursor = frontDummy;
    }
    else{ 
        afterCursor->prev = N;
        beforeCursor->next = N;
        N->next = afterCursor;
        N->prev = beforeCursor;
        afterCursor = N;
    }
    num_elements++; //increase the length 
}
void List::insertBefore(ListElement x){
    Node* N = new Node(x); //create a new node
    if (length() == 0){ //if the list is empty
        frontDummy->next = N; //connect each other of n
        backDummy->prev = N;
        N->prev = frontDummy;
        N->next = backDummy;
        beforeCursor = N;
        afterCursor = backDummy;
    }
    else{
        afterCursor->prev = N;
        beforeCursor->next = N;
        N->next = afterCursor;
        N->prev = beforeCursor;
        beforeCursor = N;
    }

    num_elements ++; //increase the length
    pos_cursor ++; //increase the position cursor
}

void List::setAfter(ListElement x){
    //error report
    if(position() >= length()){
        throw std::length_error("There was a error in setAfter()");
    }
    afterCursor->data = x; //set the element after the cursor with x
}

void List::setBefore(ListElement x){
    //error report
    if(position() <= 0){
        throw std::length_error("There was a error in setBefore()");
    }
    beforeCursor->data = x; //set the element before the cursor with x
}

void List::eraseAfter(){
    //error report
    if(position() >= length()){
        throw std::length_error("There was a error in eraseAfter()");
    }

    Node* N = afterCursor;
    Node* A = N->next;
    beforeCursor->next = A;
    A->prev = beforeCursor;
    delete N; //delete the node
    afterCursor = A;
    num_elements--; //decrease the length
}

void List::eraseBefore(){
    //error report
    if(position() <= 0){
        throw std::length_error("There was a error in eraseBefore()");
    }
    
    Node* N = beforeCursor;
    Node* A = N->prev;
    //cout<<"x"<<endl;
    afterCursor->prev = A;
    A->next = afterCursor;
    beforeCursor = A;
    delete N; //delete the node
    num_elements--; //decrese the length
    pos_cursor--; //decrease the posion cursor
}

int List::findNext(ListElement x){
    int a = position();
    int b = length();
    while(a < b){
        if(afterCursor->data == x){
            moveNext();
            return position();
        }
        moveNext();
        a++;
    }
    return -1; //return -1
}

int List::findPrev(ListElement x){
    int a = position();
    int b = 0;

    while(a >= b){
        if(beforeCursor->data == x){
            movePrev();
            return position();
        }
        if( a!= 0){
            movePrev();
        }
        a--;
    }
    return -1; //return -1
}

void List::cleanup(){
    Node* N; //create a node 
    int i = 0;
    int c = 0;
    for(N = frontDummy->next; N != backDummy; N = N->next){
        if(N == afterCursor){
            i = 1;
        }
        int a = N->data; //store the data
        Node* B = N->next; //make a node to store the next data of n
        c = 0;

        while(B != backDummy){
            int d = B->data;
            if( a == d){
                Node* e = B->next; //create a new node for the next

                if(B->next != nullptr){
                    B->next->prev = B->prev;
                }
                if(B->prev != nullptr){
                    B->prev->next = B->next;
                }
                if(i == 0 && c == 0){
                    pos_cursor--; //decrease the position 
                }
                if(B == beforeCursor){
                    beforeCursor = beforeCursor->prev;
                }
                if(B == afterCursor){
                    afterCursor = afterCursor->next;
                }
                num_elements--;//decrease the length
                delete(B); //delete the list
                B = e;
                if(B == afterCursor){
                    c = 1;
                }
            }
            else{
                B = B ->next;
                if(B == afterCursor){
                    c = 1;
                }
            }
        }
    }

}

List List::concat(const List& L) const{
    List C; //make a empty list
    Node* N = frontDummy->next;

    while(N != backDummy){
        C.insertBefore(N->data);//insert the element to the list
        N = N->next;
    }

    Node* A = L.frontDummy->next;
    while(A != L.backDummy){
        C.insertBefore(A->data);
        A = A->next;
    }
    C.moveFront();
    return C;
}

std::string List::to_string() const{
    string s = "(";
    List::Node* N = frontDummy->next;
    while(N != backDummy){
        if(N->next == backDummy){
            s += std::to_string(N->data); //string the data
        }
        else{
            s += std::to_string(N->data) + ", ";
        }
        N = N->next;
    }
    s += ")"; 
    return s; //return the string representation of the element
}

bool List:: equals(const List& R) const{
    Node* a = frontDummy -> next; //set the node for list
    Node* b = R.frontDummy->next; //set the node for list R

    if(length() != R.length()){ //if the length not equal
        return false;
    }

    for(int i = 0; i< length(); i++){
        //store the data
        int ad = a->data;
        int bd = b->data;

        if(ad != bd){ //if the element not equal
            return false;
        }

        a = a->next;
        b = b->next;
    }
    return true;
}

std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

List& List::operator=( const List& L ){
    if (this != &L) {
        //make a copy of L
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}
