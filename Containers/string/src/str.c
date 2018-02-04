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
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING start,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ctype.h>  // isctrl, isprint
#include <stdlib.h> // malloc, NULL, realloc
#include <string.h> // strcmp, strlen, strncat, strncpy, strstr
#include "str.h"

#define _MALLOC_(string, size, r_value) \
    malloc(size);                       \
    if (!string) {                      \
        return r_value;                 \
    }                                   \
    memset(string, '\0', size)

static const float _GROWTH_FACTOR_ = 1.5f;

struct _internal_string {
    char* content;
    _UINT_ size;
};
/*
* Check if a string and its content is not null.
*/
static bool string_status(string self) {
    return self && self->content;
}
//|||||||||
// Basic ||
//|||||||||
/**
* @brief Assign a new content to a string.
*
* @param self The string that will get new content.
* @param str The new content to be assigned.
*
*/
void string_assign(string self, const char* str) {
    if (!self) {
        return;
    }
    if (string_data(self)) {
        string_clear(self);
    }
    string_append(self, str);
}
/**
* @brief Initialize a new string container.
*
* @param str Set a string into the new container. It might be a empty one ("") or straight NULL.
* @param size Set a size to the new container. If its value is lesser than "str" size a new value
* will be set being the former parameter size. If "str" is empty or NULL, the new string will hold the size given.
*
* @return A new string container.
*/
string string_init(const char* str, _UINT_ size) {
    string const init = malloc(sizeof(struct _internal_string));
    if (!init) {
        return NULL;
    }
    if (str && strlen(str)) {
        init->size = size < (strlen(str) + 1) ?(_UINT_)(strlen(str) * _GROWTH_FACTOR_) : size;
        init->content = _MALLOC_(string_data(init), string_size(init), NULL);
        strncpy(string_data(init), str, strlen(str));
    }
    else {
        init->size = size ? (size + 1) : 0;
        init->content = NULL;
    }
    return init;
}
/**
* @brief Free the memory of a structure content plus structure itself.
*
* @param self The structure to be freed.
*/
void string_destroy(string self) {
    if (!self) {
        return;
    }
    if (string_data(self)) {
        free(self->content);
    }
    free(self);
}
//||||||||||
// Access ||
//||||||||||
/**
* @brief Returns a character from a string container at given position.
*
* @param self String container to get character from.
* @param pos Position at which get character from a string container. Start point is 0.
*
* @return Return a char from self at pos.
*/
char string_at(string self, _UINT_ pos) {
    return (string_status(self) && (pos <= string_capacity(self))) ? self->content[pos] : '\0';
}
/**
* @brief Return the last character in a string container.
*
* @param self String container to get last character from.
*
* @return Return the last char in self.
*/
char string_back(string self) {
    return string_status(self) ? string_at(self,string_length_raw(self)) : '\0';
}
/**
* @brief Return the content in a string container.
*
* @param self String container to get content from.
*
* @return Return a pointer to char with self content.
*/
char* string_data(string self) {
    return string_status(self) ? self->content : NULL;
}
/**
* @brief Return the first character in a string container.
*
* @param self String container to get first character from.
*
* @return Return the first char in self.
*/
char string_front(string self) {
    return string_status(self) ? string_at(self, 0) : '\0';
}
/**
* @brief Copy a string container content to a pointer to char.
*
* @param self String container whose content will be copied.
* @param array Pointer to char which will recieve the copy from a string container.
*/
void string_to_array(string self, char* array) {
    if (!string_status(self)) {
        return;
    }
    memcpy(array, string_data(self), string_size(self));
}
//////////////
// Capacity //
//////////////
/**
* @brief Returns a string container size less null termination character.
*
* @param self String container to get capacity from.
*
* @return Return the size of self less one; which is the null terminator.
*/
_UINT_ string_capacity(string self) {
    return self ? (string_size(self) - 1) : 0;
}
/**
* @brief Returns if a string container has any characters at all.
*
* @param self String container to check length from.
*
* @return Return true if self has 0 length.
*/
bool string_empty(string self) {
    return self ? string_length(self) == 0 : true;
}
/**
* @brief Returns the amount of not null characters in a string container.
*
* @param self String container to get characters length from.
*
* @return Return the amount of not null characters in self. Start point is 1;
*/
_UINT_ string_length(string self) {
    return string_status(self) ? strlen(string_data(self)) : 0;
}
/**
* @brief Returns the amount of not null characters in a string container.
*
* @param self String container to get characters length from.
*
* @return Return the amount of not null characters in self. Start point is 0;
*/
_UINT_ string_length_raw(string self) {
    return string_status(self) ? (strlen(string_data(self)) - 1) : 0;
}
/**
* @brief Assign a new size to a string container.
*
* @param self String container to set size at.
* @param size New size to be set. Unless it's lesser than current size.
*/
void string_reserve(string self, _UINT_ size) {
    if (!self && !size) {
        return;
    }
    if (size >= string_size(self)) {
        self->size = size;
        char* temp = realloc(string_data(self), string_size(self));
        if (!temp) {
            return;
        }
        self->content = temp;
        for (_UINT_ i = (string_length(self) + 1); i < string_size(self); ++i) {
            string_replace(self, "\0", i, 1);
        }
    }
}
/**
* @brief Shrink a string container to fit just the characters and null terminator in it.
*
* @param self String container to shrink size.
*/
void string_shrink_to_fit(string self) {
    if (!self) {
        return;
    }
    if (strlen(self->content) < self->size) {
        const _UINT_ size = (string_size(self) - (string_length(self) + 1));
        self->size -= size;
        char* temp = realloc(string_data(self), string_size(self));
        if (!temp) {
            return;
        }
        self->content = realloc(temp, string_size(self));
        if (!string_data(self)) {
            return;
        }
    }
}
/**
* @brief Returns the current size of a string container.
*
* @param self String container to retrieve size from.
*
* @return Return the current size of self.
*/
_UINT_ string_size(string self) {
    return self ? self->size : 0;
}
////////////////
// Operations //
////////////////
/**
* @brief Appends a string character into a string container.
*
* @param self String container which will hold the string character.
* @param str String character to be insert into a string container.
*/
void string_append(string self, const char* str) {
    if (!self && !str) {
        return;
    }
    const _UINT_ size = (_UINT_)(strlen(str) * _GROWTH_FACTOR_);
    if (string_data(self)) {
        if (string_size(self) < size) {
            self->size += size;
            string_reserve(self, string_size(self));
        }
        strncat(string_data(self), str, strlen(str));
    }
    else {
        self->size = size;
        self->content = _MALLOC_(string_data(self), size,);
        strncat(string_data(self), str, strlen(str));
    }
}
/**
* @brief Remove all characters from a string container.
*
* @param self String container whose characters are going to be removed.
*/
void string_clear(string self) {
    if (!string_status(self)) {
        return;
    }
    memset(string_data(self), '\0', string_size(self));
}
/**
* @brief Copy the content from a string container to another one.
*
* @param dst String container that will recieve the copied characters.
* @param src String container whose characters will be copied.
*/
void string_copy(string dst, string src) {
    if (!string_status(dst) && !string_status(src)) {
        return;
    }
    if (string_size(dst) < string_size(src)) {
        string_reserve(dst, string_size(src));
    }
    string_clear(dst);
    strncpy(string_data(dst), string_data(src), string_size(dst));
}
/**
* @brief Compare two string container content.
*
* @param dst String container that will be compare.
* @param src String container that will compare.
*
/ @return Return -1 if dst appear before src. 0 if the both are equal. 1 if dst appear after src.
*/
int string_compare(string dst, string src) {
    return strncmp(string_data(dst), string_data(src), string_length(src));
}
/**
* @brief Remove a characters amount from a string container.
*
* @param self String container whose characters will be erased.
* @param start Start position from which will the erase begin.
* @param end End position at which the erase will stop.
*/
void string_erase(string self, _UINT_ start, _UINT_ end) {
    if (!string_status(self) && (start > string_length_raw(self)) && (end >= string_length(self))) {
        return;
    }
    char* buffer = _MALLOC_(buffer, string_size(self),);
    strncpy(buffer, string_data(self), string_size(self));
    string_clear(self);
    _UINT_ i = 0;
    _UINT_ self_it = 0;
    for (; i < start; i++) {
        self->content[self_it++] = buffer[i];
    }
    for (i = ++end; i < string_capacity(self); ++i) {
        self->content[self_it++] = buffer[i];
    }
    free(buffer);
}
/**
* @brief Insert a character amount into a string container.
*
* @param self String container which the insertion will occur.
* @param str Characters to be inserted.
* @param pos Position at which characters will be inserted.
*/
void string_insert(string self, const char* str, _UINT_ pos) {
    if (!self && !str && (pos > string_capacity(self))) {
        return;
    }
    char* buffer = _MALLOC_(buffer, string_size(self),);
    strncpy(buffer, string_data(self), string_size(self));
    if (string_length(self) == string_capacity(self)) {
        self->size = (_UINT_)(string_size(self) * _GROWTH_FACTOR_);
        string_reserve(self, string_size(self));
    }
    string_clear(self);
    _UINT_ i;
    _UINT_ buffer_it = 0;
    for (i = 0; i < pos; ++i) {
        string_push_back(self, buffer[buffer_it++]);
    }
    for (i = 0; i < strlen(str); ++i) {
        string_push_back(self, str[i]);
    }
    for (i = buffer_it; i <= strlen(buffer); ++i) {
        string_push_back(self, buffer[buffer_it++]);
    }
    free(buffer);
}
/**
* @brief Remove last character in a string container.
*
* @param self String container whose last character will be removed.
*/
void string_pop_back(string self) {
    if (!string_status(self) && (string_length(self) <= 1)) {
        return;
    }
    string_replace(self, "\0", string_length_raw(self), 1);
}
/**
* @brief Push a character at string container end.
*
* @param self String container that will hold the new character.
* @param c Character to be add.
*/
void string_push_back(string self, const char c) {
    if (!self && (!isprint(c) || !iscntrl(c))) {
        return;
    }
    const char buffer[2] = { c, '\0' };
    if (string_data(self)) {
        if (string_length(self) == string_capacity(self)) {
            self->size = (_UINT_)(string_size(self) * _GROWTH_FACTOR_);
            string_reserve(self, string_size(self));
        }
        strncat(string_data(self), buffer, strlen(buffer));
    }
    else {
        self->size += 2;
        self->content = _MALLOC_(string_data(self), string_size(self),);
        strncpy(string_data(self), buffer, strlen(buffer));
    }
}
/**
* @brief Replace characters from a string container.
*
* @param self String container whose content will be replaced.
* @param str String character that will replace the current content.
* @param pos Position which the replacing will start.
* @param count Character amount from str that will replace string content.
*/
void string_replace(string self, const char* str, _UINT_ pos, int count) {
    if (!string_status(self) && !count && !str && (pos > string_capacity(self))) {
        return;
    }
    if (count > 1) {
        for (_UINT_ i = 0; i < count; ++i) {
            self->content[pos + i] = str[i];
        }
    }
    else {
        self->content[pos] = str[0];
    }
}
/**
* @brief Resize current string character length in a string container.
*
* @param self String container that will be changed.
* @param size New size that will be use in a string container.
*/
void string_resize(string self, _UINT_ size) {
    if (!self && !size) {
        return;
    }
    const _UINT_ count = (size - string_capacity(self));
    if (size > string_capacity(self)) {
        char c = string_at(self, (string_length(self) - 1));
        for (_UINT_ i = 0; i < count; ++i) {
            string_push_back(self, c);
        }
    }
    else {
        const _UINT_ start = (string_capacity(self) - (string_length(self) - size));
        string_erase(self, start, (string_capacity(self) - 1));
    }
}
/**
* @brief Get partial or complete content from a string container.
*
* @param self String container to get content from.
* @param start Start position to get content from.
* @param end End position to get content from.
*
* @return Return a string container holding the content requested from self.
*/
string string_substr(string self, _UINT_ start, _UINT_ end) {
    if (!string_status(self)) {
        return NULL;
    }
    const _UINT_ size = ((end - start) + 2);
    char* str = _MALLOC_(str, size, NULL);
    _UINT_ str_it = 0;
    for (_UINT_ i = start; i <= end; ++i) {
        str[str_it++] = string_at(self, i);
    }
    string substr = string_init(str, strlen(str));
    free(str);
    return substr;
}
/**
* @brief Get partial or complete content from a string container.
*
* @param self String container to get content from.
* @param start Start position to get content from.
* @param end End position to get content from.
*
* @return Return a pointer to char holding the content requested from self.
*/
char* string_substr_raw(string self, _UINT_ start, _UINT_ end) {
    if (!string_status(self) || !end) {
        return NULL;
    }
    const _UINT_ size = (end - start) + 2;
    char* str = _MALLOC_(str, size, NULL);
    _UINT_ str_it = 0;
    for (_UINT_ i = start; i <= end; ++i) {
        str[str_it++] = string_at(self, i);
    }
    return str;
}
/**
* @brief Swap the content of two string containers.
*
* @param dst String container the will hold the swapped content.
* @param src String container whose content will be swapped.
*/
void string_swap(string dst, string src) {
    if (!string_status(dst) && !string_status(src)) {
        return;
    }
    string str = string_init(string_data(dst), string_size(dst));
    dst->size = string_size(src);
    string_reserve(dst, string_size(src));
    string_copy(dst, src);
    src->size = string_size(str);
    string_reserve(src, string_size(str));
    string_copy(src, str);
    string_destroy(str);
}
////////////
// Search //
////////////
/*
* Check if a string container is suitable to be searched.
*/
static bool string_searchable(string self, const char* string, _UINT_ start) {
    return !string_status(self) || !string ||(strlen(string) < 1) || (start > string_length(self)) ? false : true;
}
/**
* @brief Search a string character in a string container.
*
* @param self String container to be searched.
* @param str String character to be searched in a string container.
* @param start Start position to lookup.
*
* @return Return first str match in self.
*/
_UINT_ string_find(string self, const char* str, _UINT_ start) {
    if (!string_searchable(self, str, start)) {
        return 0;
    }
    _UINT_ pos_start = 0;
    _UINT_ i = start;
    _UINT_ j = 0;
    const _UINT_ end = string_length_raw(self);
    bool match = false;
    for (; i <= end; ++i) {
        if (string_at(self, i) == str[j]) {
            if (!match) {
                pos_start = i;
            }
            match = true;
            if (strlen(str) == 1 || str[j + 1] == '\0') {
                break;
            }
            else {
                ++j;
                continue;
            }
        }
        if (match) {
            j = 0;
            pos_start = 0;
            match = false;
        }
    }
    return pos_start;
}
/**
* @brief Search a string character in a string container.
*
* @param self String container to be searched.
* @param str String character to be searched in a string container.
* @param start Start position to lookup.
*
* @return Return a pointer to chr at first str match.
*/
char* string_find_raw(string self, const char* str, _UINT_ start)
{
    if (!string_searchable(self, str, start)) {
        return NULL;
    }
    char* substr = start ? string_substr_raw(self, start, string_length_raw(self)) : NULL;
    const char* buffer = start ? strstr(substr, str) : strstr(string_data(self), str);
    if (!buffer) {
        free(substr);
        return NULL;
    }
    const int size = strlen(buffer) + 1;
    char* str_final = _MALLOC_(str_final, size, NULL);
    strncpy(str_final, buffer, strlen(buffer));
    if (start){
        free(substr);
    }
    return str_final;
}
/**
* @brief Search backwards a string character in a string container.
*
* @param self String container to be searched.
* @param str String character to be searched in a string container.
* @param start Start position to lookup.
*
* @return Return last str match in self.
*/
_UINT_ string_rfind(string self, const char* str, _UINT_ start)
{
    if (!string_searchable(self, str, start)) {
        return 0;
    }
    _UINT_ pos_start = 0;
    _UINT_ i = string_length_raw(self);
    _UINT_ j = (strlen(str) - 1);
    _UINT_ end = (start - 1);
    if (end > i) {
        end = 0;
    }
    bool match = false;
    for (; i >= end; --i) {
        if (string_at(self, i) == str[j]) {
            match = true;
            if (!j) {
                pos_start = i;
                break;
            }
            else {
                --j;
                continue;
            }
        }
        if (match) {
            j = (strlen(str) - 1);
            match = false;
        }
    }
    return pos_start;
}
/**
* @brief Search backwards a string character in a string container.
*
* @param self String container to be searched.
* @param str String character to be searched in a string container.
* @param start Start position to lookup.
*
* @return Return a pointer to chr at last str match.
*/
char* string_rfind_raw(string self, const char* str, _UINT_ start)
{
    if (!string_searchable(self, str, start)) {
        return NULL;
    }
    _UINT_ pos_start = string_rfind(self, str, start);
    return string_find_raw(self, str, pos_start);
}
/*
* Search algorithm to find a specific character inside a string container.
*/
static _UINT_ string_search_of(string self, const char* str, _UINT_ pos, int at, int search_of_type)
{
    if (!string_status(self) || !str || (pos < 0) || (at < 0)) {
        return 0;
    }
    _UINT_ match = -1;
    if (strlen(str) == 1) {
        match = !search_of_type ? string_find(self, (void*)&str[0], pos) : string_rfind(self, (void*)&str[0], pos);
        return match;
    }
    if (!at) {
        char buffer[2] = "\0";
        _UINT_ pos_start = 0;
        match = string_length_raw(self);
        for (_UINT_ i = 0; i < strlen(str); ++i) {
            pos_start = !search_of_type ? string_find(self, (void*)&str[i], pos) : string_rfind(self, (void*)&str[i], pos);
            if (pos_start < match) {
                buffer[0] = str[i];
                match = !search_of_type ? string_find(self, buffer, pos) : string_rfind(self, buffer, pos);
            }
        }
    }
    else {
        match = !search_of_type ? string_find(self, (void*)&str[(at - 1)], pos) : string_rfind(self, (void*)&str[(at - 1)], pos);
    }
    return match;
}
/**
* @brief Find a character in a strong container.
*
* @param self String container to be searched.
* @param str String character holding the character to be searched.
* @param pos Start position in a string container to lookup.
* @param at Character in a string character to look for in a string container.
*
* @return Return first str match in self.
*/
_UINT_ string_find_first_of(string self, const char* str, _UINT_ pos, int at) {
    return string_search_of(self, str, pos, at, 0);
}

/**
* @brief Find last character in a strong container.
*
* @param self String container to be searched.
* @param str String character holding the character to be searched.
* @param pos Start position in a string container to lookup.
* @param at Character in a string character to look for in a string container.
*
* @return Return last str match in self.
*/
_UINT_ string_find_last_of(string self, const char* str, _UINT_ pos, int at) {
    return string_search_of(self, str, pos, at, 1);
}
/*
* Search algorithm to find a non-specific character inside a string container.
*/
static _UINT_ string_search_not_of(string self, const char* str, _UINT_ pos, int search_type)
{
    if (!string_status(self) || !str || (pos < 0)) {
        return 0;
    }
    _UINT_ match = -1;
    int c = 0;
    for (_UINT_ i = !search_type ? 0 : string_length_raw(self); !search_type ? i < string_length(self) : i >= 0; !search_type ? ++i : --i) {
        c = (uint8_t)string_at(self, i);
        if (!search_type ? !strchr(str, c) : !strrchr(str, c)) {
            match = i;
            break;
        }
    }
    return match;
}
/**
* @brief Find the first not given character in a string container.
*
* @param self String container to be searched.
* @param str String character to skip from a string container content.
* @param pos Start position to search for.
*
* @return Return first non str match in self.
*/
_UINT_ string_find_first_not_of(string self, const char* str, _UINT_ pos) {
    return string_search_not_of(self, str, pos, 0);
}
/**
* @brief Find the last not given character in a string container.
*
* @param self String container to be searched.
* @param str String character to skip from a string container content.
* @param pos Start position to search for.
*
* @return Return last non str match in self.
*/
_UINT_ string_find_last_not_of(string self, const char* str, _UINT_ pos) {
    return string_search_not_of(self, str, pos, 1);
}
