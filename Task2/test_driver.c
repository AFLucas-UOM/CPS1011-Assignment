#include <stdio.h>
#include <ctype.h> // to use tolower() function
#include <unistd.h> // to be able to use sleep function
#include <stdbool.h>// to use boolean
#include <string.h> // to use strcspn
#include "MixedStack_t.h" // Link to MixedStack_t.h

//decoder int
void int_decoder(void *value, char *buffer) {
    snprintf(buffer, 100, "%d", *(int *) value); //Pass the int value in 'value' and store it in 'buffer'
}

//decoder string
void string_decoder(void *value, char *buffer) {
    strncpy(buffer, (char *) value, 64); // copy the string value in 'value' and store to the buffer
}

// Main() Function
int main() {
    // Create a new mixed stack initialization
    MixedStack stack;
    initMixedStack(&stack);
    // set var to be used inside loop
    int choice;
    bool end = false; // escape character (out of loop)

    do {
        //menu
        printf("\nPlease choose from the following menu:\n");
        printf("1... Push element\n");
        printf("2... Pop element \n");
        printf("3... Export Stack\n");
        printf("4... Check if stack is empty\n");
        printf("5... Check if stack is full\n");
        printf("6... Count stack size\n");
        printf("7... Peek at top element\n");
        printf("8... Clear Stack\n");
        printf("9... Destroy Stack\n");
        printf("q... Quit\n");

        printf("Enter your choice: ");
        choice = tolower(getchar());// accept Q or q --> getchar to only take first input from user stream
        switch (choice) {
            case '1': {
                usleep(500000);// Pause for 0.5 seconds
                int type_choice;
                //Integer or String choice [PUSH]
                printf("\nChoose your data type: \n(1)Integer\n(2)String\nChoice: ");
                scanf("%d", &type_choice);
                if (type_choice == 1) {
                    printf("Push integer selected...\n");
                    sleep(1); // Pause for 1 second
                    int value;
                    printf("Enter integer value: ");
                    scanf("%d", &value);
                    push(&stack, INTEGER_TYPE, &value); // Push the value to the stack
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
                    fflush(stdin);// Flush the input buffer
                    break;
                } else if (type_choice == 2) {
                    fflush(stdin); // Flush the input buffer from prior input
                    printf("Push string selected...\n");
                    sleep(1); // Pause for 1 second
                    char value[64];
                    printf("Enter string value: ");
                    fgets(value, 64,
                          stdin); // standard input --> stdin, 64 size, [FGETS instead of scanf for whitespace store]
                    value[strcspn(value, "\n")] = 0; // read till first '\n' from user
                    push(&stack, STRING_TYPE, &value);// Push the value to the stack
                    break;
                } else {
                    printf("Invalid choice!\n"); // in case user doesn't press 1 or 2 --> return to main menu
                    printf("\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    fflush(stdin); // Flush the input buffer
                    sleep(1); // Pause for 1 second
                    break;
                }
            }
            case '2': {
                usleep(500000); // Pause for 0.5 seconds
                printf("\nPop element selected...\n");
                sleep(1); // Pause for 1 second
                MixedStack_elm *popped_element = pop(&stack); // initialize pop() function
                // in case Stack is Empty --> underflow error
                if (popped_element == NULL) {
                    printf("\nError: Stack is empty\n");
                    fflush(stdin); // Flush the input buffer
                    sleep(1); // Pause for 1 second
                    continue; // return to main menu
                }
                // Type: Integer
                if (popped_element->type == INTEGER_TYPE) {
                    printf("\nPopped element: '%d'\n", popped_element->value.int_value);
                    // Type: String
                } else if (popped_element->type == STRING_TYPE) {
                    printf("\nPopped element: '%s'\n", popped_element->value.string_value);
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '3': {
                usleep(500000);// Pause for 0.5 seconds
                printf("\nExport stack selected...\n");
                sleep(1); // Pause for 1 second
                const char filename[] = "exported_stack.txt"; // Filename where the stack will be exported to
                export(&stack, int_decoder, string_decoder,filename); // Export the stack to a file using the int_decoder and string_decoder functions
                printf("Exported 100%% complete to: %s\n", filename);
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
                break;
            }

            case '4': {
                usleep(500000); // Pause for 0.5 seconds
                printf("\nCheck if stack is empty selected...\n");
                sleep(1); // Pause for 1 second
                char *is_empty = isEmpty(&stack); // call isEmpty() function
                printf("Is stack empty?");
                sleep(1); // Pause for 1 second
                printf(" %s\n", is_empty);
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '5': {
                usleep(500000); // Pause for 0.5 seconds
                printf("\nCheck if stack is full selected...\n");
                usleep(1500000); // Pause for 1.5 seconds
                // IS full
                if (isFull()) {
                    printf("Stack is currently full\n");
                    // is NOT full
                } else {
                    printf("Stack is NOT currently full\n");
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '6': {
                usleep(500000);// Pause for 0.5 seconds
                printf("\nCount stack size selected...\n");
                sleep(1); // Pause for 1 second
                int stack_size = count(&stack); // initialize count() function
                printf("Current Stack size: %d\n", stack_size); // prints out the number in count()
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '7': {
                usleep(500000);// Pause for 0.5 seconds
                printf("\nPeek at top element selected...\n");
                sleep(1); // Pause for 1 second
                MixedStack_elm *top_element = peek(&stack); // peek() initialized
                // Type: INT
                if (top_element->type == INTEGER_TYPE) {
                    printf("Top element in Stack is: '%d'\n", top_element->value.int_value);
                    //Type: String
                } else if (top_element->type == STRING_TYPE) {
                    printf("Top element in Stack is: '%s'\n", top_element->value.string_value);
                    // EMPTY STACK error
                } else {
                    printf("\nError: Stack is empty!!\n");
                    sleep(1); // Pause for 1 second
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                fflush(stdin);  // Flush the input buffer
                break;
            }

            case '8': {
                usleep(500000);// Pause for 0.5 seconds
                printf("\nClear Stack selected...\n");
                sleep(1); // Pause for 1 second
                clear(&stack); // CLEAR STACK FUNCTION
                // Check if the stack is empty post Clear function
                if (isEmpty(&stack)) {
                    printf("The stack is NOW empty\n");
                } else {
                    printf("Error: The stack is still NOT empty\n");
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '9': {
                usleep(500000);// Pause for 0.5 seconds
                printf("\nDESTROY Stack selected...\n");
                sleep(1); // Pause for 1 second
                deinitMixedStack(&stack); //DESTROY  STACK FUNCTION
                // Test isEmpty() function again post deinitMixedStack() function
                if (isEmpty(&stack)) {
                    printf("\nStack DESTROYED!! ");
                    usleep(500000); // Pause for 0.5 seconds
                    printf("The stack is NOW empty\n");
                } else {
                    printf("Error: The stack is still NOT empty\n");
                }
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case 'q': {
                usleep(500000); // Pause for 0.5 seconds
                printf("\nQuitting...\n");
                deinitMixedStack(&stack);
                end = true; // escape character initialized --> out_of_loop
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            default:
                printf("\nInvalid choice. Please try again.\n");
                printf("\n");
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
        }
    } while (!end); // escape character 'end'
    usleep(500000);// Pause for 0.5 seconds
    printf("Bye :(\n");
    return 0;
}