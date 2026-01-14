/* This file contains the defenation of funtions that are declared in utils.h header file along with some basic utility functions for computations */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "utils.h"

/* Variable declarations */
float avg = 0, high, low;
int grade_freq[8] = {0, 0, 0, 0, 0, 0, 0, 0};

/* UTILITY FUNCTIONS */
// This function is used to check for duplicate Ids
int is_unique_id(Student *students, int count, const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) return 0;
    }
    return 1;
}

//This function is used ensure names contains only alphabets
int is_valid_name(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i])) return 0;
    }
    return 1;
}

//This function returns grades with respect to given marks/ percentage
char* getGrade(int marks){
    if(marks < 50){
        return "F";
    }else if(marks >= 50 && marks <= 54){
        return "P";
    }else if(marks >= 55 && marks <= 59){
        return "C";
    }else if(marks >= 60 && marks <= 64){
        return "B";
    }else if(marks >= 65 && marks <= 74){
        return "B+";
    }else if(marks >= 75 && marks <= 84){
        return "A";
    }else if(marks >= 85 && marks <= 90){
        return "A+";
    }else{
        return "O";
    }
}

//This function returns points with respect to given marks/ percentage
int getPoint(int marks){
    if(marks < 50){
        return 0;
    }else if(marks >= 50 && marks <= 54){
        return 4;
    }else if(marks >= 55 && marks <= 59){
        return 5;
    }else if(marks >= 60 && marks <= 64){
        return 6;
    }else if(marks >= 65 && marks <= 74){
        return 7;
    }else if(marks >= 75 && marks <= 84){
        return 8;
    }else if(marks >= 85 && marks <= 90){
        return 9;
    }else{
        return 10;
    }
}

//This function is used to read student data from the given file
Student* readStudentData(char* filename, int* count){

    //Opening input file
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    //Initiaing and allocating memory
    int capacity = 2;
    *count = 0;
    Student *students = malloc(sizeof(Student) * capacity);

    //Loop to read each student data
    while(1){
        int gradePoints_sum = 0; 
        int res = fscanf(fin, "%19s %19s", students[*count].id, students[*count].name);
        if(res == EOF) break;
        students[*count].total = 0;

        //Id validation
        if(!is_unique_id(students, *count, students[*count].id)){
            fprintf(stderr, "Duplicate Id: %s. Terminated.\n", students[*count].id);
            exit(EXIT_FAILURE);
        }

        //Name validation
        if(!is_valid_name(students[*count].name)){
            fprintf(stderr, "Invalid name: %s at student Id: %s. Terminated.\n", students[*count].name, students[*count].id);
            exit(EXIT_FAILURE);
        }

        //Loop to read subject wise marks
        for(int i = 0; i < 5; i++){

            //Individual subject format validation
            if(fscanf(fin, "%s %d %d", students[*count].subjects[i].name, 
                      &students[*count].subjects[i].min_marks, 
                      &students[*count].subjects[i].maj_marks) != 3){
                fprintf(stderr, "Invalid format at student Id: %s name: %s subject %d. Terminated.\n", students[*count].id, students[*count].name, i+1);
                exit(EXIT_FAILURE);
            }

            //Minor marks limit validation
            if(students[*count].subjects[i].min_marks < 0 || students[*count].subjects[i].min_marks > 40){
                fprintf(stderr, "Invalid minor marks at student Id: %s name: %s subject %d Minor marks: %d. Terminated.\n", students[*count].id, students[*count].name, i+1, students[*count].subjects[i].min_marks);
                exit(EXIT_FAILURE);
            }

            //Major marks limit validation
            if(students[*count].subjects[i].maj_marks < 0 || students[*count].subjects[i].maj_marks > 60){
                fprintf(stderr, "Invalid major marks at student Id: %s name: %s subject %d Major marks: %d. Terminated.\n", students[*count].id, students[*count].name, i+1, students[*count].subjects[i].maj_marks);
                exit(EXIT_FAILURE);
            }

            //Calculating required values
            int sub_total = students[*count].subjects[i].min_marks + students[*count].subjects[i].maj_marks;
            students[*count].subjects[i].total = sub_total;
            strcpy(students[*count].subjects[i].grade, getGrade(sub_total));
            students[*count].subjects[i].point = getPoint(sub_total);
            students[*count].total += sub_total;
            gradePoints_sum += students[*count].subjects[i].point;
        }

        students[*count].percentage = students[*count].total / 5.0f;
        strcpy(students[*count].grade, getGrade((int)students[*count].percentage));
        students[*count].cgpa = gradePoints_sum / 5.0f;

        //Computing stats from class data
        avg += students[*count].percentage;
        if(*count == 0){
            high = students[*count].percentage;;
            low = students[*count].percentage;
        }else{
            if(high < students[*count].percentage){
                high = students[*count].percentage;
            }
            if(low > students[*count].percentage){
                low = students[*count].percentage;
            }
        }
        if(getPoint((int)students[*count].percentage) == 0){
            grade_freq[0] += 1;
        }else{
            grade_freq[getPoint((int)students[*count].percentage) - 3] += 1;
        }

        //Extending memory upon reaching limit
        (*count)++;
        if (*count >= capacity) {
            capacity *= 2;
            students = realloc(students, sizeof(Student) * capacity);
        }
    }
    avg /= *count;

    //Close input file and return data
    fclose(fin);
    return students;
}

//This function is used to write student data to the given file
void printStudentData(char* filename, Student* students, int count){

    //Check if data exists
    if(!students){
        fprintf(stderr, "No data found.\n");
        exit(EXIT_FAILURE);
    }

    //Open and check output file
    FILE *fout = fopen(filename, "w");
    if(!fout){
        fprintf(stderr, "Failed to open output file");
        exit(EXIT_FAILURE);
    }

    //Formating output
    fprintf(fout, "Id\t\tName\tSubject1 Minor Major Total Grade Points Subject2 Minor Major Total Grade Points Subject3 Minor Major Total Grade Points Subject4 Minor Major Total Grade Points Subject5 Minor Major Total Grade Points GrandTotal Percentage Grade CGPA\n");
    for(int i = 0; i < count; i++){
        fprintf(fout, "%s\t%s\t ", students[i].id, students[i].name);
        for(int j = 0; j < 5; j++){
            fprintf(fout, "%s\t%d\t\t%d\t\t%d\t\t%s %d\t\t", students[i].subjects[j].name, students[i].subjects[j].min_marks, students[i].subjects[j].maj_marks, students[i].subjects[j].total, students[i].subjects[j].grade, students[i].subjects[j].point);
        }
        fprintf(fout, "%d %.2f %s %.2f\n", students[i].total, students[i].percentage, students[i].grade, students[i].cgpa);
    }

    //Printing stats
    fprintf(fout, "\nClass Average Percentage: %.2f\nHighest Percentage: %.2f\nLowest Percentage: %.2f\n", avg, high, low);
    fprintf(fout, "\nGrade Count\nO\t %d\nA+\t %d\nA\t %d\nB+\t %d\nB\t %d\nC\t %d\nP\t %d\nF\t %d\n", grade_freq[7], grade_freq[6], grade_freq[5], grade_freq[4], grade_freq[3], grade_freq[2], grade_freq[1], grade_freq[0]);

    //Close output file
    fclose(fout);
}