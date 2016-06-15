/*
 * stack.h
 * Copyright (C) 2016 asxalex <asxalex@localhost>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef STACK_H
#define STACK_H

#ifndef BYTE
#define BYTE unsigned char
#endif

typedef struct mystack_s {
    BYTE *item;
    int index;
    unsigned int item_size;
    int size;
}mystack_t;

mystack_t* new_stack();
int init_stack(mystack_t *stack, unsigned int item_size, int length);
void* stack_pop(mystack_t *stack);
int stack_push(mystack_t *stack, const BYTE *node);
void stack_free(mystack_t *stack);

#define print_stack(s, type, fmt) \
    for (int i = 0; i < (s)->index; i++) \
        printf(fmt, *(type*)((s)->item + i * (s)->item_size))

#endif /* !STACK_H */
