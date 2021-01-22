#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ROWS 256
#define COLS 100

int countPal(char mat[ROWS][COLS], int strNum);

bool isPalindrome(char *str);

void f(int *b);

void g(int b[][3]);

void strcatRec(char *str1, char *str2);

bool findXneigh(int data[], int size, int x);

void cpUpper(char str[], char strUpper[]);

void main() {
    int result;
    char mat[ROWS][COLS] = {{'a', 'b', 'c', 'd', '\0'},
                            {'a', 'b', 'a', '\0'},
                            {'a', 'b', 'c', 'd', 'a', '\0'},
                            {'a', 'b', '\0'},
                            {'a', 'b', 'c', 'b', 'a', '\0'}};
    result = countPal(mat, 5);
    printf("%c\n", *mat[0] + 1);
    printf("%d\n", result);

    int b[3][3] = {{0, 1, 2},
                   {3, 4, 5},
                   {6, 7, 8}};
    f(b[0]);
    g(b + 1);
    f(*(b + 1));
    printf("%d\n", *(b[1]));
    printf("%d\n", *(b[2]));

    char str1[8] = {'s', 'd', 's', 'd', '\0'};
    char str2[5] = {'s', 'd', 's', 'd'};
    strcatRec(str1, str2);
    printf("%s\n", str1);
    int array[10] = {1, 2, 3, 7, 10};
    printf(findXneigh(array, 5, -1) ? "true" : "false");
    char *tStr = "aQVb1De";
    char strUpper[10];
    cpUpper(tStr, strUpper);
    printf("\n%s", strUpper);
}


int countPal(char mat[ROWS][COLS], int strNum) {
    int i;

    int counter = 0;
    bool isPal;
    for (i = 0; i < strNum; i++) {
        isPal = isPalindrome(mat[i]);

        if (isPal) {
            counter++;
        }
    }

    return counter;
}

bool isPalindrome(char *str) {
    int indexStrRowStart, indexStrRowEnd;
    bool isPal;

    indexStrRowStart = 0;
    indexStrRowEnd = strlen(str) - 1;
    isPal = true;
    while (indexStrRowStart < indexStrRowEnd) {
        if (str[indexStrRowStart] != str[indexStrRowEnd]) {
            isPal = false;
        }
        indexStrRowStart++;
        indexStrRowEnd--;
    }
    return isPal;
}

//{{0, 1, 2},
//{3, 4, 5},
//{6, 7, 8}};
void g(int b[][3]) {
    printf("before \n");
    printf("\t*b[0] : %d\n", *b[0]);
    printf("\t*b[0] + 1 : %d\n", *b[0] + 1);
    printf("\t*(b[0]) : %d\n", *(b[0]));
    printf("\t*(b[0] + 1) : %d\n", *(b[0] + 1));
    printf("\t*b[0] + 1 : %d\n", *b[0] + 1);
    for (int i = 0; i < 3; ++i) {
        printf("\t\t %d\n", b[0][i]);
    }
    *b[0] = *b[0] + 1;
    //{{0, 1, 2},
//{4, 4, 5},
//{6, 7, 8}};
    printf("\t*b[0] + 1 : %d\n", *b[0] + 1);
    *(b[0] + 1) += *b[0] + 1;
    printf("after \n");
    printf("\t*b[0] : %d\n", *b[0]);
    printf("\t*b[0] + 1 : %d\n", *b[0] + 1);
    printf("\t*(b[0]) : %d\n", *(b[0]));
    printf("\t*(b[0] + 1) : %d\n", *(b[0] + 1));
    printf("\t*b[0] + 1 : %d\n", *b[0] + 1);
    for (int i = 0; i < 3; ++i) {
        printf("\t\t %d\n", b[0][i]);
    }
}

void f(int *b) {
    int *p;
    for (p = &b[1]; p <= &b[3]; p++)
        printf("%d ", *p);
    printf("\n");
}

typedef struct item {
    int val;
    struct item *next;
} ITEM;

int countSeq(ITEM *head) {
    int counter = 0;
    if ((*head).next == NULL) {
        return counter;
    }

    if ((head->next->val) == (*head).val) {
        counter++;
    }
    return counter += countSeq(head->next);
}

void strcatRec(char *str1, char *str2) {
    if (str2[0] == '\0') {
        return;
    }
    int i = 0;
    while (str1[i] != '\0') {
        i++;
    }
    str1[i] = str2[0];
    str1[i + 1] = '\0';
    strcatRec(str1, str2 + 1);
}

bool findXneigh(int data[], int size, int x) {
    if (size == 1) {
        return false;
    }
    if (data[0] > data[1]) {
        if (data[0] - data[1] == x) {
            return true;
        }
    } else {
        if (data[1] - data[0] == x) {
            return true;
        }
    }
    return findXneigh(data + 1, size - 1, x);
}

void cpUpper(char str[], char strUpper[]) {
    char currentChar[2] = {str[0], '\0'};

    if (currentChar[0] == '\0') {
        return;
    }
    if (currentChar[0] >= 'A' && currentChar[0] <= 'Z') {
        strcat(strUpper, currentChar);
    }
    cpUpper(str + 1, strUpper);
}
