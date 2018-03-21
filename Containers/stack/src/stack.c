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

#include <stdlib.h>  // malloc, NULL

#include "./stack.h"

typedef struct stack_node {
    void* element;
    struct stack_node* next;
} stack_node;

struct _internal_stack {
    size_t size;
    size_t elements_size;
    stack_node* top;
};

/**
 * Check if a stack and it's elements are not null.
 */
bool stack_status(stack_t* const self) {
    return self && self->top;
}
///////////
// Basic //
///////////
/**
 * @brief Initialize a new stack container.
 * 
 * @param element_size What kind of variables is going to hold the stack container.
 * @param copy Pass a stack container and initialize a new stack with it's elements.
 * 
 * @return A new stack container.
 */
stack_t* stack_init(const size_t elements_size) {
    if (!elements_size) {
        return NULL;
    }
    stack_t* init = malloc(sizeof(stack_t));
    if (!init) {
        return NULL;
    }
    init->size = 0;
    init->elements_size = elements_size;
    init->top = NULL;
    return init;
}
/**
 * @brief Free the memory of a stack elements plus stack itself.
 *
 * @param self The stack to be freed.
 */
void stack_destroy(stack_t* const self) {
    if (!self) {
        return;
    }
    if (!self->size) {
        free(self);
    }
    else if (self->size) {
        stack_clear(self);
        free(self->top);
        free(self);
    }
}
////////////
// Access //
////////////
/**
 * @brief Returns if a stack container has any element at all.
 *
 * @param self Stack container to check elements from.
 *
 * @return Return true if self stack node is null.
 */
bool stack_is_empty(stack_t* const self) {
    return self ? self->top == NULL : true;
}
/**
 * @brief Return the element at the top of a stack container.
 * 
 * @param self Stack container to retrieve element from.
 * 
 * @return Return the element at the top of self.
 */
void* stack_top(stack_t* const self) {
    if (!stack_status(self)) {
        return NULL;
    }
    return self->top->element;
}
//////////////
// Capacity //
//////////////
/**
 * @brief Returns the current size of a stack container.
 *
 * @param self Stack container to retrieve size from.
 *
 * @return Return the current size of self.
 */
size_t stack_size(stack_t* const self) {
    if (!stack_status(self)) {
        return 0;
    }
    return self->size;
}
////////////////
// Operations //
////////////////
/**
 * @brief Remove all elements from a stack container.
 *
 * @param self Stack container whose elements are going to be removed.
 */
void stack_clear(stack_t* const self) {
    if (!stack_status(self)) {
        return;
    }
    const size_t self_size = self->size;
    for (size_t i = 0; i < self_size; ++i) {
        stack_pop(self);
    }
}
/**
 * @brief Copy the content from a stack container to another one.
 *
 * @param dst Stack container that will recieve the copied elements.
 * @param src Stack container whose elements will be copied.
 * 
 * @return Return dst containing a copy of all elements in src.
 */
stack_t* stack_copy(stack_t* dst, stack_t* const src) {
    if (!stack_status(src)) {
        return NULL;
    }
    if (!dst) {
        dst = stack_init(src->elements_size);
        if (!dst) {
            return NULL;
        }
    }
    else {
        stack_clear(dst);
    }
    stack_node* bottom = src->top;
    size_t it = src->size;
    for (size_t i = 0; i < src->size; ++i) {
        it -= i;
        while (it > 1) {
            bottom = bottom->next;
            --it;
        }
        stack_push(dst, bottom->element, src->elements_size);
        bottom = src->top;
        it = src->size;
    }
    return dst;
}
/**
 * @brief Move the content from a stack container to another one.
 * 
 * @param dst Stack container that will hold the content in another stack container.
 * @param src Stack container that will be moved onto another stack container.
 * 
 * @return Return dst containing the content that existed in src before been deleted.
 */
stack_t* stack_move(stack_t* const dst, stack_t* const src) {
    if (!stack_status(src)) {
        return NULL;
    }
    stack_t* temp = stack_copy(dst, src);
    if (!temp) {
        return NULL;
    }
    stack_destroy(src);
    return temp;
}
/**
 * @brief Remove the element at the top of a stack container.
 * 
 * @param self Stack container whose top element will be removed.
 */
void stack_pop(stack_t* const self) {
    if (!stack_status(self)) {
        return;
    }
    if (self->size == 1) {
        self->size--;
        free(self->top);
        self->top = NULL;
        return;
    }
    self->size--;
    stack_node* current_node = self->top;
    self->top = self->top->next;
    free(current_node);
}
/**
 * @brief Add an element to the top of a stack container.
 * 
 * @param self Stack container that will hold the element.
 * @param element Element to be added to stack's top.
 * @param element_size Element size that will be added.
 */
void stack_push(stack_t* const self, void* const element, const size_t element_size) {
    if (!self || (self->elements_size > 1 && element_size != self->elements_size) || self->size == UINT64_MAX) {
        return;
    }
    if (!self->size) {
        self->top = malloc(sizeof(stack_node));
        if (!self->top) {
            return;
        }
        self->top->element = element;
        self->top->next = NULL;
    }
    else {
        stack_node* new_node = malloc(sizeof(stack_node));
        if (!new_node) {
            return;
        }
        new_node->element = element;
        new_node->next = self->top;
        self->top = new_node;
    }
    self->size++;
}
/**
 * @brief Swap the content of two stack containers.
 *
 * @param dst Stack container that will hold the swapped content.
 * @param src Stack container whose content will be swapped.
 */
void stack_swap(stack_t* const dst, stack_t* const src) {
    if (!stack_status(dst) || !stack_status(src)) {
        return;
    }
    stack_t temp = *dst;
    *dst = *src;
    *src = temp;
}
