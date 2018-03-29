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

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _internal_vector vector_t;
///////////
// Basic //
///////////
vector_t*   vector_init(const size_t elements_size, const size_t elements_count);
void        vector_destroy(vector_t* const self);
////////////
// Access //
////////////
void*       vector_at(vector_t* const self, const size_t index);
void*       vector_back(vector_t* const self);
void*       vector_data(vector_t* const self);
void*       vector_front(vector_t* const self);
void        vector_to_array(vector_t* const self, void* const array, const size_t array_size);
//////////////
// Capacity //
//////////////
size_t      vector_capacity(vector_t* const self);
bool        vector_is_empty(vector_t* const self);
void        vector_reserve(vector_t* const self, const size_t size);
void        vector_resize(vector_t* const self, const size_t size, void* const element);
void        vector_shrink_to_fit(vector_t* const self);
size_t      vector_size(vector_t* const self);
/////////////////
// Operations //
////////////////
void        vector_assign(vector_t* const self, void* const element, const size_t element_size, const size_t element_count);
void        vector_clear(vector_t* const self);
vector_t*   vector_copy(vector_t* dst, vector_t* const src);
void        vector_erase(vector_t* const self, const size_t start, const size_t end);
void        vector_insert(vector_t* const self, void* const element, const size_t element_size, const size_t index);
vector_t*   vector_move(vector_t* dst, vector_t* src);
void        vector_pop_back(vector_t* const self);
void        vector_push_back(vector_t* const self, const void* const element, const size_t element_size);
void        vector_swap(vector_t* const dst, vector_t* const src);

#endif
