#include <stdio.h>
#include "MixedStack_t.h"
//#include "MixedStack_t(b).h"

int main(void) {
    MixedStack_elm stack;
    initMixedStack(&stack);
    //mixedstack_push(&stack, 3);
    push(&stack, "hello");
    // ...
    return 0;
}