/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#7
*Dictionary.cpp
****************************************************************************/
#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

Dictionary::Node::Node(keyType k, valType v){
    key = k; //set key to k
    val = v; //set val to v
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R == nullptr){
        return;
    }
    inOrderString(s,R->left); //recursively
    s += R->key + " : " + std::to_string(R->val) + "\n"; //append the node
    inOrderString(s,R->right); //recursively
} 

void Dictionary :: preOrderString(std::string& s, Node* R) const{
    if(R == nullptr){
        return;
    }
    s += R->key + "\n"; //append the node to key
    preOrderString(s,R->left); //recursively
    preOrderString(s,R->right);//recursively
}

void Dictionary :: preOrderCopy(Node* R, Node* N){
    if(R != N){
        setValue(R->key, R->val); //set the value of R to its key
        preOrderCopy(R->left, N); //recursively
        preOrderCopy(R->right,N); //recursively
    }
}

void Dictionary :: postOrderDelete(Node* R){
    if(R != nullptr){
        postOrderDelete(R->left); //recursively
        postOrderDelete(R->right); //recursively
        delete R; //delete R
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    while(R != nullptr){ //iterate as long as R is not nil
        if(root == nullptr || k == R->key){
            return R;
        }
        else if(k < R -> key){ //if k is smaller than Node R's key
            R = R->left;
        }
        else{
            R = R->right;
        }
    }
    return nil;
}

Dictionary :: Node* Dictionary::findMin(Node* R){
    Node* min = R; //set node min to R
    if(min != nullptr){
        while(min->left != nullptr){ //loop as long as it is not nil
            min = min->left;
        }
    }
    return min;
}   

Dictionary :: Node* Dictionary::findMax(Node* R){
    Node* max = R;
    if(max != nullptr){
        while (max->right != nullptr){
            max = max -> right;
        }
    }
    return max;
}

Dictionary :: Node* Dictionary::findNext(Node* N){
    if(N == nullptr || N == nil){
        return nil;
    }
    else if(N-> right != nil){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while(y != nullptr && N == y->right){
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary :: Node* Dictionary::findPrev(Node* N){
    if(N == nullptr || N == nil){
        return nil;
    }
    else if(N-> left != nil){
        return findMax(N->left);
    }
    Node* y = N->parent;
    while(y != nullptr && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}

//create the new dictionary 
Dictionary::Dictionary(){
    //nil = new Node("NIL",999);
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    //nil = new Node("NIL",999);
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}

int Dictionary::size() const{
    return num_pairs;
}

bool Dictionary::contains(keyType k)const{
    Node* N = search(root,k);
    if(N == nullptr){
        return false;
    }
    return N;
}

valType& Dictionary::getValue(keyType k)const{
    Node* N = search(root,k);
    if(N == nil){
       throw std::logic_error("Dictionary: getValue(): key \""+k+"\"does not exist"); 
    }
    return N->val;
}

bool Dictionary::hasCurrent()const{
    if(current != nil){ //if current not equal nil
        return current;
    }
    else{
        return false;
    }
}

keyType Dictionary::currentKey()const{
    if(!hasCurrent()){
        throw::std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal()const{
    if(!hasCurrent()){
        throw::std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

void Dictionary::clear(){
    postOrderDelete(root);
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
    Node *P = nullptr; //set p to nil
    Node *R = root; //set r to root
    if(root == nullptr){
        root = new Node(k,v); //make a new node
        num_pairs = 1;
        return;
    }
    while(R != nullptr && R->key != k){
        P = R; //set P to R
        if(k < R->key){
            R = R->left; //shift R to left
        }
        else{
            R = R->right; //shift R to right
        }
    }
    if(R != nullptr){
        R->val = v; //set value of R to v
    }
    else{
        Node* N = new Node(k,v); //create a new node for k and v
        N->parent = P;
        if(P == nullptr){
            root = N;
        }
        else{
            if(k < P->key){ //if k is smaller than key of p
                P->left = N;
            }
            else{
                P->right = N;
            }
        }
        num_pairs++; //increase the szie
    }
}

void Dictionary::transplant(Node *u, Node *v){
    if(u->parent == nullptr){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right =v;
    }
    if(v != nullptr){
        v->parent = u->parent;
    }
}

void Dictionary::remove(keyType k){
    Node* N = search(root,k);
    if( N == nullptr){
        throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
    }
    if(N == current){
        current = nil;
    }
    if(N->left == nullptr){
        transplant(N,N->right);
    }
    else if(N->right == nullptr){
        transplant(N,N->left);
    }
    else{
        Node* y = findMin(N->right);
        if(y ->parent != N){
            transplant(y,y->right); //call the transplant function
            y->right = N->right;
            y->right->parent = y;
        }
        transplant(N,y); //transplant the N and y node
        y->left = N->left;
        y->left->parent = y;
    }
    num_pairs --;
}

void Dictionary::begin(){
    if(size()>0){
        current = findMin(root);
    }
}

void Dictionary::end(){
    if(size()>0){
        current = findMax(root);
    }
}

void Dictionary::next(){
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: next() : current not defined");
    }
    else{
        current = findNext(current);
    }
}

void Dictionary::prev(){
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: prev() : current not defined");
    }
    else{
        current = findPrev(current);
    }
}

std::string Dictionary::to_string() const{
    std::string s = ""; //create a string s
    inOrderString(s,root);
    return s;
}

std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s,root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const{
    return to_string() == D.to_string();
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D){
    return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B){
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this != &D){
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root,temp.root);
        std::swap(current,temp.current);
        std::swap(num_pairs,temp.num_pairs);
    }
    return *this;
}
