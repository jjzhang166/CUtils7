/*
MIT License

Copyright (c) 2018 Joseph Ojeda

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "./src/stack.h"

int main(void) {
    // Test
    puts("Stack container functions:");
    //stack_init
    puts("\tstack stack_init(uint8_t elements_size):");
    stack_t* stack1 = stack_init(sizeof(uint8_t));
    puts("\t\tstack stack1 = stack_init(sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", (uint8_t*)stack_top(stack1));
    stack_t* stack2 = stack_init(sizeof(uint8_t));
    puts("\t\tstack stack2 = stack_init(sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack1)  = %d\n", (uint8_t*)stack_top(stack2));
    //stack_push
    puts("\tvoid stack_push(stack self, void* element, uint8_t element_size):");
    uint8_t stack1_element1 = 100;
    stack_push(stack1, &stack1_element1, sizeof(uint8_t));
    puts("\t\tstack_push(stack1, &stack1_element1, sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", *(uint8_t*)stack_top(stack1));
    uint8_t stack1_element2 = 101;
    stack_push(stack1, &stack1_element2, sizeof(uint8_t));
    puts("\t\tstack_push(stack1, &stack1_element2, sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", *(uint8_t*)stack_top(stack1));
    uint8_t stack1_element3 = 102;
    stack_push(stack1, &stack1_element3, sizeof(uint8_t));
    puts("\t\tstack_push(stack1, &stack1_element3, sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", *(uint8_t*)stack_top(stack1));
    uint8_t stack2_element1 = 200;
    stack_push(stack2, &stack2_element1, sizeof(uint8_t));
    puts("\t\tstack_push(stack2, &stack2_element1, sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack2) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack2)  = %d\n", *(uint8_t*)stack_top(stack2));
    uint8_t stack2_element2 = 201;
    stack_push(stack2, &stack2_element2, sizeof(uint8_t));
    puts("\t\tstack_push(stack2, &stack2_element2, sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack2) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack2)  = %d\n", *(uint8_t*)stack_top(stack2));
    puts("\tvoid stack_swap(stack_t* dst, stack_t* src):");
    uint8_t stack2_element3 = 202;
    stack_push(stack2, &stack2_element3, sizeof(uint8_t));
    puts("\t\tstack_push(stack2, &stack2_element3, sizeof(uint8_t))");
    printf("\t\t\tstack_size(stack2) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack2)  = %d\n", *(uint8_t*)stack_top(stack2));
    puts("\tvoid stack_swap(stack_t* dst, stack_t* src):");
    stack_swap(stack1, stack2);
    puts("\t\tstack_swap(stack1, stack2)");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", *(uint8_t*)stack_top(stack1));
    printf("\t\t\tstack_size(stack2) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack2)  = %d\n", *(uint8_t*)stack_top(stack2));
    /*puts("\tvoid stack_pop(stack_t* self):");
    stack_pop(stack1);
    puts("\t\tstack_pop(stack1):");
    printf("\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", *(uint8_t*)stack_top(stack1));
    stack_pop(stack2);
    puts("\t\tstack_pop(stack2):");
    printf("\t\t\tstack_size(stack2) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack2)  = %d\n", *(uint8_t*)stack_top(stack2));*/

    stack_t* stack3 = NULL;
    stack3 = stack_move(stack3, stack2);
    printf("\n\t\t\tstack_size(stack3) = %ld\n", stack_size(stack3));
    printf("\t\t\tstack_top(stack3)  = %d\n", *(uint8_t*)stack_top(stack3));

    printf("\n%lu\n", UINT64_MAX);

    /*stack_copy(stack1, stack2);
    printf("\n\t\t\tstack_size(stack1) = %ld\n", stack_size(stack1));
    printf("\t\t\tstack_top(stack1)  = %d\n", *(uint8_t*)stack_top(stack1));
    printf("\t\t\tstack_size(stack2) = %ld\n", stack_size(stack2));
    printf("\t\t\tstack_top(stack2)  = %d\n", *(uint8_t*)stack_top(stack2));*/

    stack_destroy(stack1);
    //stack_destroy(stack2);
    stack_destroy(stack3);
    return EXIT_SUCCESS;
}