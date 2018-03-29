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

#include <stdio.h>
#include <stdlib.h>

#include "./src/vector.h"

int main(void) {
    vector_t* vector1 = vector_init(sizeof(int), 0);
    printf("vector1.size = %ld\n", vector_size(vector1));
    printf("vector1.capacity = %ld\n", vector_capacity(vector1));
    printf("vector1.data = %d\n", (int*)(vector_front(vector1)));
    int a = 5;
    vector_push_back(vector1, &a, sizeof(int));
    printf("\nvector1.size = %ld\n", vector_size(vector1));
    printf("vector1.capacity = %ld\n", vector_capacity(vector1));
    printf("vector1.data = %d\n", *(int*)(vector_front(vector1)));
    int b = 10;
    vector_push_back(vector1, &b, sizeof(int));
    printf("\nvector1.size = %ld\n", vector_size(vector1));
    printf("vector1.capacity = %ld\n", vector_capacity(vector1));
    printf("vector1.data = %d\n", *(int*)(vector_at(vector1, 1)));
    int c = 15;
    vector_push_back(vector1, &c, sizeof(int));
    printf("\nvector1.size = %ld\n", vector_size(vector1));
    printf("vector1.capacity = %ld\n", vector_capacity(vector1));
    for (size_t i = 0; i < vector_size(vector1); ++i) {
        printf("vector1.data = %d\n", *(int*)(vector_at(vector1, i)));
    }

    int d = 30;
    vector_insert(vector1, &d, sizeof(int), 2);
    printf("\nvector1.size = %ld\n", vector_size(vector1));
    printf("vector1.capacity = %ld\n", vector_capacity(vector1));
    for (size_t i = 0; i < vector_size(vector1); ++i) {
        printf("vector1.data = %d\n", *(int*)(vector_at(vector1, i)));
    }

    vector_t* vector2 = vector_init(sizeof(int), 0);
    printf("\nvector2.size = %ld\n", vector_size(vector2));
    printf("vector2.capacity = %ld\n", vector_capacity(vector2));
    printf("vector2.data = %d\n", (int*)(vector_front(vector2)));
    int z = 100;
    vector_push_back(vector2, &z, sizeof(int));
    printf("\nvector2.size = %ld\n", vector_size(vector2));
    printf("vector2.capacity = %ld\n", vector_capacity(vector2));
    printf("vector2.data = %d\n", *(int*)(vector_front(vector2)));
    int y = 125;
    vector_push_back(vector2, &y, sizeof(int));
    printf("\nvector2.size = %ld\n", vector_size(vector2));
    printf("vector2.capacity = %ld\n", vector_capacity(vector2));
    printf("vector2.data = %d\n", *(int*)(vector_at(vector2, 1)));
    int x = 150;
    vector_push_back(vector2, &x, sizeof(int));
    printf("\nvector2.size = %ld\n", vector_size(vector2));
    printf("vector2.capacity = %ld\n", vector_capacity(vector2));
    for (size_t i = 0; i < vector_size(vector2); ++i) {
        printf("vector2.data = %d\n", *(int*)(vector_at(vector2, i)));
    }

    int w = 175;
    vector_insert(vector2, &w, sizeof(int), 2);
    printf("\nvector2.size = %ld\n", vector_size(vector2));
    printf("vector2.capacity = %ld\n", vector_capacity(vector2));
    for (size_t i = 0; i < vector_size(vector2); ++i) {
        printf("vector2.data = %d\n", *(int*)(vector_at(vector2, i)));
    }

    vector_destroy(vector1);
    vector_destroy(vector2);

    return EXIT_SUCCESS;
}