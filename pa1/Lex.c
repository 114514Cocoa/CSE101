/****************************************************************************
*Yiqi Li yli823
*2022 Winter CSE101 PA#1
*Lex.c
****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]){
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];

    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read each line of input file, then count and print tokens
    line_count = 0;
    while( fgets(line, MAX_LEN, in) != NULL)  {
        line_count++; //increase the line count
    }

    char** strl = malloc(line_count * sizeof(*strl));
    rewind(in); //restart
    int i = 0;
    while(fgets(line, MAX_LEN, in)!=NULL){ //get the line
        char *a = malloc(strlen(line)+1); //malloc the a
        if(a){
            strcpy(a,line);
        }
        strl[i] = a;
        i++;
    }

    List L = newList(); //make a new list
    append(L, 0);
    moveFront(L); //put the point to the front
    for(int i = 1; i < line_count; i++){ // insert the ith element
        for(moveFront(L); index(L) >= 0; moveNext(L)){
            if(strcmp(strl[get(L)], strl[i]) > 0){
                break;
            }
        }
        if(index(L) < 0){
            append(L, i);
        }else{
            insertBefore(L,i);
        }
    }

    for(moveFront(L); index(L) >= 0; moveNext(L)){
        int x = get(L); //get the value from list
        fprintf(out,"%s", strl[x]);
    }

    freeList(&L);
    for(i = 0; i < line_count;i++){
        free(strl[i]);
    }
    free(strl);
    fclose(in);
    fclose(out);
}