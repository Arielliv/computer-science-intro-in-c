#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


struct _MaxAverage {
    float avg;
    int ind;
};
typedef struct _MaxAverage MaxAverage;

struct _CUSTOMER {
    char familyName[100];
    char firstName[100];
    int id;
    char cityName[1000];
};
typedef struct _CUSTOMER CUSTOMER;
#define MAX_NAME_LEN 250

bool isPrime(int num);

void printPrimeFactors(int num);

void f2(char *s1, char *s2);

void f1(char *s1, char *s2);

void f(char *s1, char *s2);

void printChar(int num);

void strCopy2(char *str1, char *str2);

void strCombaine(char *str1, char *str2);

bool isIncluded(char *str1, char *str2);

bool isArmstrong(int num);

void findDividers(int data[], int size, int n1, int n2);

void swap(CUSTOMER data[], int index1, int index2);

int main() {
    int bbb[10] = {2, 3, 6, 11, 12};
    findDividers(bbb, 5, 2, 3);
    int ii;
    for (ii = 100; ii < 1000; ii++) {
        if (isArmstrong(ii)) {
            printf("%d ", ii);
        }
    }
    printf("\n");
    bool g = isIncluded("abc", "annnblkk");
    printf("%s", g ? "true\n" : "false\n");
    char s1[200] = {'a', 'b', 'c', '\0'};
    char s2[200] = {'a', 'b', 'c', 'd', '\0'};
    strCombaine(s1, s2);
    printf("%s\n", s1);
    printChar(123);
    printf("\n");
//    int i, y;
//    MaxAverage result = {avg: 0, ind: 0};
//    float rowAvg = 0;
//    for (i = 0; i < 10; i++) {
//        for (y = 0; y < 10; y++) {
//            rowAvg += data[i][y];
//        }
//        rowAvg /= 10;
//        if (rowAvg > result.avg) {
//            result.avg = rowAvg;
//            result.ind = i;
//        }
//    }

    float x = 3.14;
    float *xp;

    xp = &x;
    *xp /= 2;
    printf("x = %f\n", x);
    printf("*xp = %f\n", *xp);
    char str1[250] = "abc";
    char str2[250] = "def";
    f1(str1, str2);
    printf("str1 =%s str2 =%s\n", str1, str2);
    f2(str2, str1);
    printf("str1 =%s str2 =%s\n", str1, str2);
    str2[3] = '\0';
    printf("%s %s\n", str2, str1 + 3);


    char srt[12] = "hello world";
    char *pp;

    srt[5] = '\0';
    printf("%s\n", srt);

    pp = srt + 6;
    f(pp, srt);

    printf("%s\n", pp);
    printf("%s\n", srt);
    int a[5] = {0, 1, 2, 3, 4};
    int i, *p;
    for (p = a, i = 0; p + 1 <= a + 5; p++, i++) {
        printf("%d %d\n", *(p + i), p - a);
    }

    printPrimeFactors(20);


    int inputNum, resultNum = 0;
    int curNum;
    int counter = 0;
    scanf("%d", &inputNum);
    while (inputNum / 10 != 0) {
        curNum = inputNum % 10;
        resultNum += (int) curNum * pow((double) 8, (double) counter);
        counter++;
        inputNum = inputNum / 10;
    }
    curNum = inputNum % 10;
    resultNum += (int) curNum * pow((double) 8, (double) counter);
    printf("\n%d", resultNum);
}


char *find(char names[][MAX_NAME_LEN], int size, char *name) {
    int left;
    int right;
    int mid;

    if (strcmp(names[0], name) == 0) {
        return NULL;
    }
    left = 0;
    right = size - 1;
    mid = (left + right) / 2;
    while (left < right) {
        if (strcmp(names[mid], name) == 0) {
            return names[mid - 1];
        } else if (strcmp(names[mid], name) > 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return NULL;

}

void printPrimeFactors(int num) {
    int i;
    if (isPrime(num) == true) {
        printf("%d ", num);
        return;
    } else {
        for (i = 2; i < num; i++) {
            if (num % i == 0) {
                printf("%d ", i);
                printPrimeFactors(num / i);
                return;
            }
        }
    }
}

bool isPrime(int num) {
    bool result = true;
    for (int i = 2; i < num; i++) {
        if (num % i == 0) {
            result = false;
        }
    }
    return result;
}

void f1(char *s1, char *s2) {
    if (s1[0] != '\0') {
        f1(s1 + 1, s2);
    } else {
        s1[0] = s2[0];
        if (s2[0] == '\0') {
            return;
        }
        f1(s1 + 1, s2 + 1);
    }
}

void f2(char *s1, char *s2) {
    s1[0] = s2[0];
    if (s2[0] == '\0') {
        return;
    }
    f2(++s1, s2 + 1);
}

void f(char *s1, char *s2) {
    int i;
    for (i = 0; s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

void strCombaine(char *str1, char *str2) {
    if (str2[0] == '\0') {
        return;
    }
    int len = strlen(str1);
    str1[len] = str2[0];
    str1[len + 1] = '\0';
    strCombaine(str1, str2 + 1);
}


void strCopy2(char *str1, char *str2) {
    if (str2[0] == '\0') {
        if (str1[0] != '\0') {
            str1[0] = '\0';
        }
        return;
    }
    str1[0] = str2[0];
    strCopy2(str1 + 1, str2 + 1);
}

void printChar(int num) {
    int curNum;
    if (num / 10 == 0) {
        curNum = num % 10;
        printf("%c", (char) 'a' + curNum);

    } else {
        curNum = num % 10;
        printChar(num / 10);
        printf("%c", (char) 'a' + curNum);
    }

}

bool isIncluded(char *str1, char *str2) {
    if (strlen(str1) == 0) {
        return true;
    } else if (strlen(str2) == 0) {
        return false;
    } else if (str1[0] == str2[0]) {
        return isIncluded(str1 + 1, str2 + 1);
    } else {
        return isIncluded(str1, str2 + 1);
    }
}

bool isArmstrong(int num) {
    int sum, copyNum;
    copyNum = num;
    double exp = 3.0;
    sum = 0;
    while (copyNum != 0) {
        sum += (int) pow((double) (copyNum % 10), exp);
        copyNum = copyNum / 10;
    }
    if (sum == num) {
        return true;
    } else {
        return false;
    }
}

void findDividers(int data[], int size, int n1, int n2) {
    if (size == 0) {
        printf("%s\n", "BACK");
        return;
    } else {

        if (data[0] % n1 == 0) {
            printf("%d\n", data[0]);
        }
        findDividers(data + 1, size - 1, n1, n2);

        if (data[0] % n2 == 0) {
            printf("%d\n", data[0]);
        }
    }
}


int moveCity(CUSTOMER data[], int size, char thisCity[]) {
    int i, y;
    int counter;
    counter = 0;
    i = 0;
    y = size;
    while (i < y) {
        if (strcmp(data[i].cityName, thisCity) == 0) {
            i++;
            counter++;
        } else {
            if (strcmp(data[y].cityName, thisCity) == 0) {
                swap(data, y, i);
                counter++;
            }
            y--;

        }

    }
    return counter;
}

void swap(CUSTOMER data[], int index1, int index2) {
    CUSTOMER tmp;
    tmp = data[1];
    data[1] = data[2];
    data[2] = tmp;
}
