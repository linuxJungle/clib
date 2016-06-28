/*
 * list.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include "list.h"
#include <stdio.h>

typedef struct example_s {
    char *key;
    int value;
    list_node_t node;
} example_t;

int main() {
    list_t list;
    init_list_head(&list);
    example_t ex1;
    ex1.value = 1;
    ex1.key = "a";
    printf("is_singular = %d\n", is_singular(&list));
    printf("is_empty = %d\n", is_empty(&list));

    list_insert_head(&list, &(ex1.node));

    printf("is_singular = %d\n", is_singular(&list));
    printf("is_empty = %d\n", is_empty(&list));

    example_t ex2;
    ex2.value = 2;
    ex2.key = "b";
    list_insert_tail(&list, &(ex2.node));
    printf("is_singular = %d\n", is_singular(&list));
    printf("is_empty = %d\n", is_empty(&list));
    
    example_t ex3;
    ex3.value = 3;
    ex3.key = "c";
    list_insert_head(&list, &(ex3.node));

    list_node_t *temp;
    example_t *example;
    list_for_each(&list, temp) {
        example = element_of(temp, struct example_s, node);
        printf("%s: %d\n", example->key, example->value);
    }

    return 0;
}
