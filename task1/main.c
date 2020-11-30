//315363366
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_VAL 41
void main() {
    int i,j;
    int counter = 0;

    for( i = 0; i <= 9; i++){
        for ( j=0; j <= 9; j++) {
            if(j*i <= MAX_VAL){
                printf("%d : %d * %d \n", j*i , i,j);
                counter++;
            }
        }
    }
    printf("How many numbers: %d", counter);
}