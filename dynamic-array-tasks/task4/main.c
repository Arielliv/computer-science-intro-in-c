/*315363366*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#define MAX_NAME 20
#define GOOD 80

struct student {
    char name[MAX_NAME];
    int id;
    double averageGrade;
};
typedef struct student STUDENT;

// returns all student in array average grade
double average(STUDENT students[], int size);

// create new student from user input
STUDENT getStudentData();

// prints all students name who got more then `GOOD` average grade
void printGoodStudents(STUDENT students[], int size);

void main() {
    int arrayStudentSize, index;
    STUDENT *students;
    STUDENT newStudent;

    scanf("%d", &arrayStudentSize);

    students = (struct student *) malloc(sizeof(struct student) * arrayStudentSize);
    for (index = 0; index < arrayStudentSize; ++index) {
        newStudent = getStudentData();
        students[index] = newStudent;
    }

    printGoodStudents(students, arrayStudentSize);
}

STUDENT getStudentData() {
    STUDENT student;
    scanf("%s", student.name);
    scanf("%d", &student.id);
    scanf("%lf", &student.averageGrade);

    return student;
}

double average(STUDENT students[], int size) {
    int i;
    double sum = 0;

    for (i = 0; i < size; i++) {
        sum += students[i].averageGrade;
    }
    return sum / size;
}

void printGoodStudents(STUDENT students[], int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (students[i].averageGrade > GOOD) {
            printf("%s\n", students[i].name);
        }
    }
}