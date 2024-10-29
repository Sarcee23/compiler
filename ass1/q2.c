#include <stdio.h>
#include <string.h>

void analyzeCharacterString(const char *charString) {
    int countA = 0, countB = 0;
    
    // Count the number of 'a's and 'b's
    for (const char *ptr = charString; *ptr != '\0'; ++ptr) {
        if (*ptr == 'a') {
            countA++;
        } else if (*ptr == 'b') {
            countB++;
        }
        else {
            printf("Error: Invalid character '%c' found. Only 'a' and 'b' are allowed.\n", *ptr);
            return;
        }
    }

    // Display counts of 'a' and 'b'
    printf("Number of 'a's: %d\n", countA);
    printf("Number of 'b's: %d\n", countB);

    // Check if the count of 'a's and 'b's are equal
    if (countA == countB) {
        printf("The number of 'a's and 'b's are equal.\n");
    } else {
        printf("The number of 'a's and 'b's are not equal.\n");
    }

    // Check if the number of 'a's is odd or even
    if (countA % 2 == 0) {
        printf("The number of 'a's is even.\n");
    } else {
        printf("The number of 'a's is odd.\n");
    }

     // Check if the number of 'b's is odd or even
    if (countB % 2 == 0) {
        printf("The number of 'b's is even.\n");
    } else {
        printf("The number of 'b's is odd.\n");
    }
}

int main() {
    char charString[100];
    
    printf("Enter a string containing only 'a' and 'b': ");
    scanf("%s", charString);

    analyzeCharacterString(charString);

    return 0;
}
