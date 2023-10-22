/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#4
*Matrix.c
****************************************************************************/
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{ 
    int column; //use int type for the index
    double value; //use double type for the value
}EntryObj;

//private MatrixObj type
typedef struct MatrixObj{
    List* row; //a list of row can store the value
    int size; //the size of the matrix
}MatrixObj;

//return a new matrix
Matrix newMatrix(int n){
    Matrix M = (MatrixObj *)malloc(1 * sizeof(MatrixObj));//used malloc to set the memory of matrix
    M -> size = n; //the size of matrix
    M -> row = malloc(sizeof(List)*n); //allocate memory fot the row
    int i;
    for(i = 0; i <= n; i++){
        M->row[i] = newList(); //make a new list for the matrix
    }
    return M; // return the matrix
}

Entry newEntry(int a, double b){
    if(a < 0){
        printf("Columen is zero in newEntry\n");
        exit(EXIT_FAILURE);
    }
    Entry E = malloc(sizeof(EntryObj));//used malloc to set the entry
    E -> column = a;
    E -> value = b;
    return E;
}

void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        free((*pM) -> row); //delete the row
        free(*pM); //delete the pointer
        pM =NULL;
        *pM = NULL;
    }
}

void freeEntry(Entry* pE){
   free(*pE);
   *pE = NULL;
}

int size(Matrix M){
    if(M == NULL){
        printf("There was a error for m is null in size.\n");
        exit(EXIT_FAILURE);
    }
    return M->size; //return the size of the matrix
}

int NNZ(Matrix M){
    if(M == NULL){
        printf("There was a error for m is null in NNZ.\n");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    for(int i = 0; i < M->size; i++){
        List L = M->row[i];
        moveFront(L);
        count += length(L);
    }
    return count; //return the non-zero element of the matrix
}

int getCol(Entry E){
    if(E == NULL){
        printf("There was a error for e is null in col.\n");
        exit(EXIT_FAILURE);
    }
    return E->column;
}

double value(Entry E){
    if(E == NULL){
        printf("There was a error for e is null in value.\n");
        exit(EXIT_FAILURE);
    }
    return E->value;
}

int equals(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("There was a error for A or B is null in equal.\n");
        exit(EXIT_FAILURE);
    }

    if(A -> size != B->size){ //if the size of A is not equal the size of B
        return 0;
    }

    int n = size(A);
    for(int i = 0; i <= n; i++){
        List c = A->row[i]; //create the list to get the row for a
        List d = B->row[i]; //create the list to get the row for b

        if(length(c) == length(d)){
            for(moveFront(c), moveFront(d);index(c)>=0&&index(d)>=0;moveNext(c),moveNext(d)){
                if(getCol(get(c)) == getCol(get(d))){
                    if(value(get(c)) != value(get(d))){
                        return 0;
                    }
                }
            }
        }
        else{
            return 0;
        }


    }
    return 1;

}

void makeZero(Matrix M){
    if(M == NULL){
        printf("There was a error for m is null in makeZero.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < M->size; i++){
        List a = M->row[i];
        for(int j = 0; j < length(a); j++){
            Entry E = get(a); //make the entry
            freeEntry(&E);
            moveNext(a);
        }
    
        freeList(&a); //free the list
        M->row[i] = newList(); //make a new
    }
}

void insertByOrder(List L, Entry E) {
    if (length(L) == 0){
        append(L, E);
        return;
    }
    moveBack(L);
    int j = length(L)-1;
//compare the current element with the previous elements 
    while(j >= 0 && E->column < getCol(get(L))) {
        movePrev(L);
        j--;
    }
//if the current element is the samllest then add it to the front of the List
    if(j < 0){
        prepend(L,E);
    }
//or insert in to the correct position
    else{
        insertAfter(L,E);
    }
}

void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        printf("There was a error for m is null in changeEntry.\n");
        exit(EXIT_FAILURE);
    }
    List a = M->row[i-1];
    moveFront(a);
    for (int i = 0 ; i < length(a); i++){
        if (getCol(get(a)) == j) {
            if (x == 0) {
                Entry E = get(a);

                delete(a);
                freeEntry(&E);
            }
            else{
                Entry E = get(a);

                set(a, newEntry(getCol(get(a)), x));
                freeEntry(&E);
            }
            return;
        } 
        moveNext(a);
    }
    if(x != 0){
        Entry E = newEntry(j ,x);
        insertByOrder(a, E);
    }

}


Matrix copy(Matrix A){
    if(A == NULL){
        printf("There was a error for A is null in copy.\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(A->size); //make a empty copy of A

    for(int i = 0; i <= A->size;i++){
        List L = A->row[i];
        for(moveFront(L); index(L)>= 0; moveNext(L)){
            changeEntry(B, i, getCol(get(L)),value(get(L)));
        }
    }
    return B; //return the copy
}

Matrix transpose(Matrix A){
    if(A == NULL){
        printf("There was a error for A is null in transpose.\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(A->size); //make a empty copy of A

    for(int i = 0; i < A->size; i++){
        List L = A->row[i];
        for(moveFront(L); index(L)>= 0; moveNext(L)){
            changeEntry(B, getCol(get(L)),i,value(get(L))); //change the value
        }
    }
    return B; //return the matrix

}

Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        printf("There was a error for A is null in scalarMult.\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(A->size); //make a empty copy of A
    for(int i = 0; i < A->size; i++){
        List L = A->row[i];
        for(moveFront(L); index(L)>= 0; moveNext(L)){
            double v = x * value(get(L)); //xA
            changeEntry(B,i,getCol(get(L)),v); //change the value
        }
    }
    return B; //return the matrix
}

Matrix sum(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("There was a error for A or B is null in scalarMult.\n");
        exit(EXIT_FAILURE);
    }

    //pre: size(A)==size(B)
    if(A->size != B->size){
        printf("There was a error of a and b size not equal in sum.\n");
        exit(EXIT_FAILURE);
    }
    Matrix s = newMatrix(A->size);
    int z = NNZ(s);
    for(int i = 0; i <= A->size; i++){
        List a = A->row[i]; //create the list
        List b = B->row[i]; //create the list
        for(moveFront(a),moveFront(b);index(a)>=0&&index(b)>=0;moveNext(a),moveNext(b)){
            Entry c = get(a);
            Entry d = get(b);
            if(length(a) == length(b)){
                append(s->row[i], newEntry(c->value + d->value, c->column));
                if(c->value + d->value == 0){ //if the sum of they equal 0
                    deleteBack(s->row[i]);
                    z -= 1;
                }
            }
        }
    }
    return s; //return the sum matrix
}

Matrix diff(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("There was a error for A or B is null in scalarMult.\n");
        exit(EXIT_FAILURE);
    }

    //pre: size(A)==size(B)
    if(A->size != B->size){
        printf("There was a error of a and b size not equal in sum.\n");
        exit(EXIT_FAILURE);
    }
    Matrix s = newMatrix(A->size);
    int z = NNZ(s);
    for(int i = 0; i <= A->size; i++){
        List a = A->row[i]; //create the list
        List b = B->row[i]; //create the list
        for(moveFront(a),moveFront(b);index(a)>=0&&index(b)>=0;moveNext(a),moveNext(b)){
            Entry c = get(a);
            Entry d = get(b);
            if(length(a) == length(b)){
                append(s->row[i], newEntry(c->value - d->value, c->column));
                if(c->value + d->value == 0){ //if the sum of they equal 0
                    deleteBack(s->row[i]);
                    z -= 1;
                }
            }
        }
    }
    return s; //return the diff matrix
}


//the funciton computes the vector dot product of two matrix rows represented by Lists P and Q
double vectorDot(List P, List Q){
    if(P == NULL || Q == NULL){
        printf("There was a error for P or Q is null in vectorDot.\n");
        exit(EXIT_FAILURE);
    }

    //pre: length(P)==length(Q)
    if(length(P) != length(Q)){
        printf("There was a error of P and Q size not equal in vectorDot.\n");
        exit(EXIT_FAILURE);
    }
    double value = 0.0; 
    for(moveFront(P),moveFront(Q);index(P)>=0&&index(Q)>=0;moveNext(P),moveNext(Q)){
        Entry a = get(P);
        Entry b = get(Q);
        value += a->value * b->value; 
    }
    return value; //return the value

}

Matrix product(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("There was a error for A or B is null in scalarMult.\n");
        exit(EXIT_FAILURE);
    }

    //pre: size(A)==size(B)
    if(A->size != B->size){
        printf("There was a error of a and b size not equal in sum.\n");
        exit(EXIT_FAILURE);
    }
    Matrix s = newMatrix(A->size);
    Matrix t = transpose(B);
    for(int i = 1; i<=A->size; i++){
        for(int j = 1; j<=A->size;i++){
            List a = A->row[i];
            List b = t->row[i];
            double v = vectorDot(a,b); //get the value
            append(s->row[i],newEntry(v,j));
        }
    }
    return s; //return the product matrix
}



void printMatrix(FILE* out, Matrix M){
    for(int i = 0; i<M->size; i++){
        List L = M->row[i];
        for(moveFront(L);index(L)>=0;moveNext(L)){
            Entry m = get(L); //create the entry
            if(m->value != 0){ //Zero rows are not printed
                fprintf(out, "%d: ", i);
                fprintf(out,"(%d, %.1lf)",m->column,m->value);
                fprintf(out, "\n");
                break;
            }
        }
    }
    fprintf(out,"\n");
}