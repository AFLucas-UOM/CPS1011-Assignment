#include <stdio.h>
// TESTING PURPOSES ONLY

int main(void) {

    printf("Hello World\nWelcome\n");
    int dogs, cats, pets;


    printf("How many dogs do you have?\n");
    scanf("%d", &dogs);

    printf("So you have %d dog(s)!\n", dogs);
    printf("How many cats do you have?\n");
    scanf("%d", &cats);

    pets = dogs + cats;
    printf("So you have %d pet(s)!\n", pets);
}


