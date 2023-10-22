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

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
}


void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}


void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}


void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}


Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R) {
        int compare = k.compare(R->key);
        if (compare == 0) {
            return R;
        } else if (compare < 0) {
            return search(R->left, k);
        } else {
            return search(R->right, k);
        }
    }
    return nil;
}


Dictionary::Node* Dictionary::findMin(Node* R) {
    Node *yiqi = R;
    while (yiqi->left != nil) {
        yiqi = yiqi->left;
    }
    return yiqi;
}


Dictionary::Node* Dictionary::findMax(Node* R) {
    Node *yiqi = R;
    while (yiqi->right != nil) {
        yiqi = yiqi->right;
    }
    return yiqi;
}


Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {            
        return findMin(N->right);
    }
    Node *y = N->parent;                   
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}


Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {            
        return findMax(N->left);
    }
    Node *y = N->parent;                   
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

/*** Helper Functions - RBT ***/
void Dictionary::LeftRotate(Node* N) {
    // set y
    Node *y = N->right;
   
    N->right = y->left;
    if (y->left != nil) { 
        y->left->parent = N;
    }
    y->parent = N->parent; 
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }
    y->left = N; 
    N->parent = y;
    return;
}


void Dictionary::RightRotate(Node* N) {
    Node *y = N->left;     
    N->left = y->right; 
    if (y->right != nil) {
        y->right->parent = N;
    }

    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
    return;
}


void Dictionary::RB_InsertFixUp(Node* N) {
    while(N->parent->color == RED){
        Node* y = nil;
        if(N->parent == N->parent->parent->left){
            y = N->parent->parent->right;
            if (y->color == RED) {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }else{
            y = N->parent->parent->left;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else{
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


void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else { 
        u->parent->right = v;
    }
    v->parent = u->parent;
    return;
}


void Dictionary::RB_DeleteFixUp(Node* N) {
    Node *w;
    while ((N != root) && (N->color == BLACK)) {
        if (N == N->parent->left) {
            w = N->parent->right;
            if (w->color == RED) {
                w->color = BLACK;                        // case 1
                N->parent->color = RED;                   // case 1
                LeftRotate(N->parent);                // case 1
                w = N->parent->right;                     // case 1
            }
            if (w->left->color == BLACK and w->right->color == BLACK) {
                w->color = RED;                          // case 2
                N = N->parent;                           // case 2
            } else { 
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;                // case 3
                    w->color = RED;                       // case 3
                    RightRotate(w);                   // case 3
                    w = N->parent->right;                  // case 3
                }
                w->color = N->parent->color;               // case 4
                N->parent->color = BLACK;                 // case 4
                w->right->color = BLACK;                  // case 4
                LeftRotate(N->parent);                // case 4
                N = root;                             // case 4
            }
        } else {
            w = N->parent->left;
            if (w->color == RED) {
                w->color = BLACK;                        // case 5
                N->parent->color = RED;                   // case 5
                RightRotate(N->parent);               // case 5
                w = N->parent->left;                      // case 5
            }
            if (w->right->color == BLACK and w->left->color == BLACK) {
                w->color = RED;                          // case 6
                N = N->parent;                           // case 6
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;               // case 7
                    w->color = RED;                       // case 7
                    LeftRotate(w);                    // case 7
                    w = N->parent->left;                   // case 7
                }
                w->color = N->parent->color;               // case 8
                N->parent->color = BLACK;                 // case 8
                w->left->color = BLACK;                   // case 8
                RightRotate(N->parent);               // case 8
                N = root;                             // case 8
            }
        }
    }
    N->color = BLACK;
    return;
}


void Dictionary::RB_Delete(Node* N) {
    Node *y = N;
    Node *x;
    int y_original_color = y->color;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else { 
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == BLACK) {
        RB_DeleteFixUp(x);
    }
    delete N;
    return;
}


Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}


Dictionary::Dictionary() {
    nil = new Node("\000",-1);
    nil->color = BLACK;
    nil->parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
}


Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("\000",-1);
    nil->color = BLACK;
    nil->parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
    return;
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    num_pairs = 0;
    root = current = nullptr;
    delete nil;
    return;
}


int Dictionary::size() const {
    return num_pairs;
}


bool Dictionary::contains(keyType k) const {
    if (search(root, k) != nil) {
        return true;
    } else {
        return false;
    }
}


valType& Dictionary::getValue(keyType k) const {
    Node *N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): Value not in Dictionary.\n");
    } else {
        return N->val;
    }
}


bool Dictionary::hasCurrent() const {
    if (current != nil) {
        return true;
    } else {
        return false;
    }
}


keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): Key not in Dictionary.\n");
    } else {
        return current->key;
    }
}


valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): Value not in Dictionary.\n");
    } else {
        return current->val;
    }
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    root = current = nil;
    num_pairs = 0;
}


void Dictionary::setValue(keyType k, valType v) {
    Node *P = nil; //set p to nil
    Node *R = root; //set r to root
    while (R != nil) {
        P = R; //set P to R                                                                                 
        if (k < R->key) {
            R = R->left; //shift R to left
        } 
        else if (k > R->key) {
            R = R->right; //shift R to right
        } 
        else {
            break;
        }   
    }   
    Node *N = new Node(k, v);  //make a new node for k and v
    N->parent = P;
    if (P == nil) {
        root = N; //set root to N
    } 
    else if (k < P->key) { //if k is smaller than key
        P->left = N;
    } 
    else if (k > P->key) { //if k is bigger than key
        P->right = N;
    } 
    else {
        P->val = v;
        delete N; //delete node
        return;
    }   
    N->left = nil;
    N->right = nil;
    N->color = RED;
    RB_InsertFixUp(N); //insert fix up
    num_pairs++; //increase the num of pair
    return;
}


void Dictionary::remove(keyType k) {
    Node *N = search(root, k);
    if(N == nil) {
        throw std::logic_error("Dictionary: remove(): Key not in Dictionary.\n");
    }
    if(current == N) {
        current = nil;
    }
    RB_Delete(N); //call the helper function delete
    num_pairs --;
}

 
void Dictionary::begin() {
    if (size() > 0) {
        current = findMin(root);
    }
}


void Dictionary::end() {
    if (size() > 0) {
        current = findMax(root);
    }
}


void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): Value not in Dictionary.\n");
    } else {
        current = findNext(current);
    }
}


void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): Value not in Dictionary.\n");
    } else {
        current = findPrev(current);
    }
}



std::string Dictionary::to_string() const {
    std::string s = ""; //create a string s
    inOrderString(s, root);
    return s;
}


std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}



bool Dictionary::equals(const Dictionary& D) const {
    return to_string() == D.to_string();
}



std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.to_string();
}


bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}


Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if(this != &D){ 
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
     }
     return *this;
}
