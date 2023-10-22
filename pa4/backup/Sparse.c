/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#4
*Sparse.c
****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "Matrix.h"

int main(int argc, char * argv[]){
    int nums; //inital the nums to store the size of the file
    FILE *in, *out;
    
    // Check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files for reading and writing 
    in = fopen(argv[1], "r");
    if( in==NULL ){
       fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
       fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }

    fscanf(in,"%d",&nums); //get the size from the file
    int u,v; //inital the two pointer
    fscanf(in, "%d", &u); 
    fscanf(in, "%d", &v);

    Matrix A = newMatrix(nums); //make a new matrix call a
    Matrix B = newMatrix(nums); //make a new matrix call b

    for(int i = 0; i < u; i++){ //change the entry of matrix A
        int r, c;
        double value;
        fscanf(in, "%d",&r);
        fscanf(in, "%d",&c);
        fscanf(in, "%lf",&value);
        changeEntry(A,r,c,value);
    }

    for(int i = 0; i < v; i++){ //change the entry of matrix B
        int r, c;
        double value;
        fscanf(in, "%d",&r);
        fscanf(in, "%d",&c);
        fscanf(in, "%lf",&value);
        changeEntry(A,r,c,value);
    }

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A); //output the matrix A
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B); //output the matrix B

    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    

    Matrix D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);

    Matrix E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);

    Matrix F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);

    fprintf(out, "A-A =\n\n");

    Matrix G = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, G);

    Matrix H = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, H);

    Matrix I = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, I);

    
    //close the filez
    fclose(in); 
    fclose(out);
}