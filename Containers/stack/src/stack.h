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
#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h> // bool
#include <stdint.h>  // Cross platform integer size

typedef struct _internal_stack stack_t;

///////////
// Basic //
///////////
stack_t*    stack_init(const size_t elements_size);
void        stack_destroy(stack_t* const self);
////////////
// Access //
////////////
bool        stack_is_empty(stack_t* const self);
void*       stack_top(stack_t* const self);
//////////////
// Capacity //
//////////////
size_t      stack_size(stack_t* const self);
/////////////////
// Operations //
////////////////
void        stack_clear(stack_t* const self);
stack_t*    stack_copy(stack_t* dst, stack_t* const src);
stack_t*    stack_move(stack_t* const dst, stack_t* const src);
void        stack_pop(stack_t* const self);
void        stack_push(stack_t* const self, void* const element, const size_t element_size);
void        stack_swap(stack_t* const dst, stack_t* const src);
#endif
