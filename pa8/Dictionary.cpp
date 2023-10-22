/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#8
*Dictionary.cpp
****************************************************************************/
#include <iostream>
#include <string>
#include "Dictionary.h"

#define BLACK -1
#define RED 1

using namespace std;

Dictionary::Node::Node(keyType k, valType v){
    key = k; //set key to k
    val = v; //set val to v
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED; //set the color to red
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R == nil){
        return;
    }
    inOrderString(s,R->left); //recursively
    s += R->key + " : " + std::to_string(R->val) + "\n"; //append the node
    inOrderString(s,R->right); //recursively
} 

void Dictionary :: preOrderString(std::string& s, Node* R) const{
    if(R == nil){
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
    if(R != nil){
        postOrderDelete(R->left); //recursively
        postOrderDelete(R->right); //recursively
        delete R; //delete R
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    while(R != nil){ //iterate as long as R is not nil
        if(root == nil || k == R->key){
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
    if(min != nil){
        while(min->left != nil){ //loop as long as it is not nil
            min = min->left;
        }
        return min;
    }
    return nil;
}   

Dictionary :: Node* Dictionary::findMax(Node* R){
    Node* max = R;
    if(max != nil){
        while (max->right != nil){
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
    while(y != nil && N == y->right){
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
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}


void Dictionary::LeftRotate(Node* N){
    Node* y = N->right; //set y to the right of node N
    N->right = y->left; //turn y's right subtree into x's right subtree
    if (y->left != nil){
        y->left->parent = N;
    }

    y->parent = N->parent; //link y's parent to x
    if(N->parent == nil){
        root = y;
    }
    else if(N == N->parent->left){
        N->parent->left = y;
    }
    else{
        N->parent->right = y;
    }
    //put N on y's left
    y->left = N;
    N->parent = y;
}


void Dictionary::RightRotate(Node* N){
    Node* y = N->left; //set y to the left of node N
    N->left = y->right; //turn y's left subtree into x's right subtree
    if (y->right != nil){
        y->right->parent = N;
    }

    y->parent = N->parent; //link y's parent to x
    if(N->parent == nil){
        root = y;
    }
    else if(N == N->parent->right){
        N->parent->right = y;
    }
    else{
        N->parent->left = y;
    }
    //put N on y's left
    y->right = N;
    N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N){
    while(N->parent->color == RED){
        Node* y = nil;
        if(N->parent == N->parent->parent->left){
            y = N->parent->parent->right;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else{
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else{
            y = N->parent->parent->left;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else{
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N){
    while(N != root && N->color == BLACK){
        if(N == N->parent->left){
            Node* w = N->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                w->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if(w->left->color == BLACK && w->right->color ==BLACK){
                w->color = RED;
                N = N->parent;
            }
            else{
                if(w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else{
            Node* w = N->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                N = N->parent;
            }
            else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                else{
                    if(w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = N->parent->left;
                    }
                    w->color = N->parent->color;
                    N->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(N->parent);
                    N = root;
                }
            }
        }
    }
    N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N){
    Node* x = nullptr;
    Node* y = N;
    int yoc = y->color;
    if(N->left == nil){
        x = N->right;
        RB_Transplant(N,N->right);
    }
    else if(N->right == nil){
        x = N->left;
        RB_Transplant(N,N->left);
    }
    else{
        y = findMin(N->right);
        yoc = y->color;
        x = y->right;
        if(y->parent == N){
            x->parent = y;
        }
        else{
            RB_Transplant(y,y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N,y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    delete(N);
    if(yoc == BLACK){
        RB_DeleteFixUp(x);
    }
   
}

//create the new dictionary 
Dictionary::Dictionary(){
    nil = new Node("NULL",999);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    nil->color = BLACK;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("NULL",999);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    nil->color = BLACK;
    num_pairs = 0;
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
    if(N == nil){
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
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
    Node *P = nil; //set p to nil
    Node *R = root; //set r to root
    
    while(R != nil){
        P = R; //set P to R
        if(k < R->key){
            R = R->left; //shift R to left
        }
        else if(k > R->key){
            R = R->right; //shift R to right
        }
        else{
            break;
        }
    }
    Node *N = new Node(k,v); //make a new node for k and v
    N->parent = P;
    if(P == nil){
        root = N; //set root to N
    }
    else if(k < P->key){ //if k is smaller than key of p
        P->left = N;
    }
    else if(k > P->key){
        P->right = N;
    }
    else{
        P->val = v;
        delete N; //delete the node
        return;
    }
    N->left = nil;
    N->right = nil;
    N->color = RED;
    RB_InsertFixUp(N);//call the helper function
    num_pairs++; //increase the num of pair
    return;
}

void Dictionary::transplant(Node *u, Node *v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right =v;
    }
    if(v != nil){
        v->parent = u->parent;
    }
}

void Dictionary::remove(keyType k){
    Node* N = search(root,k);
    if( N == nil){
        throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
    }
    if(current == N){
        current = nil;
    }
    RB_Delete(N); //call the helper function delete 
    num_pairs--; //decrease the size
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
