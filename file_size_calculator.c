#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_size_calculator.h"

// opens the input text file and calculates the number of characters in it
long int findSize(char file_name[])
{
    FILE* fp = fopen(file_name, "r");

    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    long int res = ftell(fp);

    fclose(fp);

    return res;
}

int sizeGiver(char file_name[]){

    long int res = findSize(file_name);

    if (res != -1)

        return res;

    return -1;
}