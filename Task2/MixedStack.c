#include <stdio.h>
#include <ctype.h> // to use tolower() function
#include <unistd.h> // to be able to use sleep function
#include <stdbool.h>// to use boolean
#include "MixedStack_t.h" // Link to MixedStack_t.h

//decoder int
void int_decoder(void *value, char *buffer) {
    snprintf(buffer, 100, "%d", *(int *) value); // copy the int value to buffer
}

//decoder string
void string_decoder(void *value, char *buffer) {
    strncpy(buffer, (char *) value, 64); // copy the string value to the buffer
}

// Main() Function
int main() {
    // Create a new mixed stack
    MixedStack stack;
    initMixedStack(&stack);
    int choice;
    bool end = false; // condition to get out of loop

    do {
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
        choice = tolower(getchar());
        switch (choice) {
            case '1': {
                sleep(0.5); // Pause for 0.5 seconds
                int type_choice;
                printf("\nChoose your data type: \n(1)Integer\n(2)String\nChoice: ");
                scanf("%d", &type_choice);
                if(type_choice == 1){
                    printf("Push integer selected...\n");
                    sleep(1); // Pause for 1 second
                    int value;
                    printf("Enter integer value: ");
                    scanf("%d", &value);
                    push(&stack, INTEGER_TYPE, &value);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    fflush(stdin);
                    break;
                }
                else if (type_choice == 2){
                    printf("Push string selected...\n");
                    sleep(1); // Pause for 1 second
                    char value[64];
                    printf("Enter string value: ");
                    scanf("%s", value);
                    push(&stack, STRING_TYPE, value);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    fflush(stdin);
                    break;
                }
                else {
                    printf("Invalid choice!\n");
                    printf("\n");
                    sleep(1); // Pause for 1 second
                    break;
                }
            }
            case '2': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nPop element selected...\n");
                sleep(1); // Pause for 1 second
                MixedStack_elm *popped_element = pop(&stack);
                if (popped_element->type == INTEGER_TYPE) {
                    printf("\nPopped element: '%d'\n", popped_element->value.int_value);
                } else if (popped_element->type == STRING_TYPE) {
                    printf("\nPopped element: '%s'\n", popped_element->value.string_value);
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '3': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nExport stack selected...\n");
                sleep(1); // Pause for 1 second
                const char filename[] = "exported_stack.txt";
                export(&stack, int_decoder, string_decoder, filename);
                printf("Exported 100%% complete to: %s\n", filename);
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '4': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nCheck if stack is empty selected...\n");
                sleep(1); // Pause for 1 second
                char *is_empty = isEmpty(&stack);
                printf("Is stack empty?");
                sleep(1); // Pause for 1 second
                printf(" %s\n", is_empty);
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '5': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nCheck if stack is full selected...\n");
                sleep(1); // Pause for 1 second
                if (isFull(&stack)) {
                    printf("Stack is currently full\n");
                } else {
                    printf("Stack is not currently full\n");
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '6': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nCount stack size selected...\n");
                sleep(1); // Pause for 1 second
                int stack_size = count(&stack);
                printf("Current Stack size: %d\n", stack_size);
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '7': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nPeek at top element selected...\n");
                sleep(1); // Pause for 1 second
                if (!isEmpty(&stack)){
                    MixedStack_elm *top_element = peek(&stack);
                    if (top_element->type == INTEGER_TYPE) {
                        printf("Top element in Stack is: %d\n", top_element->value.int_value);
                    } else if (top_element->type == STRING_TYPE) {
                        printf("Top element in Stack is: '%s'\n", top_element->value.string_value);
                    }
                } else {
                    printf("\nError: Stack is empty!!\n");
                    sleep(2); // Pause for 1 second
                }
                sleep(1); // Pause for 1 second
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case '8': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nClear Stack selected...\n");
                sleep(1); // Pause for 1 second
                clear(&stack);
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
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nDESTROY Stack selected...\n");
                sleep(1); // Pause for 1 second
                deinitMixedStack(&stack);
                // Test isEmpty() function again post deinitMixedStack() function
                if (isEmpty(&stack)) {
                    printf("\nStack DESTROYED!!");
                    sleep(0.5); // Pause for 0.5 seconds
                    printf("The stack is NOW empty\n");
                } else {
                    printf("Error: The stack is still NOT empty\n");
                }
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }

            case 'q': {
                sleep(0.5); // Pause for 0.5 seconds
                printf("\nQuitting...\n");
                deinitMixedStack(&stack);
                end = true;
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
    }while (!end);
    sleep(0.5); // Pause for 0.5 seconds
    printf("Bye :(\n");
    return 0;
}