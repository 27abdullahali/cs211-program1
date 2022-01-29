//
//  main.c
//  stairs
//
//  Created by Abdullah Ali on 1/26/22.
//
#include <stdio.h>

void printStairs(int numStairs) {
    int numX = 1;
    int numSpaces = numStairs - 1;
    
    printf("up: \n\n");
    
    for (int i = 0; i < numStairs; i++) {
        
        for (int j = 0; j < numSpaces; j++) {
            printf(" ");
        }
        
        for (int k = 0; k < numX; k++) {
            printf("X");
        }
        printf("\n");
        numSpaces--;
        numX++;
    }
    
    printf("\n\ndown:\n\n");
    
    numX = 1;
    for (int i = 0; i < numStairs; i++) {
        for (int j = 0; j < numX; j++) {
            printf("X");
        }
        printf("\n");
        numX++;
    }
    
    printf("\n\nup-down:\n\n");
    
    for (int i = 0; i <= numStairs; i++) {
        for (int j = 0; j < numStairs - i; j++) {
            printf(" ");
        }
        
        for (int k = 0; k < ((2 * i) - 1); k++) {
            printf("X");
        }
        printf("\n");
    }
    printf("\n");

    
}



int main(int argc, const char * argv[]) {
    int numStairs;
    int ret = 0;
    
    printf("Enter number of stairs: ");
    ret = scanf("%i", &numStairs);
    
    if ( (ret == 1) && (numStairs >= 0) ) {
        printStairs(numStairs);
    }
    else {
        printf("INVALID INPUT\n");
        return 0;
    }
    
    return 0;
}
