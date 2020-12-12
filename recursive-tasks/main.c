#include <stdio.h>

void printTriangle(int n);

void printPatternRowRecur(int n);

void printOppositeTriangles(int n);

void drawRuler(int k);

int main() {
//    printTriangle(5);
//    printOppositeTriangles(5);
//    drawRuler(16);
    return 0;
}

void printTriangle(int n) {
    if (n < 1) {
        return;
    }
    printTriangle(n - 1);
    printPatternRowRecur(n);
    printf("\n");
}

void printOppositeTriangles(int n) {
    if (n < 1) {
        return;
    }
    printPatternRowRecur(n);
    printf("\n");
    printOppositeTriangles(n - 1);
    printPatternRowRecur(n);
    printf("\n");
}

void printPatternRowRecur(int n) {
    if (n < 1) {
        return;
    }
    printf("*");
    printPatternRowRecur(n - 1);
}

//void printPatternRulerRecur(int n) {
//    if (n < 1) {
//        return;
//    }
//    printf("-");
//    printPatternRulerRecur(n / 4);
//}
//
//void drawRuler(int k){
//    if (k < 1){
//        return;
//    } else {
//        printPatternRulerRecur(k);
//        printf("\n");
//        drawRuler(k-1);
//    }
//}

