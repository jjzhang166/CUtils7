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
    puts("\n\tbool string_empty(string self)");
    printf("\t\tstring_empty(str1) = %d\n", string_empty(str1));
    printf("\t\tstring_empty(str2) = %d\n", string_empty(str2));
    printf("\t\tstring_empty(str3) = %d\n", string_empty(str3));
    // string_append
    puts("\n\tvoid string_append(string self, const char* string):");
    string_append(str1, " How are you?");
    puts("\t\tstring_append(str1, \" How are you?\"):");
    STRING_INFO(str1);
    string_append(str2, "Who are you?");
    puts("\t\tstring_append(str2, \"Who are you?\"):");
    STRING_INFO(str2);
    string_append(str3, "Hello, world!");
    puts("\t\tstring_append(str3, \"Hello, world!\"):");
    STRING_INFO(str3);
    // string_clear
    puts("\n\tvoid string_clear(string self)");
    string_clear(str1);
    puts("\t\tstring_clear(str1)");
    STRING_INFO(str1);
    string_clear(str2);
    puts("\t\tstring_clear(str2)");
    STRING_INFO(str2);
    string_clear(str3);
    puts("\t\tstring_clear(str3)");
    STRING_INFO(str3);
    // string_push_back
    puts("\n\tvoid string_push_back(string self, const char c)");
    char buffer1[8] = "Heyyou.";
    printf("\t\tbuffer1 = %s\n", buffer1);
    for (int i = 0; i < (int)strlen(buffer1); ++i)
    {
        string_push_back(str1, buffer1[i]);
        printf("\t\tstring_push_back(str1, buffer1[%d])\n", i);
        STRING_INFO(str1);
    }
    char buffer2[9] = "are you?";
    printf("\t\tbuffer2 = %s\n", buffer2);
    for (int i = 0; i < (int)strlen(buffer2); ++i)
    {
        string_push_back(str2, buffer2[i]);
        printf("\t\tstring_push_back(str2, buffer2[%d])\n", i);
        STRING_INFO(str2);
    }
    char buffer3[8] = "Hello, ";
    printf("\t\tbuffer3 = %s\n", buffer3);
    for (int i = 0; i < (int)strlen(buffer3); ++i)
    {
        string_push_back(str3, buffer3[i]);
        printf("\t\tstring_push_back(str3, buffer3[%d])\n", i);
        STRING_INFO(str3);
    }
    // string_insert
    puts("\n\tvoid string_insert(string self, int pos, const char* string)");
    string_insert(str1, ", ", 3);
    puts("\t\tstring_insert(str1, \", \", 3)");
    STRING_INFO(str1);
    string_insert(str2, "How ", 0);
    puts("\t\tstring_insert(str2, \"How\", 3)");
    STRING_INFO(str2);
    string_insert(str3, "World!", 7);
    puts("\t\tstring_insert(str3, \"World!\", 3)");
    STRING_INFO(str3);
    // string_swap
    puts("\n\tvoid string_swap(string dst, string src)");
    string_swap(str2, str1);
    puts("\t\tstring_swap(str2, str1)");
    STRING_INFO(str1);
    STRING_INFO(str2);
    string_swap(str3, str2);
    puts("\n\t\tstring_swap(str3, str2)");
    STRING_INFO(str2);
    STRING_INFO(str3);
    // string_pop_back
    puts("\n\tvoid string_pop_back(string self)");
    string_pop_back(str1);
    puts("\t\tstring_pop_back(str1)");
    STRING_INFO(str1);
    string_pop_back(str2);
    puts("\t\tstring_pop_back(str2)");
    STRING_INFO(str2);
    string_pop_back(str3);
    puts("\t\tstring_pop_back(str3)");
    STRING_INFO(str3);
    // string_copy
    puts("\n\tvoid string_copy(string dst, string src)");
    string str4 = string_init("How are you, son?", 0);
    printf("\t\tstr4 = %s\n", string_data(str4));
    string_copy(str1, str4);
    puts("\t\tstring_copy(str1, str4)");
    STRING_INFO(str1);
    string str5 = string_init("Hello, sir.", 11);
    printf("\t\tstr5 = %s\n", string_data(str5));
    string_copy(str2, str5);
    puts("\t\tstring_copy(str2, str5)");
    STRING_INFO(str2);
    string str6 = string_init("Hey, you! Stop there!", 5);
    printf("\t\tstr6 = %s\n", string_data(str6));
    string_copy(str3, str6);
    puts("\t\tstring_copy(str3, str6)");
    STRING_INFO(str3);
    // string_compare
    puts("\n\tint string_compare(string dst, string src)");
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
    puts("\n\tvoid string_erase(string self, int start, int end)");
    string_erase(str1, 11, 15);
    puts("\t\tstring_erase(str1, 11, 15)");
    STRING_INFO(str1);
    string_erase(str2, 5, 9);
    puts("\t\tstring_erase(str2, 5, 9)");
    STRING_INFO(str2);
    string_erase(str3, 9, string_length_raw(str3));
    puts("\t\tstring_erase(str3, 9, string_length_raw(str3))");
    STRING_INFO(str3);
    // string_reserve
    puts("\n\tvoid string_reserve(string self, int size)");
    const size_t str1_reserve = (size_t)(string_size(str1) * 1.5);
    printf("\t\tstr1_reserve = %ld\n", str1_reserve);
    string_reserve(str1, str1_reserve);
    puts("\t\tstring_reserve(str1, str1_reserve)");
    STRING_INFO(str1);
    const size_t str2_reserve = (size_t)(string_size(str2) * 1.5);
    printf("\t\tstr2_reserve = %ld\n", str2_reserve);
    string_reserve(str2, str2_reserve);
    puts("\t\tstring_reserve(str2, str2_reserve)");
    STRING_INFO(str2);
    const size_t str3_reserve = (size_t)(string_size(str3) * 1.5);
    printf("\t\tstr3_reserve = %ld\n", str3_reserve);
    string_reserve(str3, str3_reserve);
    puts("\t\tstring_reserve(str3, str3_reserve)");
    STRING_INFO(str3);
    // string_replace
    puts("\n\tvoid string_replace(string self, const char* string, int pos, int count)");
    string_replace(str1, " I'm fine.", 12, 10);
    puts("\t\tstring_replace(str1, \" I'm fine.\", 12, 10)");
    STRING_INFO(str1);
    string_replace(str2, ", John.", 5, 7);
    puts("\t\tstring_replace(str2, \", John.\", 5, 7)");
    STRING_INFO(str2);
    string_replace(str3, " Wait, man!", 9, 11);
    puts("\t\tstring_replace(str3, \" Wait, man!\", 9, 11)");
    STRING_INFO(str3);
    // string_shrink_to_fit
    puts("\n\tvoid string_shrink_to_fit(string self)");
    string_shrink_to_fit(str1);
    puts("\t\tstring_shrink_to_fit(str1)");
    STRING_INFO(str1);
    string_shrink_to_fit(str2);
    puts("\t\tstring_shrink_to_fit(str2)");
    STRING_INFO(str2);
    string_shrink_to_fit(str3);
    puts("\t\tstring_shrink_to_fit(str3)");
    STRING_INFO(str3);
    // string_resize
    puts("\n\tvoid string_resize(string self, int size)");
    const int str1_resize = (string_length(str1) + strlen(".."));
    printf("\t\tstr1_resize = %d\n", str1_resize);
    string_resize(str1, str1_resize);
    puts("\t\tstring_resize(str1, str1_resize)");
    STRING_INFO(str1);
    const int str2_resize = (string_length(str2) - strlen(", John."));
    printf("\t\tstr1_resize = %d\n", str2_resize);
    string_resize(str2, str2_resize);
    puts("\t\tstring_resize(str2, str2_resize)");
    STRING_INFO(str2);
    const int str3_resize = (string_length(str3) + strlen("!!!!"));
    printf("\t\tstr3_resize = %d\n", str3_resize);
    string_resize(str3, str3_resize);
    puts("\t\tstring_resize(str3, str3_resize)");
    STRING_INFO(str3);
    // string_substr
    puts("\n\tstring string_substr(string self, int start, int end)");
    string str7 = string_substr(str1, 0, 11);
    puts("\t\tstring_substr(str1, 0, 11)");
    STRING_INFO(str7);
    string str8 = string_substr(str2, 0, string_length_raw(str2));
    puts("\t\tstring_substr(str2, 0, string_length_raw(str2))");
    STRING_INFO(str8);
    // string_substr_raw
    puts("\n\tchar* string_substr_raw(string self, int start, int end)");
    char* str9_content = string_substr_raw(str3, 10, 19);
    string str9 = string_init(str9_content, strlen(str9_content));
    if (str9_content) {
        free(str9_content);
    }
    STRING_INFO(str9);
    // string_find
    puts("\n\tint string_find(string self, const char* string, int start)");
    const int str7_find = string_find(str7, "you", 6);
    puts("\t\tstring_find(str7, \"you\", 6)");
    printf("\t\tstr7_find = %d\n", str7_find);
    const int str8_find = string_find(str8, "He", 4);
    puts("\t\tstring_find(str8, \"He\", 4)");
    printf("\t\tstr8_find = %d\n", str8_find);
    const int str9_find = string_find(str9, ",", 0);
    puts("\t\tstring_find(str9, \",\", 0)");
    printf("\t\tstr9_find = %d\n", str9_find);
    // string_find_raw
    puts("\n\tchar* string_find_raw(string self, const char* string, int start)");
    char* str7_find_raw = string_find_raw(str7, "you", 6);
    puts("\t\tstr7_find_raw(str7, \"you\", 6)");
    printf("\t\tstr7_find_raw = %s\n", str7_find_raw);
    if (str7_find_raw) {
        free(str7_find_raw);
    }
    char* str8_find_raw = string_find_raw(str8, "He", 4);
    puts("\t\tstr8_find_raw(str8, \"He\", 4)");
    printf("\t\tstr8_find_raw = %s\n", str8_find_raw);
    if (str8_find_raw) {
        free(str8_find_raw);
    }
    char* str9_find_raw = string_find_raw(str9, ",", 0);
    puts("\t\tstr9_find_raw(str9, \",\", 0)");
    printf("\t\tstr9_find_raw = %s\n", str9_find_raw);
    if (str9_find_raw) {
        free(str9_find_raw);
    }
    // string_rfind
    puts("\n\tint string_rfind(string self, const char* string, int start)");
    const int str7_rfind = string_rfind(str7, "you", 6);
    puts("\t\tstring_rfind(str7, \"you\", 6)");
    printf("\t\tstr7_rfind = %d\n", str7_rfind);
    const int str8_rfind = string_rfind(str8, "He", 4);
    puts("\t\tstring_rfind(str8, \"He\", 4)");
    printf("\t\tstr8_rfind = %d\n", str8_rfind);
    const int str9_rfind = string_rfind(str9, ",", 0);
    puts("\t\tstring_rfind(str9, \",\", 0)");
    printf("\t\tstr9_rfind = %d\n", str9_rfind);
    // string_rfind_raw
    puts("\n\tchar* string_rfind_raw(string self, const char* string, int start)");
    char* str7_rfind_raw = string_rfind_raw(str7, "you", 6);
    puts("\t\tstr7_rfind_raw(str7, \"you\", 6)");
    printf("\t\tstr7_rfind_raw = %s\n", str7_rfind_raw);
    if (str7_rfind_raw) {
        free(str7_rfind_raw);
    }
    char* str8_rfind_raw = string_rfind_raw(str8, "He", 4);
    puts("\t\tstr8_rfind_raw(str8, \"He\", 4)");
    printf("\t\tstr8_rfind_raw = %s\n", str8_rfind_raw);
    if (str8_rfind_raw) {
        free(str8_rfind_raw);
    }
    char* str9_rfind_raw = string_rfind_raw(str9, ",", 0);
    puts("\t\tstr9_rfind_raw(str9, \",\", 0)");
    printf("\t\tstr9_rfind_raw = %s\n", str9_rfind_raw);
    if (str9_rfind_raw) {
        free(str9_rfind_raw);
    }
    // string_find_first_of
    puts("\n\tint string_find_first_of(string self, const char* string, int pos, int at)");
    const int str7_find_first_of = string_find_first_of(str7, "?", 6, 0);
    puts("\t\tstring_find_first_of(str7, \"?\", 6, 0)");
    printf("\t\tstr7_find_first_of = %d\n", str7_find_first_of);
    const int str8_find_first_of = string_find_first_of(str8, "Hello", 0, 5);
    puts("\t\tstring_find_first_of(str8, \"Hello\", 0, 5)");
    printf("\t\tstr8_find_first_of = %d\n", str8_find_first_of);
    const int str9_find_first_of = string_find_first_of(str9, ",!", 3, 0);
    puts("\t\tstring_find_first_of(str9, \",!\", 3, 0)");
    printf("\t\tstr9_find_first_of = %d\n", str9_find_first_of);
    // string_find_last_of
    puts("\n\tint string_find_last_of(string self, const char* string, int pos, int at)");
    const int str7_find_last_of = string_find_last_of(str7, "o", 0, 0);
    puts("\t\tstring_find_last_of(str7, \"o\", 0, 0)");
    printf("\t\tstr7_find_last_of = %d\n", str7_find_last_of);
    const int str8_find_last_of = string_find_last_of(str8, "Hello", 0, 3);
    puts("\t\tstring_find_last_of(str8, \"Hello\", 0, 3)");
    printf("\t\tstr8_find_last_of = %d\n", str8_find_last_of);
    const int str9_find_last_of = string_find_last_of(str9, ",!", 3, 0);
    puts("\t\tstring_find_last_of(str9, \",!\", 3, 0)");
    printf("\t\tstr9_find_last_of = %d\n", str9_find_last_of);
    // string_find_first_not_of
    puts("\n\tint string_find_first_not_of(string self, const char* string, int pos)");
    const int str7_find_first_not_of = string_find_first_not_of(str7," 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 8);
    puts("\t\tstring_find_first_not_of(str7, \" 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 8)");
    printf("\t\tstr7_find_first_not_of = %d\n", str7_find_first_not_of);
    const int str8_find_first_not_of = string_find_first_not_of(str8, "abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);
    puts("\t\tstring_find_first_not_of(str8, \" 0123456789abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 0)");
    printf("\t\tstr8_find_first_not_of = %d\n", str8_find_first_not_of);
    const int str9_find_first_not_of = string_find_first_not_of(str9, "Wait man!", 3);
    puts("\t\tstring_find_first_not_of(str9, \"Wait man!\", 3)");
    printf("\t\tstr9_find_first_not_of = %d\n", str9_find_first_not_of);
    // string_find_last_not_of
    puts("\n\tint string_find_last_not_of(string self, const char* string, int pos)");
    const int str7_find_last_not_of = string_find_last_not_of(str7, " ?0123456789abcdefghijklmnopqrstuvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ", 8);
    puts("\t\tstring_find_last_not_of(str7, \" ?0123456789abcdefghijklmnopqrstuvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 8)");
    printf("\t\tstr7_find_last_not_of = %d\n", str7_find_last_not_of);
    const int str8_find_last_not_of = string_find_last_not_of(str8, "abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);
    puts("\t\tstring_find_last_not_of(str8, \" 0123456789abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\", 0)");
    printf("\t\tstr8_find_last_not_of = %d\n", str8_find_last_not_of);
    const int str9_find_last_not_of = string_find_last_not_of(str9, "Wait, man", 0);
    puts("\t\tstring_find_last_not_of(str9, \"Wait, man\", 3)");
    printf("\t\tstr9_find_last_not_of = %d\n", str9_find_last_not_of);
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

    getchar();
    return EXIT_SUCCESS;
}
