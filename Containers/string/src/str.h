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

#ifndef _STR_H
#define _STR_H

#include <stdbool.h> // bool
#include <stdint.h>  // Cross platform integer size

typedef struct _internal_string string_t;
///////////
// Basic //
///////////
string_t*   string_init(const char* const str, const size_t size);
void        string_destroy(string_t* const self);
////////////
// Access //
////////////
char        string_at(string_t* const self, const size_t pos);
char        string_back(string_t* const self);
char*       string_data(string_t* const self);
char        string_front(string_t* const self);
void        string_to_array(string_t* const self, char* const array, const size_t array_size);
//////////////
// Capacity //
//////////////
bool        string_empty(string_t* const self);
size_t      string_length(string_t* const self);
void        string_reserve(string_t* const self, const size_t size);
void        string_resize(string_t* const self, const size_t size);
void        string_shrink_to_fit(string_t* const self);
size_t      string_size(string_t* const self);
/////////////////
// Operations //
////////////////
void        string_append(string_t* const self, const char* string);
void        string_assign(string_t* const self, const char* const string);
void        string_capitalize(string_t* const self);
void        string_clear(string_t* const self);
string_t*   string_copy(string_t* dst, string_t* const src);
void        string_erase(string_t* const self, const size_t start, const size_t end);
void        string_expand_tabs(string_t* const self, const size_t tab_size);
void        string_insert(string_t* const self, const char* const str, const size_t pos);
void        string_join(string_t* const dst, string_t* const src);
void        string_justified(string_t* const self, const size_t width, const char fill);
void        string_justified_left(string_t* const self, const size_t width, const char fill);
void        string_justified_right(string_t* const self, const size_t width, const char fill);
void        string_lower_case(string_t* const self);
char        string_max_char(string_t* const self, const size_t start, const size_t end);
char        string_min_char(string_t* const self, const size_t start, const size_t end);
string_t*   string_move(string_t* dst, string_t* src);
void        string_pop_back(string_t* const self);
void        string_push_back(string_t* const self, const char c);
void        string_repeat(string_t* const self, const size_t repetitions);
void        string_replace(string_t* const self, const char* const string, const size_t pos, int count);
string_t*   string_slice(string_t* const self, const size_t start, const size_t end);
char*       string_slice_array(string_t* const self, const size_t start, const size_t end);
void        string_swap(string_t* const dst, string_t* const src);
void        string_swap_case(string_t* self);
void        string_title(string_t* const self);
void        string_trim(string_t* const self, const char remove);
void        string_trim_left(string_t* const self, const char remove);
void        string_trim_right(string_t* const self, const char remove);
void        string_upper_case(string_t* const self);
////////////
// Search //
////////////
size_t      string_count(string_t* const self, const char* const str, const size_t start, const size_t end);
bool        string_end_with(string_t* const self, const char* const str, const size_t start, const size_t end);
size_t      string_find(string_t* const self, const char* const string, const size_t start);
char*       string_find_array(string_t* const self, const char* const string, const size_t start);
size_t      string_rfind(string_t* const self, const char* const string, const size_t start);
char*       string_rfind_array(string_t* const self, const char* const string, const size_t start);
size_t      string_find_first_of(string_t* const self, const char* const string, const size_t pos, const int at);
size_t      string_find_first_not_of(string_t* const self, const char* const string, const size_t pos);
size_t      string_find_last_of(string_t* const self, const char* const string, const size_t pos, const int at);
size_t      string_find_last_not_of(string_t* const self, const char* const string, const size_t pos);
bool        string_includes(string_t* const self, const char* const str);
bool        string_start_with(string_t* const self, const char* const str, const size_t start);
#endif
