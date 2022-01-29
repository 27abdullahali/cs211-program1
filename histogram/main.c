//
//  main.c
//  histogram
//
//  Created by Abdullah Ali on 1/27/22.
//

#include <stdio.h>

void printHistogram(int A, int B, int C, int D, int max) {
    int max2 = max;
    
    for (int i = 0; i < max; i++) {
        printf(" ");
        if (A >= max2) {
            printf("X");
        }
        else {
            printf(" ");
        }
        printf(" ");
        
        if (B >= max2) {
            printf("X");
        }
        else {
            printf(" ");
        }
        printf(" ");
        
        if (C >= max2) {
            printf("X");
        }
        else {
            printf(" ");
        }
        printf(" ");
        
        if (D >= max2) {
            printf("X");
        }
        else {
            printf(" ");
        }
        printf(" ");
        max2--;
        printf("\n");
    }
    printf("---------\n");
    printf(" A B C D\n");
}

int main(int argc, const char * argv[]) {
    int A;
    int B;
    int C;
    int D;
    int ret = 0;
    
    printf("A: ");
    ret = scanf("%i", &A);
    if (ret != 1 || A < 0) {
        printf("INVALID INPUT\n");
        return 0;
    }
    int max = A;
    
    printf("B: ");
    ret = scanf("%i", &B);
    if (ret != 1 || B < 0) {
        printf("INVALID INPUT\n");
        return 0;
    }
    if (B > max) {
        max = B;
    }
    
    printf("C: ");
    ret = scanf("%i", &C);
    if (ret != 1 || C < 0) {
        printf("INVALID INPUT\n");
        return 0;
    }
    if (C > max) {
        max = C;
    }
    
    printf("D: ");
    ret = scanf("%i", &D);
    if (ret != 1 || D < 0) {
        printf("INVALID INPUT\n");
        return 0;
    }
    if (D > max) {
        max = D;
    }
    
    printHistogram(A, B, C, D, max);
    return 0;
}
