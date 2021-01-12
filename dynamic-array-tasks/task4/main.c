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

// sort students in array by id
void sortStudents(STUDENT students[], int size);

// copy array2 to array1
void copyArray(STUDENT array1[], STUDENT array2[], int size);

// merge arrays
STUDENT *merge(STUDENT array1[], int size1, STUDENT array2[], int size2);

//merge sort foe STUDENT array
void mergeSort(STUDENT arr[], int size);

// prints all students names in array
void printStudentsName(STUDENT students[], int size);

// handle malloc failure
void handleMallocFailure();

// find student by id
int findStudent(STUDENT students[], int size, int id, STUDENT *s);

// binary search for student by id
int binarySearch(STUDENT students[], int firstIndex, int lastIndex, int searchedValue);

void main() {
    int arrayStudentSize, index, searchStudentId, searchResultStudentIndex;
    STUDENT *students;
    STUDENT newStudent;
    STUDENT searchedStudent;

    scanf("%d", &arrayStudentSize);

    students = (struct student *) malloc(sizeof(struct student) * arrayStudentSize);
    if (students == NULL) {
        handleMallocFailure();
    }
    for (index = 0; index < arrayStudentSize; ++index) {
        newStudent = getStudentData();
        students[index] = newStudent;
    }

    scanf("%d", &searchStudentId);
    sortStudents(students, arrayStudentSize);
    searchResultStudentIndex = findStudent(students, arrayStudentSize, searchStudentId, &searchedStudent);
    printf("%d", searchResultStudentIndex);
    free(students);
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


void sortStudents(STUDENT students[], int size) {
    mergeSort(students, size);
}

void mergeSort(STUDENT students[], int size) {
    STUDENT *tmpArr = NULL;
    if (size <= 1) {
        return;
    }

    mergeSort(students, size / 2);
    mergeSort(students + size / 2, size - size / 2);
    tmpArr = merge(students, size / 2, students + size / 2, size - size / 2);
    if (tmpArr) {
        copyArray(students, tmpArr, size);
        free(tmpArr);
    } else {
        handleMallocFailure();
    }
}

void copyArray(STUDENT array1[], STUDENT array2[], int size) {
    int i;
    for (i = 0; i < size; ++i) {
        array1[i] = array2[i];
    }
}

STUDENT *merge(STUDENT array1[], int size1, STUDENT array2[], int size2) {
    int index1, index2, resultIndex;
    STUDENT *result = (STUDENT *) malloc((size1 + size2) * sizeof(STUDENT));

    if (result) {
        index1 = index2 = resultIndex = 0;
        while ((index1 < size1) && (index2 < size2)) {
            if (array1[index1].id <= array2[index2].id) {
                result[resultIndex] = array1[index1];
                index1++;
            } else {
                result[resultIndex] = array2[index2];
                index2++;
            }
            resultIndex++;
        }

        while (index1 < size1) {
            result[resultIndex] = array1[index1];
            index1++;
            resultIndex++;
        }
        while (index2 < size2) {
            result[resultIndex] = array2[index2];
            index2++;
            resultIndex++;
        }
    }
    return result;
}

void printStudentsName(STUDENT students[], int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("%s ", students[i].name);
    }
    printf("\n");
}

void handleMallocFailure() {
    printf("Memory allocation failure!!!\n");
    exit(1);
}

int findStudent(STUDENT students[], int size, int id, STUDENT *s) {
    int studentIndex;
    studentIndex = binarySearch(students, 0, size - 1, id);
    if (studentIndex != -1) {
        *s = students[studentIndex];
    }
    return studentIndex;
}

int binarySearch(STUDENT students[], int firstIndex, int lastIndex, int searchedValue) {
    if (lastIndex >= firstIndex) {
        int mid = firstIndex + (lastIndex - firstIndex) / 2;

        if (students[mid].id == searchedValue)
            return mid;

        if (students[mid].id > searchedValue)
            return binarySearch(students, firstIndex, mid - 1, searchedValue);

        return binarySearch(students, mid + 1, lastIndex, searchedValue);
    }

    return -1;
}