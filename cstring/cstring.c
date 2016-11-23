/*
 * cstring.c
 * Copyright (C) 2016 asxalex <asxalex@promote.cache-dns.local>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"

static int mystrncpy(char *a, const char *b, size_t n) {
    while(n--) {
        *a++ = *b++;
    }
    return 0;
}

size_t mystirng_length(mystring_t *s) {
    return s->length;
}

mystring_t *new_from_size(size_t size) {
    return new_from_nstring("", size);
}

mystring_t *new_from_string(const char *s) {
    return new_from_nstring(s, strlen(s));
}

mystring_t *new_from_nstring(const char *s, size_t size) {
    int length = strlen(s)+1;
    if (length > size) {
        length = size;
    }
    mystring_t *res = (mystring_t*)malloc(sizeof(mystring_t));
    if (!res) {
        fprintf(stderr, "unable to allocate memory for mystring_t");
        return NULL;
    }
    res->length = length;
    if (length == 0) {
        res->capacity = 1;
    } else {
        res->capacity = length;
    }
    res->content = malloc(sizeof(char) * length);
    if (!res->content) {
        fprintf(stderr, "unable to allocate content memory for mystring_t");
        free(res);
        return NULL;
    }
    mystrncpy(res->content, s, length);
    return res;
}

mystring_t *concat_string(mystring_t *s1, const mystring_t *s2) {
    int content_length = s1->length + s2->length;
    int capacity = s1->capacity;
    if (content_length < capacity / 2) {
        // case for adequate capacity
    } else if (content_length < capacity) {
        // case for capacity with less than double
        capacity = capacity * 2;
    } else {
        // case for capacity shortage
        capacity = content_length * 2;
    }

    mystring_t *result = new_from_size(capacity);
    if (!result) {
        fprintf(stderr, "error in allocation\n");
        return NULL;
    }
    char *ptr = result->content;
    mystrncpy(ptr, s1->content, s1->length);
    mystrncpy(ptr, s2->content, s2->length);
    result->length = content_length;
    result->capacity = capacity;
    return result;
}

int free_mystring(mystring_t *s) {
    free(s->content);
    free(s);
    return 0;
}

mystring_t **split(mystring_t *s, const char c, int *size){
    mystring_t **res;
    *size = 0;
    for (int i = 0; i < s->length; i++) {
        if (s->content[i] == c)
            (*size)++;
    }
    res = (mystring_t**)malloc(sizeof(mystring_t*) * (*size));
    if (!res) {
        fprintf(stderr, "failed to allocate memory for mystring_t **");
        return NULL;
    }

    int j = 0;
    char *k = s->content;
    for (int i = 0; i < s->length; i++) {
        if (s->content[i] == c) {
            res[j++] = new_from_nstring(k, i - (k - s->content));
            k = s->content + i + 1;
        }
    }
    return res;
}

int is_null_string(mystring_t *s) {
    return (s->length == 0);
}

void print_mystring(mystring_t *s) {
    printf("capacity=%ld, length=%ld : ", s->capacity, s->length);
    for (int i = 0; i < s->length; i++) {
        printf("%c", s->content[i]);
    }
    printf("\n");
}

int main() {
    mystring_t *m = new_from_string("hello world, ooo");
    printf("length=%ld, capacity=%ld\n", m->length, m->capacity);
    int n = 0;
    mystring_t **res = split(m, 'o', &n);
    for (int i = 0; i < n; i++) {
        print_mystring(res[i]);
        if (is_null_string(res[i])) {
            printf("null for %d\n", i);
        }
    }

    mystring_t *m2 = concat_string(res[0], res[1]);
    print_mystring(res[0]);
    for (int i = 0; i < n; i++) {
        free(res[i]);
    }
    free(res);
    free(m);
    free(m2);

    return 0;
}

