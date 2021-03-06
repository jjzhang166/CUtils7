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
#include <string.h> // strncat, strncmp, strstr
#include "str.h"

#define _MALLOC_(string, size, r_value) \
    malloc(size);                       \
    if (!string) {                      \
        return r_value;                 \
    }                                   \
    char_clear(string, size);

#ifndef _CHAR_H
static void char_clear(char *self, const size_t self_size) {
    if (!self) {
        return;
    }
    for (size_t i = 0; i < self_size; ++i) {
        self[i] = '\0';
    }
}

static char* char_copy(char* dst, const char* src, const size_t char_count) {
    if (!src) {
        return NULL;
    }
    if (!dst) {
        dst = _MALLOC_(dst, char_count + 1, NULL);
    }
    else {
        char_clear(dst, char_count);
    }
    for (size_t i = 0; i < char_count; ++i) {
        dst[i] = src[i];
    }
    return dst;
}

static char* char_join(char* dst, const char* src, const size_t char_count) {
    if (!src) {
        return NULL;
    }
    if (!dst) {
        dst = _MALLOC_(dst, char_count + 1, NULL);
    }
    size_t src_it = 0;
    for (size_t i = char_length(dst) - 1; i < char_count; ++i) {
        dst[i] = src[src_it++];
    }
    return dst;
}

static size_t char_length(const char* self) {
    if (!self) {
        return 0;
    }
    size_t length = 0;
    while (self[length] != '\0') {
        ++length;
    }
    return length;
}
#endif

static const float _GROWTH_FACTOR_ = 1.5f;
static const uint8_t _LETTER_CASE_FACTOR_ = 32;

struct _internal_string {
    char* content;
    size_t size;
};
/**
 * Check if a string and its content is not null.
 */
static bool string_status(string_t* const self) {
    return self && self->content;
}
///////////
// Basic //
///////////
/**
 * @brief Initialize a new string container.
 *
 * @param str Set a string into the new container. It might be a empty one ("") or straight NULL.
 * @param size Set a size to the new container. If its value is lesser than "str" size a new value
 * will be set being the former parameter size. If "str" is empty or NULL, the new string will hold the size given.
 *
 * @return A new string container.
 */
string_t* string_init(const char* const str, const size_t size) {
    string_t* init = malloc(sizeof(string_t));
    if (!init) {
        return NULL;
    }
    const size_t str_length = str ? char_length(str) : 0;
    if (str_length) {
        init->size = size < str_length + 1 ? (size_t)(str_length * _GROWTH_FACTOR_) : size;
        init->content = malloc(string_size(init));
        if (!string_data(init)) {
            free(init);
            return NULL;
        }
        char_clear(init->content, init->size);
        char_copy(string_data(init), str, str_length);
    }
    else {
        init->size = size ? size + 1 : 0;
        init->content = NULL;
    }
    return init;
}
/**
 * @brief Free the memory of a string content plus string itself.
 *
 * @param self The string to be freed.
 */
void string_destroy(string_t* const self) {
    if (!self) {
        return;
    }
    if (string_data(self)) {
        free(self->content);
    }
    free(self);
}
/*
 * Returns a string container size less null termination character.
 */
static size_t string_capacity(string_t* const self) {
    return self ? string_size(self) - 1 : 0;
}
/*
 * brief Returns the amount of not null characters in a string container.
 */
static size_t string_length_array(string_t* const self) {
    return string_status(self) ? (char_length(string_data(self)) - 1) : 0;
}
////////////
// Access //
////////////
/**
 * @brief Returns a character from a string container at given position.
 *
 * @param self String container to get character from.
 * @param pos Position at which get character from a string container. Start point is 0.
 *
 * @return Return a char from self at pos.
 */
char string_at(string_t* const self, const size_t pos) {
    return string_status(self) && pos <= string_capacity(self) ? self->content[pos] : '\0';
}
/**
 * @brief Return the last character in a string container.
 *
 * @param self String container to get last character from.
 *
 * @return Return the last char in self.
 */
char string_back(string_t* const self) {
    return string_status(self) ? string_at(self, string_length_array(self)) : '\0';
}
/**
 * @brief Return the content in a string container.
 *
 * @param self String container to get content from.
 *
 * @return Return a pointer to char with self content.
 */
char* string_data(string_t* const self) {
    return string_status(self) ? self->content : NULL;
}
/**
 * @brief Return the first character in a string container.
 *
 * @param self String container to get first character from.
 *
 * @return Return the first char in self.
 */
char string_front(string_t* const self) {
    return string_status(self) ? string_at(self, 0) : '\0';
}
/**
 * @brief Copy a string container content to a pointer to char.
 *
 * @param self          String container whose content will be copied.
 * @param array         Pointer to char which will recieve the copy from a string container.
 * @param array_size    Pointer to char size that will hold a vector container content.
 */
void string_to_array(string_t* const self, char* const array, const size_t array_size) {
    if (!string_status(self)) {
        return;
    }
    const size_t self_length = string_length(self);
    if (array_size >= self_length + 1) {
        char_copy(array, string_data(self), self_length);
    }
}
//////////////
// Capacity //
//////////////
/**
 * @brief Returns if a string container has any characters at all.
 *
 * @param self String container to check length from.
 *
 * @return Return true if self has 0 length.
 */
bool string_empty(string_t* const self) {
    return self ? string_length(self) == 0 : true;
}
/**
 * @brief Returns the amount of not null characters in a string container.
 *
 * @param self String container to get characters length from.
 *
 * @return Return the amount of not null characters in self. Start point is 1;
 */
size_t string_length(string_t* const self) {
    return string_status(self) ? char_length(string_data(self)) : 0;
}
/**
 * @brief Assign a new size to a string container.
 *
 * @param self String container to set size at.
 * @param size New size to be set. Unless it's lesser than current size.
 */
void string_reserve(string_t* const self, const size_t size) {
    if (!self || !size) {
        return;
    }
    if (size >= string_size(self)) {
        self->size = size;
        char* temp = realloc(string_data(self), string_size(self));
        if (!temp) {
            return;
        }
        self->content = temp;
        for (size_t i = string_length(self) + 1; i < string_size(self); ++i) {
            string_replace(self, "\0", i, 1);
        }
    }
}
/**
 * @brief Resize current string character length in a string container.
 *
 * @param self String container that will be changed.
 * @param size New size that will be use in a string container.
 */
void string_resize(string_t* const self, const size_t size) {
    if (!self || !size) {
        return;
    }
    const size_t count = size - string_capacity(self);
    if (size > string_capacity(self)) {
        string_reserve(self, size);
        const size_t end = string_length_array(self);
        char c = string_at(self, end);
        for (size_t i = 0; i < count; ++i) {
            self->content[end + i] = c;
        }
    }
    else {
        const size_t start = string_capacity(self) - (string_length(self) - size);
        string_erase(self, start, (string_capacity(self) - 1));
    }
}
/**
 * @brief Shrink a string container to fit just the characters and null terminator in it.
 *
 * @param self String container to shrink size.
 */
void string_shrink_to_fit(string_t* const self) {
    if (!self) {
        return;
    }
    const size_t self_length = string_length(self);
    if (self_length < self->size) {
        self->size -= string_size(self) - (self_length + 1);
        char* temp = realloc(string_data(self), string_size(self));
        if (!temp) {
            return;
        }
        self->content = temp;
    }
}
/**
 * @brief Returns the current size of a string container.
 *
 * @param self String container to retrieve size from.
 *
 * @return Return the current size of self.
 */
size_t string_size(string_t* const self) {
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
void string_append(string_t* const self, const char* str) {
    if (!self || !str) {
        return;
    }
    const size_t str_length = char_length(str);
    const size_t size = (size_t)(str_length * _GROWTH_FACTOR_);
    if (string_data(self)) {
        if (string_size(self) < size) {
            self->size += size;
            string_reserve(self, string_size(self));
        }
        strncat(string_data(self), str, str_length);
    }
    else {
        self->size = size;
        self->content = _MALLOC_(string_data(self), size,);
        strncat(string_data(self), str, str_length);
    }
}
/**
 * @brief Assign a new content to a string.
 *
 * @param self The string that will get new content.
 * @param str The new content to be assigned.
 */
void string_assign(string_t* const self, const char* const str) {
    if (!self) {
        return;
    }
    if (string_data(self)) {
        string_clear(self);
    }
    string_append(self, str);
}
/**
 * @brief Capitalize the first letter from a string container.
 * 
 * @param self String container whose first letter will be change.
 */
void string_capitalize(string_t* const self) {
    if (!string_status(self) || string_at(self, 0) < 'a' || string_at(self, 0) > 'z') {
        return;
    }
    self->content[0] -= _LETTER_CASE_FACTOR_;
}
/**
 * @brief Remove all characters from a string container.
 *
 * @param self String container whose characters are going to be removed.
 */
void string_clear(string_t* const self) {
    if (!string_status(self)) {
        return;
    }
    char_clear(string_data(self), string_length(self));
}
/**
 * @brief Copy the content from a string container to another one.
 *
 * @param dst String container that will recieve the copied characters.
 * @param src String container whose characters will be copied.
 * 
 * @return Return dst containing a copy of all elements in src.
 */
string_t* string_copy(string_t* dst, string_t* const src) {
    if (!string_status(src)) {
        return NULL;
    }
    if (!dst) {
        dst = string_init(NULL, src->size);
        if (!dst) {
            return NULL;
        }
    }
    else {
        string_clear(dst);
    }
    string_append(dst, string_data(src));
    return dst;
}
/**
 * @brief Remove a characters amount from a string container.
 *
 * @param self String container whose characters will be erased.
 * @param start Start position from which will the erase begin.
 * @param end End position at which the erase will stop.
 */
void string_erase(string_t* const self, const size_t start, const size_t end) {
    if (!string_status(self) || start > string_length_array(self) || end >= string_length(self)) {
        return;
    }
    char* buffer = _MALLOC_(buffer, string_size(self),);
    char_copy(buffer, string_data(self), string_size(self));
    string_clear(self);
    size_t i = 0;
    size_t self_it = 0;
    for (; i < start; i++) {
        self->content[self_it++] = buffer[i];
    }
    const size_t _end = end + 1;
    for (i = _end; i < string_capacity(self); ++i) {
        self->content[self_it++] = buffer[i];
    }
    free(buffer);
}
/**
 * @brief Turn '\t' command in a string container content into spaces.
 * 
 * @param self String container content to look it.
 * @param tab_size How many spaces will replace '\t' command. By default it's 4 spaces.
 * 
 * @result Return a string container with spaces instead of '\t' commands.
 */
void string_expand_tabs(string_t* const self, const size_t tab_size) {
    if (!string_status(self)) {
        return;
    }
    size_t _tab_size = tab_size;
    if (!_tab_size) {
        _tab_size = 4;
    }
    const size_t tab_count = string_count(self, "\t", 0, string_length_array(self));
    const size_t new_size = (string_length(self) + (_tab_size * tab_count)) + 1;
    if (string_size(self) < new_size) {
        const size_t self_size = (size_t)(new_size * _GROWTH_FACTOR_);
        string_reserve(self, self_size);
    }
    if (tab_count == 1) {
        const size_t tab_pos = string_find(self, "\t", 0);
        string_erase(self, tab_pos, tab_pos);
        char* buffer = _MALLOC_(buffer, (_tab_size + 1),);
        for (size_t i = 0; i < _tab_size; ++i) {
            buffer[i] = ' ';
        }
        string_insert(self, buffer, tab_pos);
        free(buffer);
    }
    else {
        char* buffer = _MALLOC_(buffer, new_size,);
        string_to_array(self, buffer, new_size);
        string_clear(self);
        size_t buffer_it = 0;
        for (size_t i = 0; buffer[buffer_it] != '\0'; ++i, ++buffer_it) {
            if (buffer[buffer_it] == '\t') {
                for (size_t j = 0; j < _tab_size; ++j) {
                    string_push_back(self, ' ');
                }
                i += tab_count;
            }
            else {
                string_push_back(self, buffer[buffer_it]);
            }
        }
        free(buffer);
    }
}
/**
 * @brief Insert a character amount into a string container.
 *
 * @param self String container which the insertion will occur.
 * @param str Characters to be inserted.
 * @param pos Position at which characters will be inserted.
 */
void string_insert(string_t* const self, const char* const str, const size_t pos) {
    if (!self || !str || pos > string_capacity(self)) {
        return;
    }
    char* buffer = _MALLOC_(buffer, string_size(self),);
    char_copy(buffer, string_data(self), string_size(self));
    if (string_length(self) == string_capacity(self)) {
        self->size = (size_t)(string_size(self) * _GROWTH_FACTOR_);
        string_reserve(self, string_size(self));
    }
    char_clear(string_data(self), string_size(self));
    size_t i;
    size_t buffer_it = 0;
    for (i = 0; i < pos; ++i) {
        string_push_back(self, buffer[buffer_it++]);
    }
    for (i = 0; i < char_length(str); ++i) {
        string_push_back(self, str[i]);
    }
    for (i = buffer_it; i <= char_length(buffer); ++i) {
        string_push_back(self, buffer[buffer_it++]);
    }
    free(buffer);
}
/**
 * @brief Join the content of two string containers.
 * 
 * @param dst String container that will be joined.
 * @param src String container that will join another one.
 */
void string_join(string_t* const dst, string_t* const src) {
    if (!string_status(dst) || !string_status(src)) {
        return;
    }
    string_append(dst, string_data(src));
}
/**
 * @brief Surround a string container content with a specify character.
 * 
 * @param self String container's content to be surrounded.
 * @param width How many times the character will be add to surround the string container's content.
 * @param fill What character is going to surround the string container's content.
*/
void string_justified(string_t* const self, const size_t width, const char fill) {
    if (!string_status(self) || !width || !fill) {
        return;
    }
    const size_t self_length = string_length(self);
    size_t _width = width;
    if ((self_length + _width) % 2 != 0) {
        _width++;
    }
    if (_width > string_size(self)) {
        const size_t new_size = (size_t)(_width * _GROWTH_FACTOR_);
        string_reserve(self, new_size);
    }
    const size_t fill_size = (_width - self_length) / 2;
    size_t fill_count = self_length + fill_size;
    string_justified_right(self, fill_count, fill);
    fill_count = string_length(self) + fill_size;
    string_justified_left(self, fill_count, fill);
}
/**
 * @brief Left justified a string container content.
 * 
 * @param self String container content to be justified.
 * @param width How many times a character will be add to the right.
 * @param fill Character that will fill the string to the right.
 */
void string_justified_left(string_t* const self, const size_t width, const char fill) {
    if (!string_status(self) || !width || !fill) {
        return;
    }
    const size_t fill_count = width - string_length(self);
    if (width > string_size(self)) {
        const size_t new_size = (size_t)(width * _GROWTH_FACTOR_);
        string_reserve(self, new_size);
    }
    for (size_t i = 0; i < fill_count; ++i) {
        string_push_back(self, fill);
    }
}
/**
 * @brief Right justified a string container content.
 * 
 * @param self String container content to be justified.
 * @param width How many times a character will be add to the left.
 * @param fill Character that will fill the string to the left.
 */
void string_justified_right(string_t* const self, const size_t width, const char fill) {
    if (!string_status(self) || !width || !fill) {
        return;
    }
    const size_t buffer_size = (width - string_length(self)) + 1;
    char* buffer = _MALLOC_(buffer, buffer_size,);
    for (size_t i = 0; i < (buffer_size - 1); ++i) {
        buffer[i] = fill;
    }
    if (width > string_size(self)) {
        const size_t new_size = (size_t)(width * _GROWTH_FACTOR_);
        string_reserve(self, new_size);
    }
    string_insert(self, buffer, 0);
    free(buffer);
}
/**
 * @brief Lower all content from a string container.
 * 
 * @param self String container content to be lowered.
 */
void string_lower_case(string_t* const self) {
    if (!string_status(self)) {
        return;
    }
    const size_t self_length = string_length(self);
    for (size_t i = 0; i < self_length; ++i) {
        if (string_at(self, i) >= 'A' && string_at(self, i) <= 'Z') {
            self->content[i] += _LETTER_CASE_FACTOR_;
        }
    }
}
/**
 * @brief Retrieve the greater character by it's value from string container content.
 * 
 * @param self String container content to get character from.
 * @param start Start position from which will start searching.
 * @param end End position at which the search will stop.
 * 
 * @return Return the greater character by it's value from self.
 */
char string_max_char(string_t* const self, const size_t start, const size_t end) {
    if (!string_status(self) || (start > string_length(self) || !end || (end > string_length(self)))) {
        return '\0';
    }
    char max_char = '\0';
    for (size_t i = start; i < end; ++i) {
        if (!i || max_char < string_at(self, i)) {
            max_char = string_at(self, i);
        }
    }
    return max_char;
}
/**
 * @brief Retrieve the lesser character by it's value from string container content.
 * 
 * @param self String container content to get character from.
 * @param start Start position from which will start searching.
 * @param end End position at which the search will stop.
 * 
 * @return Return the lesser character by it's value from self.
 */
char string_min_char(string_t* const self, const size_t start, const size_t end) {
    if (!string_status(self) || (start > string_length(self) || !end || end > string_length(self))) {
        return '\0';
    }
    char min_char = '\0';
    for (size_t i = start; i < end; ++i) {
        if (!i || min_char > string_at(self, i)) {
            min_char = string_at(self, i);
        }
    }
    return min_char;
}
/**
 * @brief Move the content from a string container to another one.
 * 
 * @param dst String container that will hold the content in another string container.
 * @param src String container that will be moved onto another string container.
 * 
 * @return Return dst containing the content that existed in src before been deleted.
 */
string_t* string_move(string_t* dst, string_t* src) {
    if (!string_status(src)) {
        return NULL;
    }
    dst = src;
    src = NULL;
    return dst;
}
/**
 * @brief Remove last character in a string container.
 *
 * @param self String container whose last character will be removed.
 */
void string_pop_back(string_t* const self) {
    if (!string_status(self) || string_length(self) <= 1) {
        return;
    }
    string_replace(self, "\0", string_length_array(self), 1);
}
/**
 * @brief Push a character at string container end.
 *
 * @param self String container that will hold the new character.
 * @param c Character to be add.
 */
void string_push_back(string_t* const self, const char c) {
    if (!self || (!isprint(c) && !iscntrl(c))) {
        return;
    }
    const char buffer[2] = { c, '\0' };
    if (string_data(self)) {
        if (string_length(self) == string_capacity(self)) {
            self->size = (size_t)(string_size(self) * _GROWTH_FACTOR_);
            string_reserve(self, string_size(self));
        }
        strncat(string_data(self), buffer, char_length(buffer));
    }
    else {
        self->size += 2;
        self->content = _MALLOC_(string_data(self), string_size(self),);
        char_copy(string_data(self), buffer, char_length(buffer));
    }
}
/**
 * @brief Repeat the content of a string container how many times requested.
 * 
 * @param self String container whose content will be repeated.
 * @param repetitions Times that a string container contents will be repeated.
 */
void string_repeat(string_t* const self, const size_t repetitions) {
    if (!string_status(self) || repetitions <= 1) {
        return;
    }
    const size_t self_length = string_length(self);
    const size_t buffer_size = self_length + 1;
    char* buffer = _MALLOC_(buffer, buffer_size,);
    string_to_array(self, buffer, buffer_size);
    const size_t needed_size = (self_length * repetitions) + 1;
    if (string_size(self) < needed_size) {
        const size_t new_size = (size_t)(needed_size * _GROWTH_FACTOR_);
        string_reserve(self, new_size);
    }
    for (size_t i = 0; i < repetitions; ++i) {
        string_append(self, buffer);
    }
    free(buffer);
}
/**
 * @brief Replace characters from a string container.
 *
 * @param self String container whose content will be replaced.
 * @param str String character that will replace the current content.
 * @param pos Position which the replacing will start.
 * @param count Character amount from str that will replace string content.
 */
void string_replace(string_t* const self, const char* const str, const size_t pos, int count) {
    if (!string_status(self) || !count || !str || pos > string_capacity(self)) {
        return;
    }
    if (count > 1) {
        for (size_t i = 0; i < count; ++i) {
            self->content[pos + i] = str[i];
        }
    }
    else {
        self->content[pos] = str[0];
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
string_t* string_slice(string_t* const self, const size_t start, const size_t end) {
    if (!string_status(self)) {
        return NULL;
    }
    const size_t size = (end - start) + 2;
    char* str = _MALLOC_(str, size, NULL);
    size_t str_it = 0;
    for (size_t i = start; i <= end; ++i) {
        str[str_it++] = string_at(self, i);
    }
    string_t* substr = string_init(str, char_length(str));
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
char* string_slice_array(string_t* const self, const size_t start, const size_t end) {
    if (!string_status(self) || !end) {
        return NULL;
    }
    const size_t size = (end - start) + 2;
    char* str = _MALLOC_(str, size, NULL);
    size_t str_it = 0;
    for (size_t i = start; i <= end; ++i) {
        str[str_it++] = string_at(self, i);
    }
    return str;
}
/**
 * @brief Swap the content of two string containers.
 *
 * @param dst String container that will hold the swapped content.
 * @param src String container whose content will be swapped.
 */
void string_swap(string_t* const dst, string_t* const src) {
    if (!string_status(dst) || !string_status(src)) {
        return;
    }
    string_t temp = *dst;
    *dst = *src;
    *src = temp;
}
/**
 * @brief Swap all content case from a string container.
 * 
 * @param self String container content to be swapped.
 */
void string_swap_case(string_t* const self) {
    if (!string_status(self)) {
        return;
    }
    const size_t self_length = string_length(self);
    for (size_t i = 0; i < self_length; ++i) {
        if (string_at(self, i) >= 'A' && string_at(self, i) <= 'Z') {
            self->content[i] += _LETTER_CASE_FACTOR_;
            continue;
        }
        if (string_at(self, i) >= 'a' && string_at(self, i) <= 'z') {
            self->content[i] -= _LETTER_CASE_FACTOR_;
            continue;
        }
    }
}
/**
 * @brief Capitalize the first letter of every word after a space in a string container.
 * 
 * @param self String container to be affected.
 */
void string_title(string_t* const self) {
    if (!string_status(self)) {
        return;
    }
    bool first_letter = false;
    string_lower_case(self);
    for (size_t i = 0; i < string_length(self); ++i) {
        if ((isalpha(string_at(self, i)) && !first_letter) || (isalpha(string_at(self, i)) && isspace(string_at(self, i - 1)))) {
            self->content[i] -= _LETTER_CASE_FACTOR_;
            first_letter = true;
        }
    }
}
/**
 * @brief Remove all appearance of a character in a string container.
 * 
 * @param self String container which will be trimmed.
 * @param remove Character to be removed.
 */
void string_trim(string_t* const self, const char remove) {
    if (!string_status(self) || !remove) {
        return;
    }
    string_trim_left(self, remove);
    string_trim_right(self, remove);
}
/**
 * @brief Remove all requested characters that repeat themselves continually at left from a string container contents.
 * 
 * @param self String container whose repeated characters will be removed.
 * @param remove Character to be removed how many times found in a continuous way.
 */
void string_trim_left(string_t* const self, const char remove) {
    if (!string_status(self) || !remove) {
        return;
    }
    size_t i = 0;
    for (; i < string_length(self); ++i) {
        if (string_at(self, i) != remove && string_at(self, i + 1) != remove) {
            break;
        }
    }
    string_erase(self, 0, --i);
}
/**
 * @brief Remove all requested characters that repeat themselves continually at right from a string container contents.
 * 
 * @param self String container whose repeated characters will be removed.
 * @param remove Character to be removed how many times found in a continuous way.
 */
void string_trim_right(string_t* const self, const char remove) {
    if (!string_status(self) || !remove) {
        return;
    }
    const size_t self_length = string_length_array(self);
    size_t i = self_length;
    for (; i > 0; --i) {
        if (string_at(self, i) != remove && string_at(self, i - 1) != remove) {
            break;
        }
    }
    string_erase(self, ++i, self_length);
}
/**
 * @brief Up all content from a string container.
 * 
 * @param self String container content to be capitalize.
 */
void string_upper_case(string_t* const self) {
    if (!string_status(self)) {
        return;
    }
    const size_t self_length = string_length(self);
    for (size_t i = 0; i < self_length; ++i) {
        if (string_at(self, i) >= 'a' && string_at(self, i) <= 'z') {
            self->content[i] -= _LETTER_CASE_FACTOR_;
        }
    }
}
////////////
// Search //
////////////
/*
 * Check if a string container is suitable to be searched.
 */
static bool string_searchable(string_t* const self, const char* const str, const size_t start) {
    return !string_status(self) || !str ||(char_length(str) < 1) || (start > string_length(self)) ? false : true;
}
/**
 * @brief Count how many times a given string is found in a string container.
 * 
 * @param self String container to look for the string to be counted.
 * @param start Start position to get content from.
 * @param end End position to get content from.
 */
size_t string_count(string_t* const self, const char* const str, const size_t start, const size_t end) {
    if (!string_searchable(self, str, start) || end >= string_length(self)) {
        return 0;
    }
    size_t counter = 0;
    size_t i = start;
    if (char_length(str) == 1) {
        for (; i <= end; ++i) {
            if (string_at(self, i) == str[0]) {
                counter++;
            }
        }
    }
    else {
        const size_t str_len = char_length(str);
        size_t j = 0;
        for (; i <= end; ++i) {
            if (string_at(self, i) == str[j]) {
                j++;
                if (j == (str_len - 1)) {
                    counter++;
                    j = 0;
                }
                continue;
            }
            j = 0;
        }
    }
    return counter;
}
/**
 * @brief Check if a string container content ends with a given string.
 * 
 * @param self String container to be checked.
 * @param str String to look for at the end of a string container.
 * 
 * @return True if self ends with str. False otherwise.
 */
bool string_end_with(string_t* const self, const char* const str, const size_t start, const size_t end) {
    if (!string_status(self) || !str) {
        return false;
    }
    if (char_length(str) == 1) {
        if (string_at(self, string_length_array(self)) == str[0]) {
            return true;
        }
    }
    else {
        size_t j = 0;
        bool match = false;
        for (size_t i = start; i <= end; ++i) {
            if (string_at(self, i) == str[j++]) {
                match = true;
                continue;
            }
            j = 0;
            match = false;
        }
        return match;
    }
    return false;
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
size_t string_find(string_t* const self, const char* const str, const size_t start) {
    if (!string_searchable(self, str, start)) {
        return 0;
    }
    const size_t str_length = char_length(str);
    size_t pos_start = 0;
    size_t i = start;
    size_t j = 0;
    const size_t end = string_length_array(self);
    bool match = false;
    for (; i <= end; ++i) {
        if (string_at(self, i) == str[j]) {
            if (!match) {
                pos_start = i;
            }
            match = true;
            if (str_length == 1 || str[j + 1] == '\0') {
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
char* string_find_array(string_t* const self, const char* const str, const size_t start)
{
    if (!string_searchable(self, str, start)) {
        return NULL;
    }
    char* substr = start ? string_slice_array(self, start, string_length_array(self)) : NULL;
    const char* buffer = start ? strstr(substr, str) : strstr(string_data(self), str);
    if (!buffer) {
        if (substr){
           free(substr);
        }
        return NULL;
    }
    const size_t buffer_len = char_length(buffer);
    const size_t size = buffer_len + 1;
    char* str_final = malloc(size);
    if (!str_final) {
        if (substr){
            free(substr);
        }
        return NULL;
    }
    char_clear(str_final, size);
    char_copy(str_final, buffer, buffer_len);
    if (substr){
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
size_t string_rfind(string_t* const self, const char* const str, const size_t start)
{
    if (!string_searchable(self, str, start)) {
        return 0;
    }
    size_t pos_start = 0;
    size_t i = string_length_array(self);
    const size_t j_start = char_length(str) - 1;
    size_t j = j_start;
    size_t end = (start - 1);
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
            j = j_start;
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
char* string_rfind_array(string_t* const self, const char* const str, const size_t start)
{
    if (!string_searchable(self, str, start)) {
        return NULL;
    }
    const size_t pos_start = string_rfind(self, str, start);
    return string_find_array(self, str, pos_start);
}
/*
 * Search algorithm to find a specific character inside a string container.
 */
static size_t string_search_of(string_t* const self, const char* str, const size_t pos, const int at, const int search_of_type)
{
    if (!string_status(self) || !str || pos > string_length_array(self) || at < 0) {
        return 0;
    }
    size_t match = 0;
    if (char_length(str) == 1) {
        match = !search_of_type ? string_find(self, (void*)&str[0], pos) : string_rfind(self, (void*)&str[0], pos);
        return match;
    }
    if (!at) {
        char buffer[2] = "\0";
        size_t pos_start = 0;
        match = string_length_array(self);
        const size_t str_length = char_length(str);
        for (size_t i = 0; i < str_length; ++i) {
            pos_start = !search_of_type ? string_find(self, (void*)&str[i], pos) : string_rfind(self, (void*)&str[i], pos);
            if (pos_start < match) {
                buffer[0] = str[i];
                match = !search_of_type ? string_find(self, buffer, pos) : string_rfind(self, buffer, pos);
            }
        }
    }
    else {
        match = !search_of_type ? string_find(self, (void*)&str[at - 1], pos) : string_rfind(self, (void*)&str[at - 1], pos);
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
size_t string_find_first_of(string_t* const self, const char* const str, const size_t pos, const int at) {
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
size_t string_find_last_of(string_t* const self, const char* const str, const size_t pos, const int at) {
    return string_search_of(self, str, pos, at, 1);
}
/*
 * Search algorithm to find a non-specific character inside a string container.
 */
static size_t string_search_not_of(string_t* const self, const char* const str, const size_t pos, const int search_type)
{
    if (!string_status(self) || !str || pos > string_length_array(self)) {
        return 0;
    }
    size_t match = -1;
    int c = 0;
    for (size_t i = !search_type ? 0 : string_length_array(self); !search_type ? i < string_length(self) : i > 0; !search_type ? ++i : --i) {
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
size_t string_find_first_not_of(string_t* const self, const char* const str, const size_t pos) {
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
size_t string_find_last_not_of(string_t* const self, const char* const str, const size_t pos) {
    return string_search_not_of(self, str, pos, 1);
}
/**
 * @brief Check if a string container content a given string.
 * 
 * @param self String container contents to be searched.
 * @param str String to search for in a string container.
 * 
 * @return Return true if str is found in self. False otherwise.
 */
bool string_includes(string_t* const self, const char* const str) {
    if (!string_status(self) || !str) {
        return false;
    }
    return strstr(string_data(self), str) ? true : false;
}
/**
 * @brief Check if a string container content starts with a given string.
 * 
 * @param self String container to be checked.
 * @param str String to look for at the start of a string container.
 * 
 * @return True if self starts with str. False otherwise.
 */
bool string_start_with(string_t* const self, const char* const str, const size_t start) {
    if (!string_status(self) || !str) {
        return false;
    }
    if (char_length(str) == 1) {
        if (string_at(self, 0) == str[0]) {
            return true;
        }
    }
    else {
        size_t j = 0;
        const size_t end = char_length(str) + start;
        bool match = false;
        for (size_t i = start; i < end; ++i) {
            if (string_at(self, i) == str[j++]) {
                match = true;
                continue;
            }
            match = false;
            break;
        }
        return match;
    }
    return false;
}
