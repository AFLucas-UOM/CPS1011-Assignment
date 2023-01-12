#include <stdbool.h> // needed for boolean data type
#include <string.h> // needed for strlen function
#include <ctype.h> // needed to use tolower function

// Iterative function to check if a string is a palindrome
bool Palindrome_Iterative(const char *str) {
    for (int i = 0;i < strlen(str) / 2; i++) { // Iterate through the string and compare characters at opposite ends of the string
        if (str[i] != str[strlen(str) - i - 1]) { // if characters don't match return false
            return false;
        }
    }
    return true;
}

// Recursive function to check if a string is a palindrome
bool Palindrome_Recursive(const char *str, int i, int z) {
    if (i >= z) { // Base case: if the indices have passed each other, return true
        return true;
    }
    if (str[i] != str[z]) { // if characters don't match return false
        return false;
    }
    return Palindrome_Recursive(str, i + 1, z - 1); // Recursive case: Check next pair of characters
}

//to_lower function ONLY USE FOR PALINDROME (both iterative and recursive)
void to_lower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}