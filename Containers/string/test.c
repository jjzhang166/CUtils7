/*
MIT License

Copyright (c) 2018 Joseph Ojeda

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the 41"Software"), to deal
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

#include <stdio.h>  // printf, puts
#include <stdlib.h> // malloc, NULL, EXIT_SUCCESS
#include <string.h> // strlen

#include "src/str.h"

#define STRING_INFO(str)                                            \
    printf("\t\t\tstring_size(%s) = %ld\n", #str, string_size(str)); \
    printf("\t\t\tstring_data(%s) = %s\n", #str, string_data(str))

int main(void)
{
    // Test
    puts("String container functions:");
    // string_init
    puts("\tstring string_init(char* str):");
    string str1 = string_init("Hey, you.", 0);
    puts("\t\tstring_init(\"Hey, you.\"):");
    STRING_INFO(str1);
    string str2 = string_init("", 0);
    puts("\t\tstring_init(\"\"):");
    STRING_INFO(str2);
    string str3 = string_init(NULL, 13);
    puts("\t\tstring_init(NULL):");
    STRING_INFO(str3);
    // string_empty
    puts("\n\tbool string_empty(string self):");
    printf("\t\tstring_empty(str1) = %d\n", string_empty(str1));
    printf("\t\tstring_empty(str2) = %d\n", string_empty(str2));
    printf("\t\tstring_empty(str3) = %d\n", string_empty(str3));
    // string_append
    puts("\n\tvoid string_append(string self, const char* string):");
    string_append(str1, " How are you?");
    puts("\t\tstring_append(str1, \" How are you?\"):");
    STRING_INFO(str1);
    string_append(str2, "who are you?");
    puts("\t\tstring_append(str2, \"who are you?\"):");
    STRING_INFO(str2);
    string_append(str3, "hello, world!");
    puts("\t\tstring_append(str3, \"hello, world!\"):");
    STRING_INFO(str3);
    // string_capitalize
    puts("\n\tvoid string_capitalize(string self):");
    string_capitalize(str1);
    puts("\t\tstring_capitalize(str1):");
    STRING_INFO(str1);
    string_capitalize(str2);
    puts("\t\tstring_capitalize(str2):");
    STRING_INFO(str2);
    string_capitalize(str3);
    puts("\t\tstring_capitalize(str3):");
    STRING_INFO(str3);
    // string_clear
    puts("\n\tvoid string_clear(string self):");
    string_clear(str1);
    puts("\t\tstring_clear(str1):");
    STRING_INFO(str1);
    string_clear(str2);
    puts("\t\tstring_clear(str2):");
    STRING_INFO(str2);
    string_clear(str3);
    puts("\t\tstring_clear(str3):");
    STRING_INFO(str3);
    // string_push_back
    puts("\n\tvoid string_push_back(string self, const char c):");
    char buffer1[8] = "Heyyou.";
    printf("\t\tbuffer1 = %s\n", buffer1);
    for (int i = 0; i < (int)strlen(buffer1); ++i)
    {
        string_push_back(str1, buffer1[i]);
        printf("\t\tstring_push_back(str1, buffer1[%d]):\n", i);
        STRING_INFO(str1);
    }
    char buffer2[9] = "are you?";
    printf("\t\tbuffer2 = %s\n", buffer2);
    for (int i = 0; i < (int)strlen(buffer2); ++i)
    {
        string_push_back(str2, buffer2[i]);
        printf("\t\tstring_push_back(str2, buffer2[%d]):\n", i);
        STRING_INFO(str2);
    }
    char buffer3[8] = "Hello, ";
    printf("\t\tbuffer3 = %s\n", buffer3);
    for (int i = 0; i < (int)strlen(buffer3); ++i)
    {
        string_push_back(str3, buffer3[i]);
        printf("\t\tstring_push_back(str3, buffer3[%d]):\n", i);
        STRING_INFO(str3);
    }
    // string_insert
    puts("\n\tvoid string_insert(string self, int pos, const char* string):");
    string_insert(str1, ", ", 3);
    puts("\t\tstring_insert(str1, \", \", 3):");
    STRING_INFO(str1);
    string_insert(str2, "How ", 0);
    puts("\t\tstring_insert(str2, \"How\", 3):");
    STRING_INFO(str2);
    string_insert(str3, "World!", 7);
    puts("\t\tstring_insert(str3, \"World!\", 3):");
    STRING_INFO(str3);
    // string_swap
    puts("\n\tvoid string_swap(string dst, string src):");
    string_swap(str2, str1);
    puts("\t\tstring_swap(str2, str1):");
    STRING_INFO(str1);
    STRING_INFO(str2);
    string_swap(str3, str2);
    puts("\n\t\tstring_swap(str3, str2):");
    STRING_INFO(str2);
    STRING_INFO(str3);
    // string_pop_back
    puts("\n\tvoid string_pop_back(string self):");
    string_pop_back(str1);
    puts("\t\tstring_pop_back(str1):");
    STRING_INFO(str1);
    string_pop_back(str2);
    puts("\t\tstring_pop_back(str2):");
    STRING_INFO(str2);
    string_pop_back(str3);
    puts("\t\tstring_pop_back(str3):");
    STRING_INFO(str3);
    // string_copy
    puts("\n\tvoid string_copy(string dst, string src):");
    string str4 = string_init("How are you, son?", 0);
    printf("\t\tstr4 = %s\n", string_data(str4));
    string_copy(str1, str4);
    puts("\t\tstring_copy(str1, str4):");
    STRING_INFO(str1);
    string str5 = string_init("Hello, sir.", 11);
    printf("\t\tstr5 = %s\n", string_data(str5));
    string_copy(str2, str5);
    puts("\t\tstring_copy(str2, str5):");
    STRING_INFO(str2);
    string str6 = string_init("Hey, you! Stop there!", 5);
    printf("\t\tstr6 = %s\n", string_data(str6));
    string_copy(str3, str6);
    puts("\t\tstring_copy(str3, str6):");
    STRING_INFO(str3);
    // string_compare
    puts("\n\tint string_compare(string dst, string src):");
    const int cmp1 = string_compare(str5, str3);
    printf("\t\tstring_compare(str5, str3) = %d\n", cmp1);
    STRING_INFO(str5);
    STRING_INFO(str3);
    const int cmp2 = string_compare(str2, str5);
    printf("\t\tstring_compare(str2, str5) = %d\n", cmp2);
    STRING_INFO(str2);
    STRING_INFO(str5);
    const int cmp3 = string_compare(str1, str2);
    printf("\t\tstring_compare(str1, str2) = %d\n", cmp3);
    STRING_INFO(str1);
    STRING_INFO(str2);
    // string_erase
    puts("\n\tvoid string_erase(string self, int start, int end):");
    string_erase(str1, 11, 15);
    puts("\t\tstring_erase(str1, 11, 15):");
    STRING_INFO(str1);
    string_erase(str2, 5, 9);
    puts("\t\tstring_erase(str2, 5, 9):");
    STRING_INFO(str2);
    string_erase(str3, 9, string_length_array(str3));
    puts("\t\tstring_erase(str3, 9, string_length_array(str3)):");
    STRING_INFO(str3);
    // string_reserve
    puts("\n\tvoid string_reserve(string self, int size):");
    const size_t str1_reserve = (size_t)(string_size(str1) * 1.5);
    printf("\t\tstr1_reserve = %ld\n", str1_reserve);
    string_reserve(str1, str1_reserve);
    puts("\t\tstring_reserve(str1, str1_reserve):");
    STRING_INFO(str1);
    const size_t str2_reserve = (size_t)(string_size(str2) * 1.5);
    printf("\t\tstr2_reserve = %ld\n", str2_reserve);
    string_reserve(str2, str2_reserve);
    puts("\t\tstring_reserve(str2, str2_reserve):");
    STRING_INFO(str2);
    const size_t str3_reserve = (size_t)(string_size(str3) * 1.5);
    printf("\t\tstr3_reserve = %ld\n", str3_reserve);
    string_reserve(str3, str3_reserve);
    puts("\t\tstring_reserve(str3, str3_reserve):");
    STRING_INFO(str3);
    // string_replace
    puts("\n\tvoid string_replace(string self, const char* string, int pos, int count):");
    string_replace(str1, " I'm fine.", 12, 10);
    puts("\t\tstring_replace(str1, \" I'm fine.\", 12, 10):");
    STRING_INFO(str1);
    string_replace(str2, ", John.", 5, 7);
    puts("\t\tstring_replace(str2, \", John.\", 5, 7):");
    STRING_INFO(str2);
    string_replace(str3, " Wait, man!", 9, 11);
    puts("\t\tstring_replace(str3, \" Wait, man!\", 9, 11):");
    STRING_INFO(str3);
    // string_shrink_to_fit
    puts("\n\tvoid string_shrink_to_fit(string self):");
    string_shrink_to_fit(str1);
    puts("\t\tstring_shrink_to_fit(str1):");
    STRING_INFO(str1);
    string_shrink_to_fit(str2);
    puts("\t\tstring_shrink_to_fit(str2):");
    STRING_INFO(str2);
    string_shrink_to_fit(str3);
    puts("\t\tstring_shrink_to_fit(str3):");
    STRING_INFO(str3);
    // string_resize
    puts("\n\tvoid string_resize(string self, int size):");
    const int str1_resize = (string_length(str1) + strlen(".."));
    printf("\t\tstr1_resize = %d\n", str1_resize);
    string_resize(str1, str1_resize);
    puts("\t\tstring_resize(str1, str1_resize):");
    STRING_INFO(str1);
    const int str2_resize = (string_length(str2) - strlen(", John."));
    printf("\t\tstr1_resize = %d\n", str2_resize);
    string_resize(str2, str2_resize);
    puts("\t\tstring_resize(str2, str2_resize):");
    STRING_INFO(str2);
    const int str3_resize = (string_length(str3) + strlen("!!!!"));
    printf("\t\tstr3_resize = %d\n", str3_resize);
    string_resize(str3, str3_resize);
    puts("\t\tstring_resize(str3, str3_resize):");
    STRING_INFO(str3);
    // string_slice
    puts("\n\tstring string_slice(string self, int start, int end):");
    string str7 = string_slice(str1, 0, 11);
    puts("\t\tstring_slice(str1, 0, 11):");
    STRING_INFO(str7);
    string str8 = string_slice(str2, 0, string_length_array(str2));
    puts("\t\tstring_slice(str2, 0, string_length_array(str2)):");
    STRING_INFO(str8);
    // string_slice_array
    puts("\n\tchar* string_slice_array(string self, int start, int end):");
    char* str9_content = string_slice_array(str3, 10, 19);
    string str9 = string_init(str9_content, strlen(str9_content));
    if (str9_content) {
        free(str9_content);
    }
    STRING_INFO(str9);
    // string_justified
    puts("\n\tvoid string_justified(string self, size_t width, const char fill):");
    string_justified(str1, (string_length(str1) + 5), '-');
    puts("\t\tstring_justified(str1, (string_length(str1) + 5), '-'):");
    STRING_INFO(str1);
    // string_count
    puts("\n\tsize_t string_count(string self, const char* src, size_t start, size_t end):");
    const size_t str7_count = string_count(str7, "you", 0, string_length_array(str7));
    puts("\t\tstring_count(str7, \"you\", 0, string_length_array(str7)):");
    printf("\t\t\tstr7_count = %ld\n", str7_count);
    const size_t str8_count = string_count(str8, "l", 0, string_length_array(str8));
    puts("\t\tstring_count(str8, \"l\", 0, string_length_array(str8)):");
    printf("\t\t\tstr8_count = %ld\n", str8_count);
    const size_t str9_count = string_count(str9, ", ", 1, 8);
    puts("\t\tstring_count(str9, \", \", 1, 8):");
    printf("\t\t\tstr9_count = %ld\n", str9_count);
    // string_end_with
    puts("\n\tbool string_end_with(string self, const char* str):");
    const bool str7_end_with = string_end_with(str7, "you?", 0, string_length_array(str7));
    puts("\t\tstring_end_with(str7, \"you?\", 0, string_length_array(str7)):");
    printf("\t\t\tstr7_end_with = %d\n", str7_end_with);
    const bool str8_end_with = string_end_with(str8, "o", 0, string_length_array(str8));
    puts("\t\tstring_end_with(str8, \"o\", 0, string_length_array(self)):");
    printf("\t\t\tstr8_end_with = %d\n", str8_end_with);
    const bool str9_end_with = string_end_with(str9, ", ", 0, 5);
    puts("\t\tstring_end_with(str9, \", \", 0, 5):");
    printf("\t\t\tstr9_end_with = %d\n", str9_end_with);
    // string_find
    puts("\n\tint string_find(string self, const char* string, int start):");
    const size_t str7_find = string_find(str7, "you", 6);
    puts("\t\tstring_find(str7, \"you\", 6):");
    printf("\t\t\tstr7_find = %ld\n", str7_find);
    const size_t str8_find = string_find(str8, "He", 4);
    puts("\t\tstring_find(str8, \"He\", 4):");
    printf("\t\t\tstr8_find = %ld\n", str8_find);
    const size_t str9_find = string_find(str9, ",", 0);
    puts("\t\tstring_find(str9, \",\", 0):");
    printf("\t\t\tstr9_find = %ld\n", str9_find);
    // string_find_array
    puts("\n\tchar* string_find_array(string self, const char* string, int start):");
    char* str7_find_raw = string_find_array(str7, "you", 6);
    puts("\t\tstring_find_array(str7, \"you\", 6):");
    printf("\t\tstr7_find_raw = %s\n", str7_find_raw);
    if (str7_find_raw) {
        free(str7_find_raw);
    }
    char* str8_find_raw = string_find_array(str8, "He", 4);
    puts("\t\tstring_find_array(str8, \"He\", 4):");
    printf("\t\t\tstr8_find_raw = %s\n", str8_find_raw);
    if (str8_find_raw) {
        free(str8_find_raw);
    }
    char* str9_find_raw = string_find_array(str9, ",", 0);
    puts("\t\tstring_find_array(str9, \",\", 0):");
    printf("\t\t\tstr9_find_raw = %s\n", str9_find_raw);
    if (str9_find_raw) {
        free(str9_find_raw);
    }
    // string_rfind
    puts("\n\tint string_rfind(string self, const char* string, int start):");
    const size_t str7_rfind = string_rfind(str7, "you", 6);
    puts("\t\tstring_rfind(str7, \"you\", 6):");
    printf("\t\t\tstr7_rfind = %ld\n", str7_rfind);
    const size_t str8_rfind = string_rfind(str8, "He", 4);
    puts("\t\tstring_rfind(str8, \"He\", 4):");
    printf("\t\t\tstr8_rfind = %ld\n", str8_rfind);
    const size_t str9_rfind = string_rfind(str9, ",", 0);
    puts("\t\tstring_rfind(str9, \",\", 0):");
    printf("\t\t\tstr9_rfind = %ld\n", str9_rfind);
    // string_rfind_array
    puts("\n\tchar* string_rfind_array(string self, const char* string, int start):");
    char* str7_rfind_raw = string_rfind_array(str7, "you", 6);
    puts("\t\tstring_rfind_array(str7, \"you\", 6):");
    printf("\t\t\tstr7_rfind_raw = %s\n", str7_rfind_raw);
    if (str7_rfind_raw) {
        free(str7_rfind_raw);
    }
    char* str8_rfind_raw = string_rfind_array(str8, "He", 4);
    puts("\t\tstring_rfind_array(str8, \"He\", 4):");
    printf("\t\t\tstr8_rfind_raw = %s\n", str8_rfind_raw);
    if (str8_rfind_raw) {
        free(str8_rfind_raw);
    }
    char* str9_rfind_raw = string_rfind_array(str9, ",", 0);
    puts("\t\tstring_rfind_array(str9, \",\", 0):");
    printf("\t\t\tstr9_rfind_raw = %s\n", str9_rfind_raw);
    if (str9_rfind_raw) {
        free(str9_rfind_raw);
    }
    // string_find_first_of
    puts("\n\tint string_find_first_of(string self, const char* string, int pos, int at):");
    const size_t str7_find_first_of = string_find_first_of(str7, "?", 6, 0);
    puts("\t\tstring_find_first_of(str7, \"?\", 6, 0):");
    printf("\t\t\tstr7_find_first_of = %ld\n", str7_find_first_of);
    const size_t str8_find_first_of = string_find_first_of(str8, "Hello", 0, 5);
    puts("\t\tstring_find_first_of(str8, \"Hello\", 0, 5):");
    printf("\t\t\tstr8_find_first_of = %ld\n", str8_find_first_of);
    const size_t str9_find_first_of = string_find_first_of(str9, ",!", 3, 0);
    puts("\t\tstring_find_first_of(str9, \",!\", 3, 0):");
    printf("\t\t\tstr9_find_first_of = %ld\n", str9_find_first_of);
    // string_find_last_of
    puts("\n\tint string_find_last_of(string self, const char* string, int pos, int at):");
    const size_t str7_find_last_of = string_find_last_of(str7, "o", 0, 0);
    puts("\t\tstring_find_last_of(str7, \"o\", 0, 0):");
    printf("\t\t\tstr7_find_last_of = %ld\n", str7_find_last_of);
    const size_t str8_find_last_of = string_find_last_of(str8, "Hello", 0, 3);
    puts("\t\tstring_find_last_of(str8, \"Hello\", 0, 3):");
    printf("\t\t\tstr8_find_last_of = %ld\n", str8_find_last_of);
    const size_t str9_find_last_of = string_find_last_of(str9, ",!", 3, 0);
    puts("\t\tstring_find_last_of(str9, \",!\", 3, 0):");
    printf("\t\t\tstr9_find_last_of = %ld\n", str9_find_last_of);
    // string_find_first_not_of
    puts("\n\tint string_find_first_not_of(string self, const char* string, int pos):");
    const size_t str7_find_first_not_of = string_find_first_not_of(str7," 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 8);
    puts("\t\tstring_find_first_not_of(str7, \" 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 8):");
    printf("\t\t\tstr7_find_first_not_of = %ld\n", str7_find_first_not_of);
    const size_t str8_find_first_not_of = string_find_first_not_of(str8, "abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);
    puts("\t\tstring_find_first_not_of(str8, \" 0123456789abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 0):");
    printf("\t\t\tstr8_find_first_not_of = %ld\n", str8_find_first_not_of);
    const size_t str9_find_first_not_of = string_find_first_not_of(str9, "Wait man!", 3);
    puts("\t\tstring_find_first_not_of(str9, \"Wait man!\", 3):");
    printf("\t\t\tstr9_find_first_not_of = %ld\n", str9_find_first_not_of);
    // string_find_last_not_of
    puts("\n\tint string_find_last_not_of(string self, const char* string, int pos):");
    const size_t str7_find_last_not_of = string_find_last_not_of(str7, " ?0123456789abcdefghijklmnopqrstuvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ", 8);
    puts("\t\tstring_find_last_not_of(str7, \" ?0123456789abcdefghijklmnopqrstuvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 8):");
    printf("\t\t\tstr7_find_last_not_of = %ld\n", str7_find_last_not_of);
    const size_t str8_find_last_not_of = string_find_last_not_of(str8, "abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);
    puts("\t\tstring_find_last_not_of(str8, \" 0123456789abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 0):");
    printf("\t\t\tstr8_find_last_not_of = %ld\n", str8_find_last_not_of);
    const size_t str9_find_last_not_of = string_find_last_not_of(str9, "Wait, man", 0);
    puts("\t\tstring_find_last_not_of(str9, \"Wait, man\", 3):");
    printf("\t\t\tstr9_find_last_not_of = %ld\n", str9_find_last_not_of);
    // string_includes
    puts("\n\tbool string_includes(string self, const char* str):");
    const bool str7_includes = string_includes(str7, "you?");
    puts("\t\tstring_includes(str7, \"you?\"):");
    printf("\t\t\tstr7_includes = %d\n", str7_includes);
    // string_start_with
    puts("\n\tbool string_start_with(string self, const char* str):");
    const bool str7_start_with = string_start_with(str7, "How" , 0);
    puts("\t\tstring_start_with(str7, \"How \", 0):");
    printf("\t\t\tstr7_start_with = %d\n", str7_start_with);
    const bool str8_start_with = string_start_with(str8, "H", 0);
    puts("\t\tstring_start_with(str8, \"H\", 0):");
    printf("\t\t\tstr8_start_with = %d\n", str8_start_with);
    const size_t str9_end_pos = string_find(str9, "man!", 0);
    const bool str9_start_with = string_start_with(str9, "man!", str9_end_pos);
    puts("\t\tstring_start_with(str9, \"man!\", str9_end_pos):");
    printf("\t\t\tstr9_start_with = %d\n", str9_start_with);
    // string_expand_tab
    puts("\n\tstring string_expand_tabs(string self, size_t tab_size):");
    string str10 = string_init("Wait\tme", 0);
    puts("\t\tstring_init(\"Wait\tme\", 0):");
    STRING_INFO(str10);
    string_expand_tabs(str10, 8);
    puts("\t\tstring_expand_tabs(str10, 8):");
    STRING_INFO(str10);
    string str11 = string_init("Welcome\tto\tmy\thome", 0);
    puts("\t\tstring_init(\"Welcome\tto\tmy\thome\", 0):");
    STRING_INFO(str11);
    string_expand_tabs(str11, 0);
    puts("\t\tstring_expand_tabs(str11, 0):");
    STRING_INFO(str11);
    // string_join
    puts("\n\tvoid string_join(string dst, string src):");
    string str12 = string_init("Hey... ", 0);
    puts("\t\tstring_init(\"Hey... \", 0):");
    STRING_INFO(str12);
    string str13 = string_init("Wait for me!", 0);
    puts("\t\tstring_init(\"Wait for me!\", 0):");
    STRING_INFO(str13);
    string_join(str12, str13);
    puts("\t\tstring_join(str12, str13):");
    STRING_INFO(str12);
    // string_lower_case
    puts("\n\tvoid string_lower_case(string self):");
    string_lower_case(str12);
    puts("\t\tstring_lower_case(str12):");
    STRING_INFO(str12);
    // string_upper_case
    puts("\n\tvoid string_upper_case(string self):");
    string_upper_case(str12);
    puts("\t\tstring_upper_case(str12):");
    STRING_INFO(str12);
    // string_swap_case
    puts("\n\tvoid string_swap_case(string self):");
    string_swap_case(str13);
    puts("\t\tstring_swap_case(str13):");
    STRING_INFO(str13);
    // string_justified_left
    puts("\n\tvoid string_justified_left(string self, size_t width, const char fill):");
    const size_t str12_justified_left = (string_length(str12) + 8);
    string_justified_left(str12, str12_justified_left, '!');
    puts("\t\tstring_justified_left(str12, str12_justified_left, '!'):");
    STRING_INFO(str12);
    // string_justified_right
    puts("\n\tvoid string_justified_right(string self, size_t width, const char fill):");
    const size_t str12_justified_right = (string_length(str12) + 8);
    string_justified_right(str12, str12_justified_right, '!');
    puts("\t\tstring_justified_right(str12, str12_justified_right, '!'):");
    STRING_INFO(str12);
    // string_min_char
    puts("\n\tchar string_min_char(string self, size_t start, size_t end):");
    char str13_min_char = string_min_char(str13, 0, string_length(str13));
    puts("\t\tstring_min_char(str13, 0, string_length(str13)):");
    printf("\t\tstr13_min_char = %c\n", str13_min_char);
    // string_max_char
    puts("\n\tchar string_max_char(string self, size_t start, size_t end):");
    char str13_max_char = string_max_char(str13, 0, string_length(str13));
    puts("\t\tstring_max_char(str13, 0, string_length(str13)):");
    printf("\t\tstr13_max_char = %c\n", str13_max_char);
    // string_trim
    puts("\n\tvoid string_trim(string self, char remove):");
    string_trim(str12, '!');
    puts("\t\tstring_trim(str12, '!'):");
    STRING_INFO(str12);
    // string_trim_left
    /*puts("\n\tvoid string_trim_left(string self, const char remove):");
    string_trim_left(str12, '!');
    puts("\t\tstring_trim_left(str12, '!'):");
    STRING_INFO(str12);
    // string_trim_right
    puts("\n\tvoid string_trim_right(string self, const char remove):");
    string_trim_right(str12, '!');
    puts("\t\tstring_trim_right(str12, '!'):");
    STRING_INFO(str12);*/
    // string_title
    puts("\n\tvoid string_title(string self):");
    string_title(str12);
    puts("\t\tstring_title(str12):");
    STRING_INFO(str12);
    // string_repeat
    puts("\n\tvoid string_repeat(string self, size_t repetitions):");
    string_repeat(str8, 4);
    puts("\t\tstring_repeat(str8, 4):");
    STRING_INFO(str8);
    // string_destroy
    string_destroy(str1);
    string_destroy(str2);
    string_destroy(str3);
    string_destroy(str4);
    string_destroy(str5);
    string_destroy(str6);
    string_destroy(str7);
    string_destroy(str8);
    string_destroy(str9);
    string_destroy(str10);
    string_destroy(str11);
    string_destroy(str12);
    string_destroy(str13);

    getchar();
    return EXIT_SUCCESS;
}
