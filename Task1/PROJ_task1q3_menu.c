#include <stdio.h>
#include <string.h> // needed for strlen function
#include <unistd.h> // to be able to use sleep function
#include "palindrome.h" // link to palindrome header file
#include "matrix.h" // link to matrix header file


int main(void) {
    char str[100]; // Declare string with size 100
    int choice; // Declare variable outside of loop (to be used for user choice
    bool end = false; // condition to get out of loop

    do{
        printf("Please choose from the following menu:\n");
        printf("1... Iterative Palindrome Checker\n2... Recursive Palindrome Checker\n3... Matrix Calculator\nq... Quit\n\nEnter your choice: ");
        choice = tolower(getchar());
        int b;
        while ((b = getchar()) != '\n' && b != EOF); //this loop is used to consume any remaining input in the buffer, effectively clearing the buffer
        switch (choice) {
            case '1':
                printf("\nIterative checker selected...\n");
                sleep(1);  // Pause for 1 seconds
                printf("\nEnter a string to check if it is a palindrome: ");
                scanf("%s", str);

                // Force all characters to lowercase, using tolower function
                to_lower(str);
                sleep(1); // Pause for 1 second

                // Call iterative palindrome checker function
                if (Palindrome_Iterative(str)) {
                    printf("The string '%s' IS a palindrome.\n", str);
                } else {
                    printf("The string '%s' IS NOT a palindrome.\n", str);
                }
                printf("\n");
                sleep(1); // Pause for 1 second

                int c;
                while ((c = getchar()) != '\n' && c != EOF); //this loop is used to consume any remaining input in the buffer, effectively clearing the buffer
                break;

            case '2':
                printf("\nRecursive checker selected...\n");
                sleep(1); // Pause for 1 second
                printf("\nEnter a string to check if it is a palindrome: ");
                scanf("%s", str);

                // Force all characters to lowercase, using tolower function
                to_lower(str);
                sleep(1); // Pause for 1 second

                // Call recursive palindrome checker function
                if (Palindrome_Recursive(str, 0, strlen(str) - 1)) {
                    printf("The string '%s' IS a palindrome.\n", str);
                } else {
                    printf("The string '%s' IS NOT a palindrome.\n", str);
                }
                printf("\n");
                sleep(1); // Pause for 1 seconds

                int d;
                while ((d = getchar()) != '\n' && d != EOF); //this loop is used to consume any remaining input in the buffer, effectively clearing the buffer
                break;
            case '3':
                printf("\nMatrix Calculator...\n");
                sleep(1); // Pause for 1 second
                matrix();
                int e;
                while ((e = getchar()) != '\n' && e != EOF); //this loop is used to consume any remaining input in the buffer, effectively clearing the buffer
                break;
            case 'q':
                printf("\nQuitting...\n");
                end = true;
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                printf("\n");
                sleep(1); // Pause for 1 second
                int g;
                while ((g = getchar()) != '\n' && g != EOF); //this loop is used to consume any remaining input in the buffer, effectively clearing the buffer
                break;
        }
    }while(!end);
    sleep(1); // Pause for 1 second
    printf("Bye:(\n");
    return 0;
}