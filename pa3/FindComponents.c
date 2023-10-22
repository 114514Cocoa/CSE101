/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#3
*FindXomponents.c
****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "Graph.h"

int main(int argc, char * argv[]){
    int nums; //inital the nums to store the order of the file
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
    fscanf(in, "%d", &nums); //use fscanf to read the order and store it
    Graph G = newGraph(nums); //make a  new graph
    int u ,v; //inital the value of two point
    fscanf(in, " %d", &u); 
    fscanf(in, " %d", &v);
    while (u != 0 || v != 0){ //loop to get the point from file and add it to the graph
        addArc(G, u, v); //add it the graph
        fscanf(in, " %d", &u); 
        fscanf(in, " %d", &v);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out,G); //output the graph

    List L = newList();
    int n = getOrder(G);
    for(int i = 1; i <= n; i++){
        append(L,i);
    }
    DFS(G,L);
    Graph R = transpose(G); //make the transpose of graph g
    DFS(R,L);
    //print the strong components of G to the output file to topologically sorted order
    List S = newList(); //make the other list to store the value

    int leng = 0; //inital the lenght
    int count = 0; 

    for(moveFront(L); index(L) >= 0; moveNext(L)){
        if(leng < length(L)){
            if(getParent(R,get(L)) == NIL){
                count++;
                prepend(S,get(L)); //put the value to the new list
            }
            leng++; //length increase
        }
    }
    fprintf(out, "\nG contains %d strongly connected components:\n",count); //output the number of connected

    int a = 0; //the componments begian 1
    for(moveFront(S); index(S) >= 0; moveNext(S)){
        a++;
        fprintf(out, "Component %d: ",a);
        List C = newList();
        if(index(L) < 0 ){
            moveBack(L);
        }
        while(index(L) >= 0){
            if(getParent(R,get(L)) == NIL){
                prepend(C, get(L));
                movePrev(L);
                break;
            }
            prepend(C, get(L));
            // fprintf(out, " %d", get(S));
            movePrev(L);
        }
        printList(out, C);
        fprintf(out, "\n");
        freeList(&C);
    }
    fclose(in); //close the file
    fclose(out);
    freeGraph(&G); //free the memory
    freeList(&L);
    freeList(&S);

}
