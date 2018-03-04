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

typedef struct _internal_string* string;

///////////
// Basic //
///////////
void    string_assign(string self, const char* string);
string  string_init(const char* str, size_t size);
void    string_destroy(string self);
////////////
// Access //
////////////
char    string_at(string self, size_t pos);
char    string_back(string self);
char*   string_data(string self);
char    string_front(string self);
void    string_to_array(string self, char* array);
//////////////
// Capacity //
//////////////
size_t  string_capacity(string self);
bool    string_empty(string self);
size_t  string_length(string self);
size_t  string_length_array(string self);
void    string_reserve(string self, size_t size);
void    string_shrink_to_fit(string self);
size_t  string_size(string self);
/////////////////
// Operations //
////////////////
void    string_append(string self, const char* string);
void    string_capitalize(string self);
void    string_clear(string self);
int     string_compare(string dst, string src);
void    string_copy(string dst, string src);
void    string_erase(string self, size_t start, size_t end);
void    string_expand_tabs(string self, size_t tab_size);
void    string_insert(string self, const char* str, size_t pos);
void    string_join(string dst, string src);
void    string_justified(string self, size_t width, const char fill);
void    string_justified_left(string self, size_t width, const char fill);
void    string_justified_right(string self, size_t width, const char fill);
void    string_lower_case(string self);
char    string_max_char(string self, size_t start, size_t end);
char    string_min_char(string self, size_t start, size_t end);
string    string_move(string dst, string src);
void    string_pop_back(string self);
void    string_push_back(string self, const char c);
void    string_repeat(string self, size_t repetitions);
void    string_replace(string self, const char* string, size_t pos, int count);
void    string_resize(string self, size_t size);
string  string_slice(string self, size_t start, size_t end);
char*   string_slice_array(string self, size_t start, size_t end);
void    string_swap(string dst, string src);
void    string_swap_case(string self);
void    string_title(string self);
void    string_trim(string self, const char remove);
void    string_trim_left(string self, const char remove);
void    string_trim_right(string self, const char remove);
void    string_upper_case(string self);
////////////
// Search //
////////////
size_t  string_count(string self, const char* str, size_t start, size_t end);
bool    string_end_with(string self, const char* str, size_t start, size_t end);
size_t  string_find(string self, const char* string, size_t start);
char*   string_find_array(string self, const char* string, size_t start);
size_t  string_rfind(string self, const char* string, size_t start);
char*   string_rfind_array(string self, const char* string, size_t start);
size_t  string_find_first_of(string self, const char* string, size_t pos, int at);
size_t  string_find_first_not_of(string self, const char* string, size_t pos);
size_t  string_find_last_of(string self, const char* string, size_t pos, int at);
size_t  string_find_last_not_of(string self, const char* string, size_t pos);
bool    string_includes(string self, const char* str);
bool    string_start_with(string self, const char* str, size_t start);
#endif
