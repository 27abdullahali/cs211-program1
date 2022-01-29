//
//  main.c
//  median3
//
//  Created by Abdullah Ali on 1/26/22.
//

#include <stdio.h>
void findMedian(int numbers[3]) {
    int temp;
    
        for (int i = 0; i < (2); ++i) {
            
            for (int j = 0; j < 2 - i; ++j ) {
                
                if (numbers[j] > numbers[j+1]){
                    temp = numbers[j+1];
                    numbers[j+1] = numbers[j];
                    numbers[j] = temp;
                }
            }
        }
    
    int median = numbers[1];
    
    printf("median: %i\n", median);
    
}

int main(int argc, const char * argv[]) {
    int numbers[3];
    int ret = 0;
    
    for (int i = 0; i < 3; i++) {
        printf("Enter an integer: ");
        ret += scanf("%i", &numbers[i]);
    }
    if (ret == 3) {
        findMedian(numbers);
    }
    else {
        printf("INVALID INPUT\n");
        return 0;
    }
    
    
    return 0;
}
