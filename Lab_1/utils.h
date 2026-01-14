/* This file contains declarations of structures and functions that are used in multiple files */
#ifndef UTILS_H
#define UTILS_H

/* Structure declarations */
typedef struct Subject{
    char name[20];
    int min_marks;
    int maj_marks;
    int total;
    char grade[3];
    int point;
}Subject;

typedef struct Student{
    char id[20];
    char name[20];
    Subject subjects[5];
    int total;
    float percentage;
    char grade[3];
    float cgpa;
}Student;

/* Function declarations */
Student* readStudentData(char* filename, int* count);
void printStudentData(char* filename, Student* students, int count);

#endif