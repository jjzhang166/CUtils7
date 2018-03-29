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

#include <stdlib.h>

#include "./vector.h"

static const float _GROWTH_FACTOR_ = 1.5f;

static void* memory_copy(void* const dest, const void* const src, size_t bytes) {
    char* dest_temp = dest;
    const char *src_temp = src;
    while (bytes--) {
        *dest_temp++ = *src_temp++;
    }
    return dest;
}

static void* memory_set(void* const src, int value, size_t bytes) {
    uint8_t* temp = src;
    while (bytes--) {
        *temp++ = (uint8_t)value;
    }
    return src;
}

struct _internal_vector {
    size_t capacity;
    size_t size;
    size_t elements_size;
    void* elements;
};
/*
 * Check if a vector and it's elements are not null.
 */
static bool vector_status(vector_t* const self){
    return self && self->elements ? true : false;
}
///////////
// Basic //
///////////
/**
 * @brief Initialize a new vector container.
 *
 * @param elements_size What kind of variables is going to hold the vector container.
 * @param elements_count How much capacity the vector container will have at it's creation.
 *
 * @return A new vector container.
 */
vector_t* vector_init(const size_t elements_size, const size_t elements_count) {
    if (!elements_size) {
        return NULL;
    }
    vector_t* init = malloc(sizeof(vector_t));
    if (!init) {
        return NULL;
    }
    init->size = 0;
    init->elements_size = elements_size;
    if (!elements_count) {
        init->capacity = elements_count;
        init->elements = NULL;
    }
    else {
        init->capacity = (size_t)(elements_count * _GROWTH_FACTOR_);
        init->elements = malloc(init->elements_size * vector_capacity(init));
        if (!init->elements) {
            free(init);
            return NULL;
        }
        for (size_t i = 0; i < init->capacity; ++i) {
            memory_set(init->elements + i * init->elements_size, 0, init->elements_size);
        }
    }
    return init;
}
/**
 * @brief Free the memory of a vector content plus container itself.
 *
 * @param self The vector to be freed.
 */
void vector_destroy(vector_t* const self) {
    if (!self) {
        return;
    }
    if (!self->elements) {
        free(self);
    }
    else {
        free(self->elements);
        free(self);
    }
}
////////////
// Access //
////////////
/**
 * @brief Returns a element from a vector container at given position.
 *
 * @param self  Vector container to get element from.
 * @param index Position at which get element from a vector container. Start point is 0.
 *
 * @return Return a element from self at index.
 */
void* vector_at(vector_t* const self, const size_t index) {
    if (!vector_status(self)) {
        return NULL;
    }
    return self->elements + index * self->elements_size;
}
/**
 * @brief Return the last element in a vector container.
 *
 * @param self Vector container to get last element from.
 *
 * @return Return the last element in self.
 */
void* vector_back(vector_t* const self) {
    if (!vector_status(self)) {
        return NULL;
    }
    return self->size ? self->elements + (vector_size(self) - 1) * self->elements_size : vector_data(self);
}
/**
 * @brief Return the content in a vector container.
 *
 * @param self Vector container to get content from.
 *
 * @return Return a pointer to void with self content.
 */
void* vector_data(vector_t* const self) {
    if (!vector_status(self)) {
        return NULL;
    }
    return self->elements;
}
/**
 * @brief Return the first element in a string container.
 *
 * @param self Vector container to get first element from.
 *
 * @return Return the first element in self.
 */
void* vector_front(vector_t* const self) {
    if (!vector_status(self)) {
        return NULL;
    }
    return self->elements;
}
/**
 * @brief Copy a vector container content to a pointer to void.
 *
 * @param self          Vector container whose content will be copied.
 * @param array         Pointer to void which will recieve the copy from a string container.
 * @param array_size    Pointer to void size that will hold a vector container content.
 */
void vector_to_array(vector_t* const self, void* const array, const size_t array_size) {
    if (!vector_status(self) || !array_size) {
        return;
    }
    for (size_t i = 0; i < array_size; ++i) {
        memory_copy(array + i * self->elements_size, self->elements + i * self->elements_size, array_size);
    }
}
//////////////
// Capacity //
//////////////
size_t vector_capacity(vector_t* const self) {
    if (!self) {
        return 0;
    }
    return self->capacity;
}
/**
 * @brief Returns if a vector container has any elements at all.
 *
 * @param self Vector container to check size from.
 *
 * @return Return true if self has 0 size.
 */
bool vector_is_empty(vector_t* const self) {
    return self ? self->size == 0 : true;
}
/**
 * @brief Assign a new capacity to a vector container.
 *
 * @param self Vector container to set capacity at.
 * @param size New capacity to be set. Unless it's lesser than current size.
 */
void vector_reserve(vector_t* const self, const size_t size) {
    if (!self || !size) {
        return;
    }
    if (self->capacity < size) {
        self->capacity = (size_t)(size * _GROWTH_FACTOR_);
        void* temp = realloc(self->elements, self->elements_size * self->capacity);
        if (!temp) {
            return;
        }
        self->elements = temp;
        for (size_t i = self->capacity - self->size - 1; i < self->capacity; ++i) {
            memory_set(self->elements + i * self->elements_size, 0, self->elements_size);
        }
    }
}
/**
 * @brief Resize current vector elements size in a vector container.
 *
 * @param self Vector container that will be changed.
 * @param size New size that will be use in a vector container.
 */
void vector_resize(vector_t *const self, const size_t size, void* const element) {
    if (!vector_status(self) || !size) {
        return;
    }
    if (size > self->size) {
        if (size > self->capacity) {
            vector_reserve(self, size);
        }
        for (size_t i = self->size; i < size; i++) {
            if (!element) {
                memory_set(self->elements + i * self->elements_size, 0, self->elements_size);
            }
            else {
                memory_copy(self->elements + i * self->elements_size, element, self->elements_size);
            }
        }
    }
    else {
        vector_erase(self, self->size - 1, size - 1);
    }
    self->size = size;
}
/**
 * @brief Shrink a vector container to fit just the elements in it.
 *
 * @param self Vector container to shrink capacity.
 */
void vector_shrink_to_fit(vector_t* const self) {
    if (!vector_status(self)) {
        return;
    }
    if (self->capacity > self->size) {
        self->capacity = self->size;
        void* temp = realloc(self->elements, self->capacity * self->elements_size);
        if (!temp) {
            return;
        }
        self->elements = temp;
    }
}
/**
 * @brief Returns the current size of a vector container.
 *
 * @param self Vector container to retrieve size from.
 *
 * @return Return the current size of self.
 */
size_t vector_size(vector_t* const self) {
    if (!self) {
        return 0;
    }
    return self->size;
}
/////////////////
// Operations //
////////////////
/**
 * @brief Assign a new content to a vector.
 *
 * @param self The vector that will get new content.
 * @param element The new content to be assigned.
 * @param element_size The element's size in bytes.
 * @param element_count How many elements will be inserted.
 */
void vector_assign(vector_t* const self, void* const element, const size_t element_size, const size_t element_count) {
    if (!element || element_size != self->elements_size || !element_count) {
        return;
    }
    if (element_count > vector_capacity(self)) {
        vector_reserve(self, element_count);
    }
    for (size_t i = 0; i < element_count; ++i) {
        memory_copy(self->elements + i * self->elements_size, element, self->elements_size);
    }
    self->size = element_count;
}
/**
 * @brief Remove all elements from a vector container.
 *
 * @param self Vector container whose elements are going to be removed.
 */
void vector_clear(vector_t* const self) {
    if (!self) {
        return;
    }
    for (size_t i = 0; i < self->size; ++i) {
        memory_set(self->elements + i * self->elements_size, 0, self->elements_size);
    }
    self->size = 0;
}
/**
 * @brief Copy the content from a vector container to another one.
 *
 * @param dst Vector container that will recieve the copied elements.
 * @param src Vector container whose elements will be copied.
 * 
 * @return Return dst containing a copy of all elements in src.
 */
vector_t* vector_copy(vector_t* dst, vector_t* const src) {
    if (!vector_status(src)) {
        return NULL;
    }
    if (!dst) {
        dst = vector_init(src->elements_size, src->size);
    }
    else {
        vector_clear(dst);
    }
    for (size_t i = 0; i < src->size; ++i) {
        vector_push_back(dst, src->elements + i * src->elements_size, src->elements_size);
    }
    return dst;
}
/**
 * @brief Remove a element amount from a vector container.
 *
 * @param self Vector container whose elements will be erased.
 * @param start Start position from which will the erase begin.
 * @param end End position at which the erase will stop.
 */
void vector_erase(vector_t* const self, const size_t start, const size_t end) {
    if (!vector_status(self) || start >= self->size || !end) {
        return;
    }
    const size_t elements_size = self->size;
    void* elements = malloc(elements_size * self->elements_size);
    for (size_t i = 0; i < elements_size; ++i) {
        memory_copy(elements + i * self->elements_size, self->elements + i * self->elements_size, self->elements_size);
    }
    vector_clear(self);
    size_t i = 0;
    size_t self_it = 0;
    for (; i < start; ++i) {
        memory_copy(self->elements + self_it++ * self->elements_size, elements + i * self->elements_size, self->elements_size);
    }
    for (i = end + 1; i < elements_size; ++i) {
        memory_copy(self->elements + self_it++ * self->elements_size, elements + i * self->elements_size, self->elements_size);
    }
    self->size = end - start + 1;
    free(elements);
}
/**
 * @brief Insert a element at random position into a vector container.
 *
 * @param self          Vector container which the insertion will occur.
 * @param element       Element to be inserted.
 * @param element_size  Element size to be inserted.
 * @param index         Position at which element will be inserted.
 */
void vector_insert(vector_t* const self, void* const element, const size_t element_size, const size_t index) {
    if (!self || !element || !element_size || element_size != self->elements_size || index >= self->size) {
        return;
    }
    if (self->size + 1 > self->capacity) {
        vector_reserve(self, self->capacity + 1);
    }
    for (size_t i = self->size; i > index; --i) {
        memory_copy(self->elements + i * self->elements_size, self->elements + (i - 1) * self->elements_size, self->elements_size);
        if (i - 1 == index) {
            memory_copy(self->elements + index * self->elements_size, element, self->elements_size);
        }
    }
    self->size++;
}
/**
 * @brief Move the content from a vector container to another one.
 * 
 * @param dst Vector container that will hold the content from another vector container.
 * @param src Vector container that will be moved into another vector container.
 * 
 * @return Return dst containing the content that existed in src before been deleted.
 */
vector_t* vector_move(vector_t* dst, vector_t* src) {
    if (!vector_status(src)) {
        return NULL;
    }
    dst = src;
    src = NULL;
    return dst;
}
/**
 * @brief Remove last element in a vector container.
 *
 * @param self Vector container whose last element will be removed.
 */
void vector_pop_back(vector_t* const self) {
    if (!vector_status(self) || !self->size) {
        return;
    }
    memory_set(self->elements + (self->size - 1) * self->elements_size, 0, self->elements_size);
    self->size--;
}
/**
 * @brief Push a element at vector container end.
 *
 * @param self String container that will hold the new character.
 * @param c Character to be add.
 */
void vector_push_back(vector_t* const self, const void* const element, const size_t element_size) {
    if (!self || !element || element_size != self->elements_size) {
        return;
    }
    if (!self->elements) {
        if (self->size + 1 >= self->capacity) {
            self->capacity = (size_t)((self->capacity + 1) * _GROWTH_FACTOR_);
        }
        self->elements = malloc(self->elements_size * self->capacity);
        if (!self->elements) {
            return;
        }
        for (size_t index = self->capacity - self->size - 1; index < self->capacity; ++index) {
            memory_set(self->elements + index * self->elements_size, 0, self->elements_size);
        }
    }
    else {
        if (self->size + 1 >= self->capacity) {
            vector_reserve(self, self->capacity + 1);
        }
    }
    memory_copy(self->elements + self->size * self->elements_size, element, self->elements_size);
    self->size++;
}
/**
 * @brief Swap the content of two stack containers.
 *
 * @param dst Vector container that will hold the swapped content.
 * @param src Vector container whose content will be swapped.
 */
void vector_swap(vector_t* const dst, vector_t* const src) {
    if (!vector_status(dst) || !vector_status(src)) {
        return;
    }
    vector_t temp = *dst;
    *dst = *src;
    *src = temp;
}
