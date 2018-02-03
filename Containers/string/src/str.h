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

#ifndef STR_H
#define STR_H

#include <stdbool.h> // bool
#include <stdint.h>  // Cross platform integer size

typedef uint8_t _UINT_;

typedef struct _internal_string* string;

///////////
// Basic //
///////////
void string_assign(string self, const char* string);
string string_init(const char* str, _UINT_ size);
void string_destroy(string self);
////////////
// Access //
////////////
char string_at(string self, _UINT_ pos);
char string_back(string self);
char* string_data(string self);
char string_front(string self);
void string_to_array(string self, char* array);
//////////////
// Capacity //
//////////////
_UINT_ string_capacity(string self);
bool string_empty(string self);
_UINT_ string_length(string self);
_UINT_ string_length_raw(string self);
void string_reserve(string self, _UINT_ size);
void string_shrink_to_fit(string self);
_UINT_ string_size(string self);
/////////////////
// Operations //
////////////////
void string_append(string self, const char* string);
void string_clear(string self);
void string_copy(string dst, string src);
int string_compare(string dst, string src);
void string_erase(string self, _UINT_ start, _UINT_ end);
void string_insert(string self, const char* str, _UINT_ pos);
void string_pop_back(string self);
void string_push_back(string self, const char c);
void string_replace(string self, const char* string, _UINT_ pos, int count);
void string_resize(string self, _UINT_ size);
string string_substr(string self, _UINT_ start, _UINT_ end);
char* string_substr_raw(string self, _UINT_ start, _UINT_ end);
void string_swap(string dst, string src);
////////////
// Search //
////////////
_UINT_ string_find(string self, const char* string, _UINT_ start);
char* string_find_raw(string self, const char* string, _UINT_ start);
_UINT_ string_rfind(string self, const char* string, _UINT_ start);
char* string_rfind_raw(string self, const char* string, _UINT_ start);
_UINT_ string_find_first_of(string self, const char* string, _UINT_ pos, int at);
_UINT_ string_find_first_not_of(string self, const char* string, _UINT_ pos);
_UINT_ string_find_last_of(string self, const char* string, _UINT_ pos, int at);
_UINT_ string_find_last_not_of(string self, const char* string, _UINT_ pos);
#endif
