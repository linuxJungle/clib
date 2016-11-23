/*
 * cstring.h
 * Copyright (C) 2016 asxalex <asxalex@promote.cache-dns.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CSTRING_H
#define CSTRING_H

typedef struct mystring_s mystring_t;

struct mystring_s {
    char *content;
    size_t length;
    size_t capacity;
};

static int mystrncpy(char *a, const char *b, size_t n);
size_t mystirng_length(mystring_t *s);
mystring_t *new_from_string(const char *);
mystring_t *new_from_nstring(const char *, size_t size);
mystring_t *concat_string(mystring_t *, const mystring_t *);
int free_mystring(mystring_t *t);
mystring_t **split(mystring_t *, const char, int *size);
void print_mystring(mystring_t *s);
int is_null_string(mystring_t *s);


#endif /* !CSTRING_H */
