#include<stdio.h>
#include<stdlib.h>
#include "utils.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <inutFile> <outputFile>\n", argv[0]);
        return 1;
    }

    int count = 0;
    Student *students = readStudentData(argv[1], &count);
    printStudentData(argv[2], students, count);

    return 0;
}