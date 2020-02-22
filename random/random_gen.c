
// C program for generating a 
// random number in a given range. 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
  
// Generates and prints 'count' random 
// numbers in range [lower, upper]. 
void printRandoms(int lower, int upper, int count) 
{ 
    int i; 
    for (i = 0; i < count; i++)
    { 
        int num = (rand() % 
           (upper - lower + 1)) + lower; 
        printf("%d \n", num); 
    } 
} 
  
// Driver code 
int main() 
{
    int num;
    // Use current time as  
    // seed for random generator 
    // num = (srand(time(0)) | 0xFFFFFFFF); 
    num = rand() | time(NULL);
    printf("%d \n", num); 
  
    return 0; 
} 

