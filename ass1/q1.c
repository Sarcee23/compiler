#include <stdio.h>

void analyzeBinaryString(char *binaryStr) {
    int count0 = 0, count1 = 0;

    // Traverse the binary string and count 0s and 1s
    while (*binaryStr != '\0') {
        if (*binaryStr == '0') {
            count0++;
        } else if (*binaryStr == '1') {
            count1++;
        } else {
            printf("Invalid input: Binary string should contain only 0s and 1s.\n");
            return;
        }
        binaryStr++;
    }

    // Output the counts
    printf("Number of 0s: %d\n", count0);
    printf("Number of 1s: %d\n", count1);

    // Check if the counts of 0s and 1s are equal
    if (count0 == count1) {
        printf("The number of 0s and 1s are equal.\n");
    } else {
        printf("The number of 0s and 1s are not equal.\n");
    }

    // Check if the count of 0s is odd or even
    if (count0 % 2 == 0) {
        printf("The number of 0s is even.\n");
    } else {
        printf("The number of 0s is odd.\n");
    }

      // Check if the count of 1s is odd or even
    if (count1 % 2 == 0) {
        printf("The number of 1s is even.\n");
    } else {
        printf("The number of 1s is odd.\n");
    }
}

int main() {
    char binaryStr[100];

    printf("Enter a binary string: ");
    scanf("%s", binaryStr);

    analyzeBinaryString(binaryStr);

    return 0;
}
