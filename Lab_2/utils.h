/* This file contains declarations of structures and functions that are used in multiple files */
#ifndef UTILS_H
#define UTILS_H

/* Structure declarations */
typedef struct Subject{
    char name[20];
    int min_marks;
    int maj_marks;
    int total;
    int point;
    char grade[3];
}Subject;

typedef struct Student{
    char id[20];
    char name[20];
    Subject subjects[5];
    int total;
    float percentage;
    float cgpa;
    char grade[3];
}Student;

/* Function declarations */
Student* readStudentData(char* filename, int* count);
void printStudentData(char* filename, Student* students, int count);

#endif