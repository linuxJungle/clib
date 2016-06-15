/*
 * stack.c
 * Copyright (C) 2016 asxalex <asxalex@localhost>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <string.h>

mystack_t* new_stack() {
    mystack_t* s = malloc(sizeof(mystack_t));
    if (!s) 
        return NULL;
    return s;
}

int init_stack(mystack_t* s, unsigned int item_size, int length) {
    s->item = malloc(item_size * length);
    if (!s->item)
        return -1;
    s->index = 0;
    s->item_size = item_size;
    s->size = length;
    return 0;
}

void* stack_pop(mystack_t *s) {
    if (s->index <= 0)
        return NULL;
    return s->item + ((--s->index) * s->item_size);
}

int stack_push(mystack_t *s, const BYTE *node) {
    if (s->index >= s->size) {
        return -1;
    }
    printf("src address: %p\n", node);
    memcpy(s->item + s->item_size * (s->index++), node, s->item_size);
    return 0;
}

void stack_free(mystack_t *s) {
    free(s->item);
    free(s);
}

int main() {
    mystack_t *stack = new_stack();
    init_stack(stack, sizeof(int), 10);
    int i = 10;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    i++;
    stack_push(stack, (const BYTE*)&i);
    print_stack(stack, int, "%d ");
    printf("\n");
    stack_free(stack);
    return 0;
}
