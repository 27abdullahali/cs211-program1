//
//  main.c
//  num_ones
//
//  Created by Abdullah Ali on 1/26/22.
//

#include <stdio.h>

void numOnesInBinary(int userInput) {
    int numOnes = 0;
    int remainder;
    
    while (userInput > 0) {
        remainder = userInput % 2;
        userInput = userInput / 2;
        
        if (remainder != 0) {
            numOnes++;
        }
    }
    printf("That number has %i one(s) in its binary representation\n", numOnes);
    
    
}

int main(int argc, const char * argv[]) {
    int userInput;
    int ret;
    printf("Enter a non-negative integer: ");
    ret = scanf("%i", &userInput);
    
    if (ret == 1 && userInput >= 0) {
        numOnesInBinary(userInput);
    }
    else {
        printf("INVALID INPUT\n");
        return 0;
    }
    return 0;
}
